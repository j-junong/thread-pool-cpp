#include <iostream>
#include <thread>
#include "thread-safe-queue.h"

int main()
{
    ThreadSafeQueue test;

    std::thread producer([&test]()
                         {
                             test.push(1);
                             test.push(2);
                             test.push(3);
                             std::cout << "Producer pushed 3 tasks" << std::endl;
                         });

    std::thread consumer([&test]()
                         {
        for (int i{}; i < 3; ++i) {
            std::optional<int> task = test.waitForTask();
            if (task.has_value()) std::cout << "Consumer got task: " << task.value() << std::endl;
        } });

    producer.join();
    consumer.join();

    return 0;
}