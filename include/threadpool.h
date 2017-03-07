#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>


class ThreadPool
{
    int numberOfThreads;
    std::vector<std::thread> threadWorkers;
    std::queue<std::function<void()> > functionsWaitingToBeExecuted;
    std::mutex mutexForQueue;
    std::unique_lock<std::mutex> lock;
    std::condition_variable isWorkAvailable;
public:
    ThreadPool(int);
    void addThread();
    void assignToThread(std::function<void()>);
    void waitOrWork(int i);
    ~ThreadPool();
};

#endif // THREADPOOL_H
