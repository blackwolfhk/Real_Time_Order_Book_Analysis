#include "websocket_client.hpp"
#include "csv_writer.hpp"
#include "orderbook.hpp"

#include <iostream>
#include <filesystem>
#include <atomic>
#include <ctime>
#include <iomanip>

int main() {
    std::filesystem::create_directories("data");

    CSVWriter writer("data/orderbook_log.csv");
    OrderBook orderbook;
    std::atomic<std::time_t> last_logged_time{0};

    WebSocketClient ws;
    ws.start("stream.binance.com", "/ws/btcusdt@depth20@100ms", [&](const std::string&msg) {
        std::time_t now = std::time(nullptr);

        if (now != last_logged_time) {
            last_logged_time = now;

            try {
                // Clear screen and show formatted data
                std::cout << "\033[2J\033[1;1H"; // Clear screen
                std::cout << "🚀 ===== BTC/USDT REAL-TIME ORDER BOOK ===== 🚀" << std::endl;
                std::cout << "⏰ Time: " << std::put_time(std::localtime(&now), "%H:%M:%S") << std::endl;
                std::cout << "═══════════════════════════════════════════════" << std::endl;

                orderbook.update(msg);
                double real_imbalance = orderbook.calculate_imbalance();
                
                // Get order book data for display
                auto bids = orderbook.get_bids();
                auto asks = orderbook.get_asks();
                
                std::cout << std::fixed << std::setprecision(2);
                
                // Display top asks (sell orders) - higher prices first
                std::cout << "\n📉 ASKS (Sell Orders):" << std::endl;
                std::cout << "┌─────────────┬──────────────┐" << std::endl;
                std::cout << "│    Price    │    Volume    │" << std::endl;
                std::cout << "├─────────────┼──────────────┤" << std::endl;
                
                // Show top 5 asks (reversed order - highest first)
                for (int i = std::min(4, (int)asks.size() - 1); i >= 0; i--) {
                    std::cout << "│ $" << std::setw(10) << asks[i].first 
                              << " │ " << std::setw(11) << asks[i].second << " │" << std::endl;
                }
                
                // Show spread
                if (!bids.empty() && !asks.empty()) {
                    double spread = asks[0].first - bids[0].first;
                    double spread_pct = (spread / bids[0].first) * 100;
                    std::cout << "├─────────────┼──────────────┤" << std::endl;
                    std::cout << "│ 💰 SPREAD: $" << std::setw(6) << spread 
                              << " (" << std::setprecision(4) << spread_pct << "%) │" << std::endl;
                }
                
                std::cout << "├─────────────┼──────────────┤" << std::endl;
                
                // Display top bids (buy orders)
                std::cout << "│ 📈 BIDS (Buy Orders)        │" << std::endl;
                std::cout << "├─────────────┼──────────────┤" << std::endl;
                
                // Show top 5 bids
                for (int i = 0; i < std::min(5, (int)bids.size()); i++) {
                    std::cout << "│ $" << std::setw(10) << bids[i].first 
                              << " │ " << std::setw(11) << bids[i].second << " │" << std::endl;
                }
                
                std::cout << "└─────────────┴──────────────┘" << std::endl;
                
                // Show analysis
                std::cout << "\n📊 MARKET ANALYSIS:" << std::endl;
                std::cout << "╔══════════════════════════════════╗" << std::endl;
                std::cout << "║ Order Imbalance: " << std::setw(15) << std::setprecision(6) << real_imbalance << " ║" << std::endl;
                
                std::string imbalance_desc;
                if (real_imbalance > 0.1) imbalance_desc = "🟢 STRONG BUY PRESSURE";
                else if (real_imbalance > 0.05) imbalance_desc = "🔵 MODERATE BUY";
                else if (real_imbalance < -0.1) imbalance_desc = "🔴 STRONG SELL PRESSURE";
                else if (real_imbalance < -0.05) imbalance_desc = "🟠 MODERATE SELL";
                else imbalance_desc = "⚪ BALANCED MARKET";
                
                std::cout << "║ Signal: " << std::setw(22) << imbalance_desc << " ║" << std::endl;
                std::cout << "╚══════════════════════════════════╝" << std::endl;
                
                // Log to CSV
                std::string line = std::to_string(now) + "," + std::to_string(real_imbalance);
                writer.write_line(line);
                
                std::cout << "\n💾 Data logged to CSV | 🔄 Updates every second" << std::endl;
                std::cout << "Press [Enter] to stop..." << std::endl;
                
            } catch (const std::exception& e) {
                std::cerr << "❌ Error parsing data: " << e.what() << std::endl;
                std::string line = std::to_string(now) + ",-1";
                writer.write_line(line);
            }
        }
    });

    std::cout << "🚀 WebSocket started. Press [Enter] to stop..." << std::endl;
    std::cin.get();
    return 0;
}
