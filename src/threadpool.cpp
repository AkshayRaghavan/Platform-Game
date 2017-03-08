#include "threadpool.h"
#include <QDebug>
#include <QThread>

ThreadPool::ThreadPool(int number_of_threads = 0)
{
    if(number_of_threads <= 0)
    {
        number_of_threads = std::thread::hardware_concurrency();
    }
    numberOfThreads = number_of_threads;
    for(int i = 0; i < number_of_threads; i++)
    {
        threadWorkers.push_back(std::thread(&ThreadPool::waitOrWork,this,i));
    }
    isWaiting = false;
}

void ThreadPool::addThread()
{
    numberOfThreads++;
    threadWorkers.push_back(std::thread(&ThreadPool::waitOrWork,this,numberOfThreads-1));
}

void ThreadPool::assignToThread(std::function<void()> function_with_work)
{
    if(isWaiting)
    {
        std::unique_lock<std::mutex> queueEmptyLock(queueEmptyMutex);
        isWaitingForQueue.wait(lock,[](){ return isWaiting });
    }
    std::unique_lock<std::mutex> lock(mutexForQueue);
    functionsWaitingToBeExecuted.push(function_with_work);
    isWorkAvailable.notify_one();
}

void ThreadPool::waitOrWork(int i)
{
    int id = i;
    while(true)
    {
        std::unique_lock<std::mutex> lock(mutexForQueue);
        isWorkAvailable.wait(lock, [&](){ return !functionsWaitingToBeExecuted.empty(); });
        std::function<void()> work_to_do = functionsWaitingToBeExecuted.front();
        functionsWaitingToBeExecuted.pop();
        if(isWaiting && functionsWaitingToBeExecuted.empty())
        {
            waiter.notify_all();
        }
        qDebug() << "function assigned to thread " << id;
        work_to_do();
    }
}

void ThreadPool::waitTillAllComplete()
{
    std::unique_lock<std::mutex> queueEmptyLock(queueEmptyMutex);
    isWaiting = false;
    //waiter waits till it is woken up when queue is empty
    //notifies assigntothreads to continue

}

ThreadPool::~ThreadPool()
{
    for(int i = 0; i < numberOfThreads; i++)
    {
        threadWorkers[i].join();
    }
}
