#include "BlockingQueue.h"

template <typename T>
void consumer(BlockingQueue<T>& kuyeuye)
{
    int count = 0;
    while (count < 10) {
        int value;
        if (kuyeuye.try_pop(value)) {
            std::cout << "Consumed: " << value << std::endl;
            ++count;
        } else if (kuyeuye.empty()) {
            break;
        }
        else {
            std::this_thread::yield();
        }
    }
}

template <typename T>
void producer(BlockingQueue<T>& kuyeuye)
{
    for (int i = 0; i < 10; ++i) {
        if (kuyeuye.try_push(i)) {
            std::cout << "Produced: " << i << std::endl;
        }
    }
}

int main() {

    BlockingQueue<int> queue(5);

    std::thread producerThread([&] {
        producer(queue);
    });

    std::thread consumerThread([&] {
        consumer(queue);
    });

    producerThread.join();
    consumerThread.join();
    return 0;
}
