#pragma once

#include <cstdint>
#include <functional>
#include <sys/epoll.h>
#include <sys/types.h>

class Epoll;
class EventLoop;

// channel是针对一个服务器不同服务类型，所以需要有一个fd和epoll
// 而通过指针，理论上我们可以指向任何一个地址块的内容，可以是一个类的对象，这样就可以将一个文件描述符封装成一个`Channel`类，一个Channel类自始至终只负责一个文件描述符，对不同的服务、不同的事件类型，都可以在类中进行不同的处理，而不是仅仅拿到一个`int`类型的文件描述符。

class Channel {
public:
  Channel(const Channel &) = delete;
  Channel(Channel &&) = delete;
  Channel &operator=(const Channel &) = delete;
  Channel &operator=(Channel &&) = delete;
  Channel(EventLoop *_loop, int _fd);
  ~Channel();

  void HandleEvent();
  void EnableRead();
  void EnableWrite();
  void EnableET();

  int GetFd();
  int16_t GetReadyEvents();
  int16_t GetListenEvents();
  bool GetExist();

  void SetReadyEvent(int16_t _ev);
  void SetReadCallBack(std::function<void()> const &_callback);
  void SetWriteCallBack(std::function<void()> const &_callback);
  void SetExist(bool _condition);

  static const int16_t READ_EVENT;
  static const int16_t WRITE_EVENT;
  static const int16_t ET;

private:
  int fd_;  // channel 负责的fd
  EventLoop *loop_;// channel 所在的事件处理循环
  int16_t listen_events_;// chanel负责监听的事件
  int16_t ready_events_; // channel 已经发生的事件
  bool exists_; // channel 是否在事件循环中
  std::function<void()> read_callback_; //读回调函数
  std::function<void()> write_callback_; // 写回调函数
};
