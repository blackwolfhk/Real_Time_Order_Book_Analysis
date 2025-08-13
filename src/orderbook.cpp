#include "orderbook.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void OrderBook::update(const std::string& data) {
    std::lock_guard<std::mutex> lock(mtx);
    auto j = json::parse(data);
    bids.clear();
    asks.clear();

    for (const auto& bid : j["bids"]) {
        bids.push_back({std::stod(bid[0].get<std::string>()), std::stod(bid[1].get<std::string>())});
    }
    for (const auto& ask : j["asks"]) {
        asks.push_back({std::stod(ask[0].get<std::string>()), std::stod(ask[1].get<std::string>())});
    }
}

double OrderBook::calculate_imbalance() {
    std::lock_guard<std::mutex> lock(mtx);
    double bid_volume = 0, ask_volume = 0;
    for (const auto& b : bids) bid_volume += b.quantity;
    for (const auto& a : asks) ask_volume += a.quantity;
    return bid_volume / (bid_volume + ask_volume);
}

std::string OrderBook::snapshot_to_csv() {
    std::lock_guard<std::mutex> lock(mtx);
    double imbalance = calculate_imbalance();
    return std::to_string(imbalance);
}