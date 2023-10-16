#pragma once

#include"common.h"
#include<vector>
#include<sys/epoll.h>

class Channel;

class Poller{
    public:
    Poller();
    Poller(const Poller &) = delete;
    Poller(Poller &&) = delete;
    Poller &operator=(const Poller &) = delete;
    Poller &operator=(Poller &&) = delete;
    ~Poller();

    RC UpdateChannel(Channel *_chl)const;
    RC DeleteChannel(Channel *_chl)const;

    [[nodiscard]] std::vector<Channel*> Poll(int64_t timeout=-1)const;

    private:
    int epfd_;  // epoll 实例的句柄
    struct epoll_event *events_{nullptr}; 
    // 接口的返回参数，epoll把发生的事件的集合从内核复制到
    // events数组中


};