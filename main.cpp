#pragma once
#include <queue>

class ThreadSafeQueue
{
public:
    void push(int task)
    {
        queue.push(task);
    }

    int pop()
    {
        int task;
        if (!queue.empty())
        {
            task = queue.front();
            queue.pop();
        }

        return task;
    }

private:
    std::queue<int> queue;
};