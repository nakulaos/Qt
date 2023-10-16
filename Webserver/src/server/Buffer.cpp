#include "Buffer.h"
#include <cstddef>
#include <string_view>

const std::string &Buffer::GetBuf() const { return buf_; }

const char *Buffer::CStr() const { return buf_.c_str(); }

void Buffer::SetBuf(std::string_view _sv) { buf_ = _sv; }

size_t Buffer::Size() const { return buf_.size(); }

void Buffer::Append(std::string_view sv,int _size) {
    for(int i=0;i<_size;i++){
        buf_+=sv[i];
    }
}

void Buffer::Clear() { buf_.clear(); }