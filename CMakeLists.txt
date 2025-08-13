cmake_minimum_required(VERSION 3.10)
project(realtime_orderbook)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

# Find Boost
find_package(Boost REQUIRED COMPONENTS system)

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# Add nlohmann/json
find_package(nlohmann_json 3.2.0 QUIET)
if(NOT nlohmann_json_FOUND)
    include(FetchContent)
    FetchContent_Declare(json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3)
    FetchContent_MakeAvailable(json)
endif()

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
    Boost::system
    ${OPENSSL_LIBRARIES}
    nlohmann_json::nlohmann_json
    pthread
)