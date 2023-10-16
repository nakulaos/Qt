#include "Connection.h"

#include <asm-generic/errno-base.h>
#include <asm-generic/errno.h>
#include <sys/types.h>
#include <unistd.h>

#include <algorithm>
#include <cerrno>
#include <cstddef>
#include <cstring>
#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string_view>

#include "Buffer.h"
#include "Channel.h"
#include "Socket.h"
#include "common.h"

Connection::Connection(int _fd, EventLoop *_loop) {
    socket_ = std::make_unique<Socket>();
    socket_->SetFd(_fd);
    if (_loop != nullptr) {
        channel_ = std::make_unique<Channel>(_loop, _fd);
        channel_->EnableRead();
        // ET模式只通知一次
        channel_->EnableET();
    }
    read_buf_ = std::make_unique<Buffer>();
    send_buf_ = std::make_unique<Buffer>();

    state_ = State::Connected;
}

RC Connection::Read() {
    // TODO(nakulaos): read功能

    // 判断是否连接
    try {
        if (state_ != State::Connected) {
            throw std::runtime_error(
                "Connection is not connected ,can`t not read");
        }
    } catch (std::exception &e) {
        std::cerr << "catch:" << e.what();
        return RC_CONNECTION_ERROR;
    }

    read_buf_->Clear();

    // 根据socket来选择阻塞读和非阻塞读
    if (socket_->IsNonBlocking()) {
        return ReadNonBlocking();
    }
    return ReadBlocking();
}

RC Connection::ReadNonBlocking() {
    int sockfd = socket_->GetFd();

    char buf[1024];

    while (true) {
        memset(buf, 0, sizeof(buf));
        ssize_t bytes_read = ::read(sockfd, buf, sizeof(buf));

        if (bytes_read > 0) {
            read_buf_->Append(buf, bytes_read);
        } else if (bytes_read == -1) {
            if (errno == EINTR) {
                // 程序正常中断，继续读取
                std::cout << "continue reading...\n";
            } else if (errno == EAGAIN && errno == EWOULDBLOCK) {
                // 非阻塞IO，这个条件表示全部1读取完毕
                break;
            }
        } else if (bytes_read == 0) {
            // EOF,客户端断开连接
            std::cout << "read EOF,client fd " << sockfd << " disconnected\n";
            state_ = State::Closed;
            Close();
            break;
        } else {
            std::cout << "other error on client fd" << sockfd << std::endl;
            state_ = State::Closed;
            Close();
            break;
        }
    }

    return RC_SUCCESS;
}

RC Connection::Write(){
    //TODO(nakulaos): write 功能 ，解决了怎么写的问题，但并未解决是调用它写的问题

    // 判断是否连接
    try {
        if (state_ != State::Connected) {
            throw std::runtime_error(
                "Connection is not connected ,can`t not read");
        }
    } catch (std::exception &e) {
        std::cerr << "catch:" << e.what();
        return RC_CONNECTION_ERROR;
    }

    RC  rc=RC::RC_UNDEFINE;
    if(socket_->IsNonBlocking()){
        rc=WriteNonBlocking();
    }else{
        rc=WriteBlocking();
    }
    send_buf_->Clear();
    return rc;
}

RC Connection::WriteNonBlocking(){

    int sockfd = socket_->GetFd();
    // 一次写入的有限制
    char buf[send_buf_->Size()];
    memcpy(buf, send_buf_->CStr(), send_buf_->Size());

    int data_size = send_buf_->Size();

    int data_left = data_size;

    while(data_left>0){
        ssize_t bytes_write = ::write(sockfd, buf+data_size-data_left,sizeof(buf));
        if(bytes_write==-1){
            if(errno == EINTR){
                std::cout<<"continue writing!!! \n";
                continue;
            } else if (errno == EAGAIN) {
                // 全部写完
                break;
            }else{
                // 客户端断开
                std::cout<<"Other error happened on client fd "<<sockfd<<std::endl;
                state_=State::Closed;
            }
            data_left-= bytes_write;
        }

    }
    return RC_SUCCESS;
}

RC Connection::WriteBlocking(){
    int sockfd = socket_->GetFd();
    ssize_t bytes_write = write(sockfd, send_buf_->GetBuf().c_str(),send_buf_->Size());
    if(bytes_write==-1){
        std::cout << "Other error happened on client fd " << sockfd
                  << std::endl;
        state_ = State::Closed;
    }
    return RC_SUCCESS;
}

RC Connection::ReadBlocking(){
    //TODO(nakulaos):非阻塞是提供给客户端
    int sockfd = socket_->GetFd();
    // unsigned int rcv_size = 0;
    // socklen_t len = sizeof(rcv_size);
    // getsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &rcv_size, &len);
    size_t data_size = socket_->RecvBufSize();
    char buf[1024];
    ssize_t bytes_read = read(sockfd, buf, sizeof(buf));
    if (bytes_read > 0) {
        read_buf_->Append(buf, bytes_read);
    } else if (bytes_read == 0) {
        printf("read EOF, blocking client fd %d disconnected\n", sockfd);
        state_ = State::Closed;
    } else if (bytes_read == -1) {
        printf("Other error on blocking client fd %d\n", sockfd);
        state_ = State::Closed;
    }
    return RC_SUCCESS;
}

RC Connection::Send(std::string _msg){
    // TODO(nakulaos):发送字符串_msg，解决谁调用写（存疑）
    SetSendBuf(_msg);
    Write();
    return RC_SUCCESS;
}

// MARK 不懂的代码
void Connection::Business(){
    // 业务逻辑函数
    Read();
    on_recv_(this);
}

void Connection::SetDeleteConnection(std::function<void(int)> _fn){
    delete_connection_ = std::move(_fn);
}

void Connection::SetOnConnection(std::function<void(Connection *)> _fn){
    on_recv_ = std::move(_fn);
    std::function<void()> bus = std::bind(&Connection::Business,this);
    //MARK: connection 为 channel 设置回调函数
    channel_->SetReadCallBack(bus);
}

void Connection::SetOnRecv(std::function<void(Connection*)> _fn){
    on_recv_ = _fn;
}

void Connection::Close(){
    delete_connection_(socket_->GetFd());
}

Connection::State Connection::GetState(){
    return state_;
}

Socket* Connection::GetSocket(){
    return socket_.get();
}

void Connection::SetSendBuf(std::string_view _sv){
    send_buf_->SetBuf(_sv);
}

Buffer* Connection::GetSendBuffer(){
    return send_buf_.get();
}

Buffer* Connection::GetReadBuffer(){
    return read_buf_.get();
}

