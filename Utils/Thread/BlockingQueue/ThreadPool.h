#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <functional>
#include <future>
#include <thread>
#include <vector>
#include <memory>
#include "BlockingQueue.h"

class ThreadPool {
private:
    std::vector<std::thread> m_threads;
    BlockingQueue<std::function<void()>>* m_tasks;
    std::atomic<bool> m_stop;
    std::size_t m_count;

public:
    ThreadPool()
        : m_tasks(BlockingQueue<std::function<void()>>::create(std::thread::hardware_concurrency())),
          m_stop(false),
          m_count(std::thread::hardware_concurrency())
    {
        for (size_t i = 0; i < m_count; ++i) {
            m_threads.emplace_back([this] {
                while (!m_stop.load()) {
                    std::function<void()> task;
                    if (m_tasks->try_pop(task)) {
                        task();
                    } else {
                        std::this_thread::yield();
                    }
                }
            });
        }
    }

    ~ThreadPool()
    {
        m_stop.store(true);

        for (size_t i = 0; i < m_count; ++i) {
            m_tasks->push([]() { std::this_thread::sleep_for(std::chrono::milliseconds(1)); });
        }

        for (auto& t : m_threads) {
            if (t.joinable()) {
                t.join();
            }
        }
    }

    template <class F, class... Args>
auto enqueue(F&& f, Args&&... args)
    {
        using return_type = std::invoke_result_t<F, Args...>;

        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
            );

        auto future = task->get_future();

        m_tasks->push([task]() {
          (*task)();
        });

        return future;
    }
};

#endif //THREADPOOL_HPP
