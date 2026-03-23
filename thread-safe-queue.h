#pragma once
#include <queue>
#include <optional>
#include <mutex>
#include <condition_variable>

class ThreadSafeQueue
{
public:
  // Pushes a task into the queue
  void push(int task)
  {
    std::lock_guard<std::mutex> guard(lock); // Grab lock before pushing a task
    queue.push(task);
    cv.notify_one(); // Wakes a thread after pushing a task
  }

  // Removes a task from the front of the queue
  std::optional<int> pop()
  {

    std::lock_guard<std::mutex> guard(lock); // Grab lock before checking for tasks
    if (!queue.empty())
    {
      int task;
      task = queue.front();
      queue.pop();
      return task;
    }
    return std::nullopt; // Return this if there is nothing in queue
  }

  int waitForTask()
  {
    std::unique_lock<std::mutex> guard(lock); // Allows the release of the lock mid scope
    cv.wait(guard, [this]
            { return !queue.empty(); }); // Puts a thread to sleep until there is a task
    int task = queue.front();
    queue.pop();
    return task;
  }

private:
  std::queue<int> queue;
  std::mutex lock;
  std::condition_variable cv;
};