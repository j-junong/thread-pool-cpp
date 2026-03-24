#pragma once
#include "thread-safe-queue.h"
#include <functional>
#include <vector>
#include <thread>

class ThreadPool
{
private:
  ThreadSafeQueue<std::function<void()>> tasks;
  std::vector<std::thread> threads;
};