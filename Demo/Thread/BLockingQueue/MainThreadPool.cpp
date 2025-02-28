#include <iostream>
#include <ThreadPool.h>


int task1(int a, int b) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return a + b;
}

int main() {
    ThreadPool pool;

    auto future1 = pool.enqueue(task1, 10, 20);
    auto future2 = pool.enqueue(task1, 30, 40);

    std::cout << "Result of task 1: " << future1.get() << std::endl;
    std::cout << "Result of task 2: " << future2.get() << std::endl;

    return 0;
}