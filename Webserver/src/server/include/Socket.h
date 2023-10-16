#pragma once

#include "common.h"
#include <cstdint>
#include <string>
#include <sys/types.h>

class Socket {
public:
  Socket();
  Socket(const Socket &) = delete;
  Socket(Socket &&) = delete;
  Socket &operator=(const Socket &) = delete;
  Socket &operator=(Socket &&) = delete;
  ~Socket();

  void SetFd(int _fd);
  int GetFd();
  std::string GetAddr();

  RC Create();
  RC Bind(const char *_ip, uint16_t _port) const;
  [[nodiscard]] RC Listen() const;
  RC Accept(int &clnt_fd) const;
  RC Connect(const char *_ip, uint16_t _port) const;
  [[nodiscard]] RC SetNonBlocking() const;
  [[nodiscard]] bool IsNonBlocking() const;
  [[nodiscard]] ssize_t RecvBufSize() const;

private:
  int fd_;
};