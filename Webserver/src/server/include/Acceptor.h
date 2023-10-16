#pragma once

#include <functional>
#include <memory>

#include "Channel.h"
#include "Socket.h"
#include "common.h"
class Acceptor {
   public:
    Acceptor(const Acceptor &) = delete;
    Acceptor(Acceptor &&) = delete;
    Acceptor &operator=(const Acceptor &) = delete;
    Acceptor &operator=(Acceptor &&) = delete;
    explicit Acceptor(EventLoop *_loop);
    ~Acceptor();

    [[nodiscard]] RC AcceptConnection() const;
    void SetNewConnectionCallback(std::function<void(int)> const &_callback);

   private:
    std::unique_ptr<Socket> socket_;
    std::unique_ptr<Channel> channel_;
    std::function<void(int)> new_connection_callback_;
};