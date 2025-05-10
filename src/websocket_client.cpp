#include "websocket_client.hpp"
#include <boost/beast.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <thread>
#include <iostream>

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
namespace ssl = boost::asio::ssl;
using tcp = net::ip::tcp;

void WebSocketClient::start(const std::string& host, const std::string& target, MessageHandler handler) {
    std::thread([=]() {
        try {
            net::io_context ioc;
            ssl::context ctx(ssl::context::tlsv12_client);

            // Load root certificates
            ctx.set_default_verify_paths();

            // Resolve the domain name
            tcp::resolver resolver(ioc);
            auto const results = resolver.resolve(host, "9443");

            // Create WebSocket stream over SSL
            websocket::stream<beast::ssl_stream<tcp::socket>> ws(ioc, ctx);

            // Connect to the endpoint
            net::connect(ws.next_layer().next_layer(), results.begin(), results.end());

            // Perform SSL handshake
            ws.next_layer().handshake(ssl::stream_base::client);

            // Perform WebSocket handshake
            ws.handshake(host, target);

            std::cout << "✅ WebSocket handshake successful with Binance at " << host << target << std::endl;

            // Start reading messages
            for (;;) {
                beast::flat_buffer buffer;
                ws.read(buffer);

                std::string msg = beast::buffers_to_string(buffer.data());

                if (!msg.empty()) {
                    handler(msg); // Pass message to callback
                } else {
                    std::cerr << "⚠️ Received empty message from WebSocket." << std::endl;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "❌ WebSocket error: " << e.what() << std::endl;

            // Optional: retry on disconnect
            // std::this_thread::sleep_for(std::chrono::seconds(5));
            // start(host, target, handler);  // naive reconnect
        }
    }).detach();
}