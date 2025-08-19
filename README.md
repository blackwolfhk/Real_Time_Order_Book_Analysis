Here's a complete beginner-friendly README.md for your project:

```markdown
# Real-Time Binance Order Book Logger

This project connects to the Binance WebSocket API and logs real-time order book data (depth updates) for a selected trading pair (e.g., `BTC/USDT`). It computes the **order book imbalance** and logs it to a CSV file for further analysis and backtesting.

---

## 🚀 Features

- Connects to Binance WebSocket using `Boost.Beast` (SSL over WebSocket)
- Parses real-time order book depth updates
- Computes **order book imbalance** (bid vs ask volume)
- Logs timestamped data into a CSV file
- Modular C++17 codebase with `OrderBook`, `CSVWriter`, and `WebSocketClient`
- Cross-platform (Windows/WSL, macOS & Linux)

---

## 📋 Prerequisites

- **Windows**: WSL2 (Windows Subsystem for Linux) recommended
- **macOS/Linux**: Native terminal
- Basic familiarity with command line

---

## 🛠️ Complete Setup Guide (First Time)

### Step 1: Install Dependencies

#### **Windows (WSL2 - Recommended)**

1. **Install WSL2** (if not already installed):
   - Open PowerShell as Administrator
   - Run: `wsl --install`
   - Restart your computer
   - Open WSL terminal

2. **Install build tools and dependencies**:
```bash
# Update package list
sudo apt update

# Install build tools and dependencies
sudo apt install -y build-essential cmake libboost-all-dev libssl-dev git

# Verify installation
g++ --version
cmake --version
```

#### **macOS**

```bash
# Install Homebrew (if not installed)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Install dependencies
brew install cmake boost openssl

# Verify installation
g++ --version
cmake --version
```

#### **Linux (Ubuntu/Debian)**

```bash
# Update package list
sudo apt update

# Install build tools and dependencies
sudo apt install -y build-essential cmake libboost-all-dev libssl-dev git

# Verify installation
g++ --version
cmake --version
```

### Step 2: Clone or Download the Project

If you haven't already:

```bash
# Clone the repository (if using git)
git clone https://github.com/blackwolfhk/Real_Time_Order_Book_Analysis
cd Real_Time_Order_Book_Analysis

# OR if you downloaded as ZIP, navigate to the extracted folder
cd /path/to/Real_Time_Order_Book_Analysis
```

### Step 3: Build the Project

```bash
# Step 3.1: Configure the project (creates build files)
cmake -S . -B build

# Step 3.2: Build the executable
cmake --build build --target realtime_orderbook
```

**Expected Output**:
- Step 3.1 should show: "Found Boost", "Found OpenSSL", "Configuring done"
- Step 3.2 should show compilation progress for each .cpp file

### Step 4: Run the Application

```bash
# Run the executable
./build/realtime_orderbook
```

---

## 🔧 Troubleshooting

### Common Issues and Solutions

#### **Issue**: `cmake: command not found`
**Solution**: 
```bash
sudo apt install cmake
```

#### **Issue**: `fatal error: 'boost/beast.hpp' file not found`
**Solution**: 
```bash
sudo apt install libboost-all-dev
```

#### **Issue**: `OpenSSL not found`
**Solution**: 
```bash
sudo apt install libssl-dev
```

#### **Issue**: Build fails with linker errors
**Solution**: Clean and rebuild:
```bash
rm -rf build
cmake -S . -B build
cmake --build build --target realtime_orderbook
```

#### **Issue**: Permission denied when running executable
**Solution**: 
```bash
chmod +x ./build/realtime_orderbook
./build/realtime_orderbook
```

---

## 📁 Project Structure

```
Real_Time_Order_Book_Analysis/
├── CMakeLists.txt          # Build configuration
├── README.md               # This file
├── src/                    # Source code
│   ├── main.cpp
│   ├── websocket_client.cpp
│   ├── orderbook.cpp
│   └── csv_writer.cpp
├── include/                # Header files
│   ├── websocket_client.hpp
│   ├── orderbook.hpp
│   └── csv_writer.hpp
├── data/                   # Output CSV files (generated)
└── build/                  # Build files (generated)
    └── realtime_orderbook  # Final executable
```

---

## 🖥️ Usage

1. **Run the application**:
```bash
./build/realtime_orderbook
```

2. **Check the output**:
   - The application will connect to Binance WebSocket
   - Real-time order book data will be logged to `data/orderbook_BTCUSDT.csv`
   - Press `Ctrl+C` to stop the application

3. **Analyze the data**:
   - Open the CSV file to see timestamped order book data
   - Use the data for backtesting or analysis

---

## 🔄 Development Workflow

### Making Changes

1. **Edit source files** in `src/` or `include/`
2. **Rebuild**:
```bash
cmake --build build --target realtime_orderbook
```
3. **Test**:
```bash
./build/realtime_orderbook
```

### Clean Build (if needed)

```bash
rm -rf build
cmake -S . -B build
cmake --build build --target realtime_orderbook
```

---

## 📊 Output Format

The CSV file contains:
- **Timestamp**: When the data was received
- **Symbol**: Trading pair (e.g., BTCUSDT)
- **Best Bid**: Highest buy price
- **Best Ask**: Lowest sell price
- **Bid Volume**: Volume at best bid
- **Ask Volume**: Volume at best ask
- **Imbalance**: (Bid Volume - Ask Volume) / (Bid Volume + Ask Volume)

---

## ⚡ Quick Commands Reference

```bash
# First time setup (after installing dependencies)
cmake -S . -B build && cmake --build build --target realtime_orderbook

# Run the application
./build/realtime_orderbook

# Rebuild after making changes
cmake --build build --target realtime_orderbook

# Clean and rebuild (if issues)
rm -rf build && cmake -S . -B build && cmake --build build --target realtime_orderbook
```


