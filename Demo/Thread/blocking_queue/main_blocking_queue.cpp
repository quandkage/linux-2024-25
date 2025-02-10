#include "blocking_queue.h"

int main() {

    Blocking_Queue<int> queue(5);

    std::thread producer([&] {
        for (int i = 0; i < 10; ++i) {
            queue.enqueue(i);
            {
                std::cout << "Produced: " << i << std::endl;
            }
        }
    });

    std::thread consumer([&] {
        for (int i = 0; i < 10; ++i) {
            auto value = queue.dequeue();
            if (value) {
                std::cout << "Consumed: " << value << std::endl;
            }
        }
    });

    producer.join();
    consumer.join();
    return 0;
}
