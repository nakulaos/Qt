#pragma  once
#include "Channel.h"
#include "Poller.h"
#include"common.h"
#include <memory>

class EventLoop{
    public:
    EventLoop();
    ~EventLoop();

    void Loop()const;
    void UpdateChannel(Channel *chl)const;
    void DeleteChannel(Channel *chl)const;

    private:
    std::unique_ptr<Poller> poller_;
};