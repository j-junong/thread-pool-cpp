#pragma once
#include "thread-safe-queue.h"
#include <functional>
#include <vector>
#include <thread>
#include <future>

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
  template <typename T>
  std::future<T> addTask(std::function<T()> task)
  {
    auto wrapper = std::make_shared<std::packaged_task<T()>>(task); // Create a task on the heap
    std::future<T> future = wrapper->get_future(); // Connect wrapper to future
    tasks.push([wrapper] () { (*wrapper)(); }); // Push the task onto the queue
    return future;
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