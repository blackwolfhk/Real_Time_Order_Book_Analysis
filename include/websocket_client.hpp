#ifndef WEBSOCKET_CLIENT_HPP
#define WEBSOCKET_CLIENT_HPP

#include <string>
#include <functional>

class WebSocketClient {
public:
    using MessageHandler = std::function<void(const std::string&)>;
    void start(const std::string& host, const std::string& target, MessageHandler handler);
};

#endif // WEBSOCKET_CLIENT_HPP