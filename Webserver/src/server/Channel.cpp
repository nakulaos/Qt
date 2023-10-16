#include "Channel.h"

#include <EventLoop.h>

#include <cstdint>

const int16_t Channel::READ_EVENT = 1;
const int16_t Channel::WRITE_EVENT = 2;
const int16_t Channel::ET = 4;

Channel::Channel(EventLoop *_loop, int _fd)
    : fd_(_fd), loop_(_loop), listen_events_(0), ready_events_(0), exists_() {}

Channel::~Channel() { loop_->DeleteChannel(this); }

int Channel::GetFd() { return fd_; }

int16_t Channel::GetListenEvents() { return listen_events_; }

int16_t Channel::GetReadyEvents() { return ready_events_; }

bool Channel::GetExist() { return exists_; }

void Channel::SetReadyEvent(int16_t _ev) { ready_events_ = _ev; }

void Channel::SetReadCallBack(std::function<void()> const &_callback) {
  read_callback_ = std::move(_callback);
}

void Channel::SetWriteCallBack(std::function<void()> const &_callback) {
  write_callback_ =std::move( _callback);
}

void Channel::SetExist(bool _condition) { exists_ = _condition; }

void Channel::HandleEvent(){
    if(ready_events_ & READ_EVENT){
        read_callback_();
    }
    if(ready_events_ & WRITE_EVENT){
        write_callback_();
    }
}

void Channel::EnableRead(){
    listen_events_ |= READ_EVENT;
    loop_->UpdateChannel(this);
}

void Channel::EnableWrite(){
    listen_events_ |= WRITE_EVENT;
    loop_->UpdateChannel(this);
}

void Channel::EnableET(){
    listen_events_ |= ET;
    loop_->UpdateChannel(this);
}

