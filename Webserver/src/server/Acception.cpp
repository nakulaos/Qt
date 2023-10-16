#include <fcntl.h>
#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include "Acceptor.h"
#include "Channel.h"
#include "EventLoop.h"
#include "Socket.h"
#include "common.h"

Acceptor::Acceptor(EventLoop *_loop){

    socket_ =std::make_unique<Socket>();
    try{
        if(socket_->Create()==RC_SUCCESS 
        && socket_->Bind("127.0.0.1", 8888)==RC_SUCCESS
        && socket_->Listen()==RC_SUCCESS){
            throw std::runtime_error("socket error in acceptor!!!");      
        }
    }catch(std::exception &e){
        std::cerr<<e.what()<<std::endl;
    }
    
    channel_ = std::make_unique<Channel>(_loop,socket_->GetFd());
    std::function<void()> cb = std::bind(&Acceptor::AcceptConnection,this);
    // MARK : Acceptor 为 channel 设置回调函数
    channel_->SetReadCallBack(cb);
    channel_->EnableRead();
}

Acceptor::~Acceptor()=default;

void Acceptor::SetNewConnectionCallback(std::function<void(int)> const&  _callback){
    new_connection_callback_ = std::move(_callback);
}

RC Acceptor::AcceptConnection() const {
    int clnt_fd = -1;
    if(socket_->Accept(clnt_fd)!= RC_SUCCESS){
        return RC_ACCEPTOR_ERROR;
    }
    // 设置非阻塞
    fcntl(clnt_fd, F_SETFL,fcntl(clnt_fd, F_GETFL|O_NONBLOCK));

    if(new_connection_callback_){
        new_connection_callback_(clnt_fd); 
    }

    return RC_SUCCESS;

}