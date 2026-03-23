#include <iostream>
#include "thread-safe-queue.h"

int main()
{
    ThreadSafeQueue test;

    test.push(2);
    test.push(5);
    test.push(1);

    std::cout << test.pop().value();

    return 0;
}