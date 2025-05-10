#include "websocket_client.hpp"
#include "csv_writer.hpp"

#include <iostream>
#include <filesystem>
#include <atomic>
#include <ctime>

int main() {
    std::filesystem::create_directories("data");

    CSVWriter writer("data/orderbook_log.csv");
    std::atomic<std::time_t> last_logged_time{0};

    WebSocketClient ws;
    ws.start("stream.binance.com", "/ws/btcusdt@depth", [&](const std::string& msg) {
        std::time_t now = std::time(nullptr);

        if (now != last_logged_time) {
            last_logged_time = now;

            std::string line = std::to_string(now) + ",0.5"; // Dummy imbalance
            std::cout << "📝 Logging: " << line << std::endl;
            writer.write_line(line);
        }
    });

    std::cout << "🚀 WebSocket started. Press [Enter] to stop...\n";
    std::cin.get();
    return 0;
}