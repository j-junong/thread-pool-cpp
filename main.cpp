#include <iostream>
#include "thread-safe-queue.h"

int main()
{
    ThreadSafeQueue test;

    test.push(2);
    test.push(5);
    test.push(1);

    int result = test.waitForTask();
    std::cout << result << std::endl;

    result = test.waitForTask();
    std::cout << result << std::endl;

    result = test.waitForTask();
    std::cout << result << std::endl;

    return 0;
}