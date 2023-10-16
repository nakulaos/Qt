# webserver
## 类介绍
+ socket 
  封装socket的listen，bind，poller，eventloop，create等函数
+ poller
  封装epoll_event 的 epoll_ctl,epoll_wait,epoll_create等函数，给eventloop提供两个接口，updateChannel，poll（事件轮询）
+ eventloop
  poller的使用者，解决事件轮询由谁去使用
+ channel
  抽象了事件，提供handleevent的回调函数
+ Buffer
  缓冲区
+ connect
  提供连接的读写

+ acceptor
  负责连接
