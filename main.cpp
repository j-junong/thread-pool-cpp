#include <iostream>
#include <thread>
#include "thread-safe-queue.h"
#include "thread-pool.h"

int main()
{
    ThreadPool pool(4);
    pool.addTask([]() { std::cout << "Task 1 executed" << std::endl; });
    pool.addTask([]() { std::cout << "Task 2 executed" << std::endl; });
    pool.addTask([]() { std::cout << "Task 3 executed" << std::endl; });
    pool.addTask([]() { std::cout << "Task 4 executed" << std::endl; });
    pool.addTask([]() { std::cout << "Task 5 executed" << std::endl; });
    pool.addTask([]() { std::cout << "Task 6 executed" << std::endl; });
    pool.addTask([]() { std::cout << "Task 7 executed" << std::endl; });
    pool.addTask([]() { std::cout << "Task 8 executed" << std::endl; });

    return 0;
}