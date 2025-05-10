# 📈 Real-Time Binance Order Book Logger (C++)

This project connects to the Binance WebSocket API and logs real-time order book data (depth updates) for a selected trading pair (e.g., `BTC/USDT`). It computes the **order book imbalance** and logs it to a CSV file for further analysis and backtesting.

---

## Features

- Connects to Binance WebSocket using `Boost.Beast` (SSL over WebSocket)
- Parses real-time order book depth updates
- Computes **order book imbalance** (bid vs ask volume)
- Logs timestamped data into a CSV file
- Modular C++17 codebase with `OrderBook`, `CSVWriter`, and `WebSocketClient`
- Cross-platform (macOS & Linux)

---

## Dependencies

Before building, make sure you have the following installed:

### macOS (via Homebrew):

```bash
brew install boost
brew install openssl
brew install cmake
```

### Build Instructions

1. Clone the Repository

```bash
   git clone https://github.com/blackwolfhk/Real_Time_Order_Book_Analysis
```

2. Configure the Project with CMake

```bash
   cmake -S . -B build \
    -DOPENSSL_ROOT_DIR=$(brew --prefix openssl) \
```

```bash
cmake --build build --target realtime_orderbook
```

### Run the real-time logger:

```bash
./build/realtime_orderbook
```
