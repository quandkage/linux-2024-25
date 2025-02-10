#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template <class T>
class Blocking_Queue
{
private:
    std::mutex mtx;
    std::condition_variable cv;
    std::queue<T> buff;
    std::size_t m_maxSize = 0;

public:
    explicit Blocking_Queue(std::size_t maxSize);

    void enqueue(const T& obj);
    T dequeue();
};

#include "blocking_queue.cpp"

#endif //BLOCKING_QUEUE_H
