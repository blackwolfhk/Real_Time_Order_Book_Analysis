#!/bin/bash
cd "$(dirname "$0")/.."
mkdir -p build
cd build
cmake ..
make -j$(sysctl -n hw.logicalcpu)
./realtime_orderbook