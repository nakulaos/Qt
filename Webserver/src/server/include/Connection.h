#pragma once

#include <functional>
#include <memory>
#include <string_view>
#include "Buffer.h"
#include "Channel.h"
#include "Socket.h"
#include "common.h"
class Connection{
    public:
    enum State{
        Invalid =0,
        Connecting,
        Connected,
        Closed,
    };

    Connection(const Connection &) = delete;
    Connection(Connection &&) = delete;
    Connection &operator=(const Connection &) = delete;
    Connection &operator=(Connection &&) = delete;
    Connection(int _fd, EventLoop *_loop);
    ~Connection();
    
    void SetDeleteConnection(std::function<void(int)> _fn);
    void SetOnConnection(std::function<void(Connection*)> _fn);
    void SetOnRecv(std::function<void(Connection*)> _fn);
    void SetSendBuf(std::string_view _sv);

    State GetState();
    Socket* GetSocket();
    Buffer* GetReadBuffer();
    Buffer* GetSendBuffer(); 

    RC Read();
    RC Write();
    RC Send(std::string _msg);
    void Close();
    void OnMessage(std::function<void()> _fn);
    void OnConnect(std::function<void()> _fn);
    
    private:
    void Business(); // 自定义业务逻辑函数
    RC ReadNonBlocking();
    RC WriteNonBlocking();
    RC ReadBlocking();
    RC WriteBlocking();


    State state_; // 连接状态
    std::unique_ptr<Socket> socket_; // connect 的端口
    std::unique_ptr<Channel> channel_; // 这个connect的事件
    std::unique_ptr<Buffer> read_buf_; // 缓冲区
    std::unique_ptr<Buffer> send_buf_;
    std::function<void(int)> delete_connection_; // 链接删除函数
    std::function<void(Connection*)> on_recv_; // 

};