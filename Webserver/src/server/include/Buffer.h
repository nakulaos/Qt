#pragma once

#include <cstddef>
#include <string>
#include <string_view>

class Buffer {
public:
  Buffer() = default;
  Buffer(const Buffer &) = delete;
  Buffer(Buffer &&) = delete;
  Buffer &operator=(const Buffer &) = delete;
  Buffer &operator=(Buffer &&) = delete;
  ~Buffer() = default;

  [[nodiscard]] const std::string &GetBuf() const;
  [[nodiscard]] const char *CStr() const;

  void SetBuf(std::string_view _sv);

  [[nodiscard]] size_t Size() const;
  void Append(std::string_view _sv,int _size);
  void Clear();

private:
  std::string buf_;
};