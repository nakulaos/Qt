#include "Socket.h"
#include "common.h"
#include <arpa/inet.h>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <exception>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

Socket::Socket() : fd_(-1) {}

Socket::~Socket() {
  if (fd_ != -1) {
    close(fd_);
  }
  fd_ = -1;
}

void Socket::SetFd(int _fd) { fd_ = _fd; }

int Socket::GetFd() { return fd_; }

std::string Socket::GetAddr() {
  // TODO(nakulaos): 以字符串的形式返回绑定的地址
  // getpeername 返回绑定的地址
  struct sockaddr_in addr {};
  memset(&addr, 0, sizeof(addr));
  socklen_t len = sizeof(addr);
  if (getpeername(fd_, reinterpret_cast<struct sockaddr *>(&addr), &len) ==
      -1) {
    return "";
  }
  // 大端字节序（网路字节序）：整数的高位存储在内存低处，整数的低位存储在内存高处
  // 小端字节序(主机字节序）:与上相反

  // inet_ntoa:从一个网络数为以个ASCII字符串
  std::string ret(inet_ntoa(addr.sin_addr));
  ret += ":";
  ret += std::to_string(htons(addr.sin_port));
  return ret;
}

RC Socket::Create() {
  // TODO(nakulaos): 为fd_创建一个socket

  // 已经分配
  try {
    if (fd_ != -1) {
      throw std::logic_error("Socket already create !!");
    }
  } catch (std::exception &e) {
    std::cerr << "catch:" << e.what() << std::endl;
    return RC_SOCKET_ERROR;
  }

  fd_ = socket(AF_INET, SOCK_STREAM, 0);

  // fd 创建失败
  try {
    if (fd_ == -1) {
      throw std::out_of_range("Failed to create socket!!!");
    }
  } catch (std::exception &e) {
    std::cerr << "catch:" << e.what() << std::endl;
  }

  return RC_SUCCESS;
}

RC Socket::Bind(const char *_ip, uint16_t _port) const {
  // TODO(nakulaos)：fd_ 绑定地址

  // Socket didn't create
  try {
    if (fd_ == -1) {
      throw std::logic_error("Socket didn't create !!");
    }
  } catch (std::exception &e) {
    std::cerr << "catch:" << e.what() << std::endl;
    return RC_SOCKET_ERROR;
  }

  struct sockaddr_in addr {};
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET; // 哪一种类型的地址
  addr.sin_addr.s_addr = inet_addr(_ip);
  addr.sin_port = htons(_port);

  try {
    if (::bind(fd_, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)) == -1) {
      throw std::runtime_error("Socket bind error!!!");
    }
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return RC_SOCKET_ERROR;
  }
  return RC_SUCCESS;
}

RC Socket::Listen()const{
  // TODO(nakulaos):listen the fd_

  // Socket didn't create
  try {
    if (fd_ == -1) {
      throw std::logic_error("Socket didn't create !!");
    }
  } catch (std::exception &e) {
    std::cerr << "catch:" << e.what() << std::endl;
    return RC_SOCKET_ERROR;
  }

  try {
    if (::listen(fd_, SOMAXCONN) ==
        -1) {
      throw std::runtime_error("Socket Listen error!!!");
    }
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return RC_SOCKET_ERROR;
  }

  return RC_SUCCESS;

}

RC Socket::Accept(int &_clnt_fd)const{
    //TODO(nakulaos): accept new socket

    // Socket didn't create
    try {
      if (fd_ == -1) {
        throw std::logic_error("Socket didn't create !!");
      }
    } catch (std::exception &e) {
      std::cerr << "catch:" << e.what() << std::endl;
      return RC_SOCKET_ERROR;
    }

    _clnt_fd = accept(fd_, NULL, NULL);

    try {
      if (_clnt_fd == -1) {
        throw std::runtime_error("Socket Acccept error!!!");
      }
    } catch (std::exception &e) {
      std::cerr << e.what() << std::endl;
      return RC_SOCKET_ERROR;
    }

    return RC_SUCCESS;
}

RC Socket::Connect(const char *_ip, uint16_t _port) const {

  struct sockaddr_in addr {};
  memset(&addr, 0, sizeof(addr));
  addr.sin_family = AF_INET; // 哪一种类型的地址
  addr.sin_addr.s_addr = inet_addr(_ip);
  addr.sin_port = htons(_port);

  try {
    if (::connect(fd_, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr)) ==
        -1) {
      throw std::runtime_error("Socket connected error!!!");
    }
  } catch (std::exception &e) {
    std::cerr << e.what() << std::endl;
    return RC_SOCKET_ERROR;
  }
  return RC_SUCCESS;
}