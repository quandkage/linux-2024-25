#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template <class T>
class BlockingQueue
{
private:
    std::mutex m_mtx;
    std::condition_variable m_cv;
    std::queue<T> m_buff;
    const std::size_t m_maxSize = 0;

public:
    explicit BlockingQueue(std::size_t maxSize);
    ~BlockingQueue();

    BlockingQueue(BlockingQueue&&) noexcept;
    BlockingQueue& operator=(BlockingQueue&&) noexcept;

    BlockingQueue(const BlockingQueue&) = delete;
    BlockingQueue& operator=(const BlockingQueue&) = delete;

    void push(const T& obj);
    void push(T&& obj);

    bool try_push(const T& obj);
    bool try_push(T&& obj);

    T pop();
    bool try_pop(T& obj);

    bool empty();
};

#include "BlockingQueue.hpp"

#endif //BlockingQueue_H
