#pragma once
#include <queue>
#include <optional>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue
{
public:
  // Pushes a task into the queue
  void push(T task)
  {
    std::lock_guard<std::mutex> guard(lock); // Grab lock before pushing a task
    queue.push(task);
    cv.notify_one(); // Wakes a thread after pushing a task
  }

  // Removes a task from the front of the queue
  std::optional<T> pop()
  {

    std::lock_guard<std::mutex> guard(lock); // Grab lock before checking for tasks
    if (!queue.empty())
    {
      T task;
      task = queue.front();
      queue.pop();
      return task;
    }
    return std::nullopt; // Return this if there is nothing in queue
  }

  std::optional<T> waitForTask()
  {
    std::unique_lock<std::mutex> guard(lock); // Allows the release of the lock mid scope
    cv.wait(guard, [this]
            { return stopped || !queue.empty(); }); // Puts a thread to sleep until there is a task
    if (!stopped)                                   // If thread wakes up not from shutting down
    {
      T task = queue.front();
      queue.pop();
      return task;
    }
    return std::nullopt;
  }

  void stopWaiting()
  {
    std::lock_guard<std::mutex> guard(lock);
    stopped = true;
    cv.notify_all();
  }

private:
  std::queue<T> queue;
  std::mutex lock;
  std::condition_variable cv;
  bool stopped = false;
};