#include <iostream>
#include <thread>
#include "thread-safe-queue.h"
#include "thread-pool.h"

int main()
{
    ThreadPool pool(4);
    auto future = pool.addTask<int>([]() { return 4 + 2; });
    std::cout << future.get() << std::endl;
    
    return 0;
}