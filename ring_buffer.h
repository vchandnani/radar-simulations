#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <vector>
#include <memory>
#include <mutex>

template <typename T>
class RingBuffer {
public:
    explicit RingBuffer(size_t size);
    ~RingBuffer() = default;

    void push(T item);
    T pop();
    
    bool empty() const;
    bool full() const;
    size_t size() const;
    size_t capacity() const;

private:
    std::unique_ptr<T[]> buffer_;
    size_t head_ = 0; // write pointer
    size_t tail_ = 0; // read pointer
    size_t max_size_;
    bool full_ = false;
    mutable std::mutex mutex_; // makes this thread-safe
};

#include "ring_buffer.cpp"

#endif // RING_BUFFER_H