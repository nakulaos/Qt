#include "Poller.h"
#include <strings.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <cstdint>
#include <cstring>
#include <exception>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <vector>
#include "Channel.h"
#include "common.h"
#define MAX_EVENTS 1024

Poller::Poller():epfd_(epoll_create1(0 )){
    // TODO(nakulaos):initial epfd_ and events_
    try{
        if(epfd_==-1){
            throw std::runtime_error("epoll create error!!!");
        }
    }catch(std::exception &e){
        std::cout<<e.what()<<std::endl;
    }
    events_=  new epoll_event[MAX_EVENTS];
    memset(events_, 0, sizeof(epoll_event)*MAX_EVENTS);
}

Poller::~Poller(){
    if(epfd_!=-1){
        close(epfd_);
    }
    delete []events_;
}

std::vector<Channel*> Poller::Poll(int64_t _timeout)const{
    // TODO(nakulaos) return poll vector of channel
    // 返回事件的轮询数组
    std::vector<Channel*> active_channel;

    //epoll_wait 参数，发生的时间数，发生的事件，最大事件数，等待时长
    int nfds = epoll_wait(epfd_,events_,MAX_EVENTS,_timeout);

    for(int i=0;i<nfds;i++){

        // 转换指针，可以直接访问事件体
        Channel *chl = static_cast<Channel*>(events_[i].data.ptr);
        uint32_t events = events_[i].events;

        // 这个事件的类型
        if(events | EPOLLIN){
            chl->SetReadyEvent(Channel::READ_EVENT);
        }
        if(events | EPOLLOUT){
            chl->SetReadyEvent(Channel::WRITE_EVENT);
        }
        if(events | EPOLLET){
            chl->SetReadyEvent(Channel::ET);
        }

        active_channel.push_back(chl);
    }

    return active_channel;
}

RC Poller::UpdateChannel(Channel* _chl)const{

    int sockfd = _chl->GetFd();

    struct epoll_event ev{};

    // 放进epfd的数据表居然是ch
    ev.data.ptr = _chl;

    if(_chl->GetListenEvents() & Channel::READ_EVENT){
        ev.events = EPOLLIN | EPOLLPRI;
        // epollin 表示有数据可读
        // epollpri 表示有紧急数据到达
    }
    if(_chl->GetListenEvents() & Channel::Channel::WRITE_EVENT){
        ev.events = EPOLLOUT;
    }
    if(_chl->GetReadyEvents() & Channel::ET){
        ev.events = EPOLLET;
    }

    if(_chl->GetExist()){
        // 存在epfd中修改即可
        try{
            if(epoll_ctl(epfd_, EPOLL_CTL_MOD, sockfd, &ev)==-1){
                throw std::runtime_error("epoll mod error!!!");
            }
        }catch(std::exception &e){
            std::cerr<<e.what()<<std::endl;
            return RC_POLLER_ERROR;
        }
    }else{
      try {
        if (epoll_ctl(epfd_, EPOLL_CTL_ADD, sockfd, &ev) == -1) {
          throw std::runtime_error("epoll add error!!!");
        }
      } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return RC_POLLER_ERROR;
      }
    }
    return RC_SUCCESS;
}

RC Poller::DeleteChannel(Channel *_chl) const { 
    int sockfd = _chl->GetFd();

    try {
      if (epoll_ctl(epfd_, EPOLL_CTL_DEL, sockfd, nullptr) == -1) {
        throw std::runtime_error("epoll del error!!!");
      }
    } catch (std::exception &e) {
      std::cerr << e.what() << std::endl;
      return RC_POLLER_ERROR;
    }
    return RC_SUCCESS;

}