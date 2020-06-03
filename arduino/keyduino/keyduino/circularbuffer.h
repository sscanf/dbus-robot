#ifndef CIRCULARBUFFER_h
#define CIRCULARBUFFER_h
#include <inttypes.h>

template <typename T, uint16_t Size>
class CircularBuffer {
public:
  enum {
    Empty = 0,
    Half = Size / 2,
    Full = Size,
  };

  CircularBuffer() :
    wp_(buf_), rp_(buf_), tail_(buf_+Size),  remain_(0) {}
  ~CircularBuffer() {}
  void push(T value) {
    *wp_++ = value;
    remain_++;
    if (wp_ == tail_) wp_ = buf_;
  }
  T pop() {
    T result = *rp_++;
    remain_--;
    if (rp_ == tail_) rp_ = buf_;
    return result;
  }
  int remain() const {
    return remain_;
  }

private:
  T buf_[Size];
  T *wp_;
  T *rp_;
  T *tail_;
  uint16_t remain_;
};

#endif
