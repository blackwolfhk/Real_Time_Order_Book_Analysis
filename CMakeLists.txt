cmake_minimum_required(VERSION 3.10)
project(realtime_orderbook)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

# Find Boost
find_package(Boost REQUIRED)

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# Main executable
add_executable(realtime_orderbook
    src/main.cpp
    src/websocket_client.cpp
    src/orderbook.cpp
    src/csv_writer.cpp
)

target_include_directories(realtime_orderbook PRIVATE
    ${Boost_INCLUDE_DIRS}
    ${OPENSSL_INCLUDE_DIR}
)

target_link_libraries(realtime_orderbook
    ${OPENSSL_LIBRARIES}
    pthread
)


target_include_directories(test_csv PRIVATE include)