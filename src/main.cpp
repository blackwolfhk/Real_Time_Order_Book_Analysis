#include "websocket_client.hpp"
#include "csv_writer.hpp"
#include "orderbook.hpp"

#include <iostream>
#include <filesystem>
#include <atomic>
#include <ctime>

int main() {
    std::filesystem::create_directories("data");

    CSVWriter writer("data/orderbook_log.csv");
    OrderBook orderbook;
    std::atomic<std::time_t> last_logged_time{0};

    WebSocketClient ws;
    ws.start("stream.binance.com", "/ws/btcusdt@depth20@100ms", [&](const std::string& msg) {
        std::time_t now = std::time(nullptr);

        if (now != last_logged_time) {
            last_logged_time = now;

            try {
                std::cout << "Raw message: " << msg.substr(0, 200) << "..." << std::endl;
                orderbook.update(msg);
                double real_imbalance = orderbook.calculate_imbalance();
                
                std::string line = std::to_string(now) + "," + std::to_string(real_imbalance);
                std::cout << "Logging: " << line << std::endl;
                writer.write_line(line);
                
            } catch (const std::exception& e) {
                std::cerr << "Error parsing data: " << e.what() << std::endl;
                std::string line = std::to_string(now) + ",-1";
                writer.write_line(line);
            }
        }
    });

    std::cout << "WebSocket started. Press [Enter] to stop..." << std::endl;
    std::cin.get();
    return 0;
}
