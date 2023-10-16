#pragma once
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>
#include "Acceptor.h"
#include "Channel.h"
#include "Connection.h"
#include "ThreadPool.h"
#include"common.h"

class TcpServer{
    public:
    TcpServer();
    TcpServer(const TcpServer &) = delete;
    TcpServer(TcpServer &&) = delete;
    TcpServer &operator=(const TcpServer &) = delete;
    TcpServer &operator=(TcpServer &&) = delete;
    ~TcpServer();

    void Start();

    RC NewConnection(int _fd);
    RC DeleteConnection(int _fd);
    // MARK:由使用这个服务器的去设置回调函数
    void SetOnConnect(std::function<void(Connection*)> _fn);
    void SetOnRecv(std::function<void(Connection*)> _fn);

    private:
    std::unique_ptr<EventLoop> main_reactor_;
    std::unique_ptr<Acceptor> acceptor_;
    std::unordered_map<int, std::unique_ptr<Connection>> connections_;
    std::vector<std::unique_ptr<EventLoop>> sub_reactors_;
    std::unique_ptr<ThreadPool> thread_pool_; //线程池
    std::function<void(Connection*)> on_recv_; // 用来设置conn的业务逻辑函数
    std::function<void(Connection*)> on_connect_;  //为Acceptor连接时自定义的回调函数
};