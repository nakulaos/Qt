#include <memory>
#include "Channel.h"
#include"EventLoop.h"
#include "Poller.h"

EventLoop::EventLoop(){
    poller_ = std::make_unique<Poller>();
}

EventLoop::~EventLoop()=default;

void EventLoop::Loop()const{
    while(true){
        for(Channel* chl : poller_->Poll()){
            chl->HandleEvent();
        }
    }
}

void EventLoop::UpdateChannel(Channel *_chl)const{
    poller_->UpdateChannel(_chl);
}

void EventLoop::DeleteChannel(Channel *_chl)const{
    poller_->DeleteChannel(_chl);
}