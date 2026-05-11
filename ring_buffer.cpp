#include "ring_buffer.h"

template <typename T>
RingBuffer<T>::RingBuffer(size_t size) 
    : buffer_(std::unique_ptr<T[]>(new T[size])), max_size_(size) {}

template <typename T>
void RingBuffer<T>::push(T item) {
    std::lock_guard<std::mutex> lock(mutex_);
    buffer_[head_] = item;

    if (full_) {
        tail_ = (tail_ + 1) % max_size_;
    }

    head_ = (head_ + 1) % max_size_;
    full_ = head_ == tail_;
}

template <typename T>
T RingBuffer<T>::pop() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (empty()) {
        throw std::runtime_error("Buffer is empty");
    }

    T val = buffer_[tail_];
    full_ = false;
    tail_ = (tail_ + 1) % max_size_;
    return val;
}

template <typename T>
bool RingBuffer<T>::empty() const {
    return (!full_ && (head_ == tail_));
}

template <typename T>
bool RingBuffer<T>::full() const {
    return full_;
}

template <typename T>
size_t RingBuffer<T>::size() const {
    size_t size = max_size_;
    if (!full_) {
        if (head_ >= tail_) {
            size = head_ - tail_;
        } else {
            size = max_size_ + head_ - tail_;
        }
    }
    return size;
}

template <typename T>
size_t RingBuffer<T>::capacity() const {
    return max_size_;
}