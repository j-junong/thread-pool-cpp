#pragma once
#include "thread-safe-queue.h"
#include <functional>
#include <vector>
#include <thread>

class ThreadPool
{
public:
  ThreadPool(int numThreads)
  {
    // Creates worker threads
    for (int i{}; i < numThreads; ++i)
    {
      threads.push_back(std::thread([this]() {
          while (true) {
            std::optional<std::function<void()>> task = tasks.waitForTask(); // Returns nullopt when shut down
            if (task.has_value()) task.value()();  // Executes the function by calling 
            else return;
          } 
        }
      ));
    }
  }

  // Adds task into the queue and wakes a thread
  void addTask(std::function<void()> task)
  {
    tasks.push(std::move(task));
  }

  ~ThreadPool()
  {
    tasks.stop(); //Main thread calls this
    for (auto &thread : threads)
    {
      thread.join();  // Wait for all threads to finish before shutting down
    }
  }

private:
  ThreadSafeQueue<std::function<void()>> tasks;
  std::vector<std::thread> threads;
};