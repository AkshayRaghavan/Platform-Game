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
    std::vector<bool> threadStatus;
    std::queue<std::function<void()> > functionsWaitingToBeExecuted;
    std::mutex mutexForQueue;
    std::condition_variable isWorkAvailable;
    std::mutex queueEmptyMutex;
    std::condition_variable isWaitingForQueue;
    std::condition_variable waiter;
    std::mutex waiterMutex;
    bool isWaiting;
    bool stopNow;
public:
    ThreadPool(int);
    void addThread();
    void assignToThread(std::function<void()>);
    void waitOrWork(int i);
    ~ThreadPool();
    void waitTillAllComplete();
};

#endif // THREADPOOL_H
