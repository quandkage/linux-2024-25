#ifndef BLOCKING_QUEUE_CPP
#define BLOCKING_QUEUE_CPP

#include "blocking_queue.h"

template <typename T>
Blocking_Queue<T>::Blocking_Queue(std::size_t maxSize): m_maxSize(maxSize) {}

template <typename T>
void Blocking_Queue<T>::enqueue(const T &obj) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this] {
        return buff.size() < m_maxSize;
    });
    buff.push(obj);
    cv.notify_one();
}

template<class T>
T Blocking_Queue<T>::dequeue() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [this]{
        return !buff.empty();
    });
    T poped = buff.front();
    buff.pop();
    cv.notify_one();
    return poped;
}

void consumer(Blocking_Queue<int>& kuyeuye) {
    for (int i = 0; i < 15; ++i) {
        kuyeuye.enqueue(i);
    }
}

void producer(Blocking_Queue<int> &kuyeuye) {
    for (int i = 0; i < 15; ++i) {
        kuyeuye.dequeue();
    }
}

#endif
