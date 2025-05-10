#pragma once
#include <string>
#include <vector>
#include <mutex>

struct OrderBookEntry {
    double price;
    double quantity;
};

class OrderBook {
public:
    void update(const std::string& json_data);
    double calculate_imbalance();
    std::string snapshot_to_csv();

private:
    std::vector<OrderBookEntry> bids;
    std::vector<OrderBookEntry> asks;
    std::mutex mtx;
};