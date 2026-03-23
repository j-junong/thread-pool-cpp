#pragma once
#include <queue>
#include <optional>
#include <mutex>

class ThreadSafeQueue
{
public:
  // Pushes a task into the queue
  void push(int task)
  {
    queue.push(task);
  }

  // Removes a task from the front of the queue
  std::optional<int> pop()
  {
    int task;
    if (!queue.empty())
    {
      task = queue.front();
      queue.pop();
      return task;
    }

    return std::nullopt; // Return this if there is nothing in queue
  }

private:
  std::queue<int> queue;
  std::mutex lock;
};