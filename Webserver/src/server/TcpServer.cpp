#include "TcpServer.h"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <thread>
#include <utility>
#include "Acceptor.h"
#include "Channel.h"
#include "Connection.h"
#include "ThreadPool.h"
#include "common.h"


TcpServer::TcpServer(){
    main_reactor_=std::make_unique<EventLoop>();
    acceptor_ = std::make_unique<Acceptor>(main_reactor_.get());
    std::function<void(int)> cb = std::bind(&TcpServer::NewConnection,this,std::placeholders::_1);
    // MARK :TcpServer 为 accept设置 回调函数
    acceptor_->SetNewConnectionCallback(cb);

    unsigned int size = std::thread::hardware_concurrency();
    thread_pool_ = std::make_unique<ThreadPool>(size);

    for(unsigned int i=0;i<size;i++){
        std::unique_ptr<EventLoop> sub_reactor = std::make_unique<EventLoop>();
        sub_reactors_.push_back(std::move(sub_reactor));
    }
    Start();
}

TcpServer::~TcpServer()= default;

void TcpServer::Start(){
    // TODO（naklaos）:开启服务器，将每个线程的事件循环添加进线程池
    for(const auto & sub_reactor : sub_reactors_){
        std::function<void()> sub_loop =
            std::bind(&EventLoop::Loop, sub_reactor.get());
        thread_pool_->Add(std::move(sub_loop));
    }
    main_reactor_->Loop();
}

RC TcpServer::NewConnection(int _fd){
    uint64_t random = _fd%sub_reactors_.size();
    std::unique_ptr<Connection> conn = std::make_unique<Connection>(_fd,sub_reactors_[random].get());
    std::function<void(int)> cb = std::bind(&TcpServer::DeleteConnection,this,std::placeholders::_1);


    //MARK: Acceptor 为 Connection 设置回调函数
    conn->SetDeleteConnection(cb);
    conn->SetOnRecv(on_recv_);

    connections_[_fd]=std::move(conn);
    if(on_connect_){
        on_connect_(connections_[_fd].get());
    }
    return RC_SUCCESS;
}


RC TcpServer::DeleteConnection(int _fd){
    auto it=connections_.find(_fd);
    assert(it!=connections_.end());
    connections_.erase(_fd);
    return RC_SUCCESS;
}

void TcpServer::SetOnConnect(std::function<void(Connection*)> _fn){
    on_connect_=std::move(_fn);
}

void TcpServer::SetOnRecv(std::function<void(Connection*)> _fn){
    on_recv_ = std::move(_fn);
}
