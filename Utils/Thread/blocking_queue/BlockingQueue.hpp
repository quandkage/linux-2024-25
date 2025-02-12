#ifndef BLOCKING_QUEUE_HPP
#define BLOCKING_QUEUE_HPP

template <typename T>
BlockingQueue<T>::BlockingQueue(const std::size_t maxSize)
    : m_maxSize(maxSize) {}

template <typename T>
BlockingQueue<T>::BlockingQueue(BlockingQueue&& other) noexcept
    : m_maxSize(other.m_maxSize)
{
    std::lock_guard<std::mutex> lock(other.m_mtx);
    m_buff = std::move(other.m_buff);
}

template <typename T>
BlockingQueue<T>& BlockingQueue<T>::operator=(BlockingQueue&& other) noexcept
{
  if (this != &other){
      std::lock_guard<std::mutex> lockThis(m_mtx);
      std::lock_guard<std::mutex> lockOther(other.m_mtx);

      m_buff = std::move(other.m_buff);
  }
  return *this;
}

template <typename T>
BlockingQueue<T>::~BlockingQueue()
{
    std::lock_guard<std::mutex> lock(m_mtx);
    while (!m_buff.empty()) {
        m_buff.pop();
    }

    m_cv.notify_all();
}

template <typename T>
void BlockingQueue<T>::push(const T &obj)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    m_cv.wait(lock, [this] { return m_buff.size() < m_maxSize; });

    m_buff.push(obj);

    lock.unlock();
    m_cv.notify_one();
}

template <typename T>
void BlockingQueue<T>::push(T&& obj)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    m_cv.wait(lock, [this] { return m_buff.size() < m_maxSize; });

    m_buff.push(std::move(obj));

    lock.unlock();
    m_cv.notify_one();
}

template <typename T>
bool BlockingQueue<T>::try_push(const T& obj)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    if (m_buff.size() >= m_maxSize) {
      std::cout << "try_push faild \n";
      return false;
    }
    m_buff.push(obj);
    std::cout << "try_push: " << obj << "\n";

    lock.unlock();
    m_cv.notify_one();

    return true;
}

template <typename T>
bool BlockingQueue<T>::try_push(T&& obj)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    if (m_buff.size() >= m_maxSize) {
      std::cout << "try_push faild \n";
      return false;
    }
    m_buff.push(std::move(obj));

    lock.unlock();
    m_cv.notify_one();

    return true;
}

template <typename T>
T BlockingQueue<T>::pop()
{
    std::unique_lock<std::mutex> lock(m_mtx);
    m_cv.wait(lock, [this] { return !m_buff.empty(); });

    T poped = m_buff.front();
    m_buff.pop();
    std::cout << "pop: " << poped << "\n";

    lock.unlock();
    m_cv.notify_one();

    return poped;
}

template <typename T>
bool BlockingQueue<T>::try_pop(T &obj)
{
    std::unique_lock<std::mutex> lock(m_mtx);
    if (m_buff.empty()) {
      std::cout << "try_pop failed \n";
      return false;
    }

    obj = std::move(m_buff.front());
    m_buff.pop();
    std::cout << "try_pop: " << obj << "\n";

    lock.unlock();
    m_cv.notify_one();

    return true;
}

template <typename T>
bool BlockingQueue<T>::empty()  {
    std::lock_guard<std::mutex> lock(m_mtx);
    return m_buff.empty();
}

#endif
