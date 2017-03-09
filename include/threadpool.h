#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>

/*!
 * \brief Thread Pool to allot work concurrently
 * Handles the creation of threads, assigns work, and handles wait till all threads complete execution
 */

class ThreadPool
{
    /*!
     * \brief number of threads in the thread pool
     */
    int numberOfThreads;

    /*!
     * \brief Stores all the threads
     */
    std::vector<std::thread> threadWorkers;

    /*!
     * \brief Stores whether each thread is running or not - true if yes, false if no
     */
    std::vector<bool> threadStatus;

    /*!
     * \brief Stores a queue of functions waiting for a thread to execute
     */
    std::queue<std::function<void()> > functionsWaitingToBeExecuted;

    /*!
     * \brief Mutex to protect access to the queue
     */
    std::mutex mutexForQueue;

    /*!
     * \brief condition variable on which threads wait till work is available
     */
    std::condition_variable isWorkAvailable;

    /*!
     * \brief Mutex on which threads hold when they wait till queue is empty
     */
    std::mutex queueEmptyMutex;

    /*!
     * \brief condition variable on which threads wait till queue is empty
     */
    std::condition_variable isWaitingForQueue;

    /*!
     * \brief condition variable on which the thread pool waits till queue is empty
     */
    std::condition_variable waiter;

    /*!
     * \brief Mutex held by waiter
     */
    std::mutex waiterMutex;

    /*!
     * \brief Stores whether the thread pool is waiting for all threads to complete
     */
    bool isWaiting;

    /*!
     * \brief Stores whether all threads have been ordered to exit after completing their tasks
     */
    bool stopNow;
public:
    /*!
     * \brief Constructor
     * \param number_of_threads the number of threads in the thread pool
     */
    ThreadPool(int number_of_threads);

    /*!
     * \brief Adds a thread to the thread pool
     */
    void addThread();

    /*!
     * \brief Puts function in the queue waiting for a thread to execute
     * \param function_to_execute the function to be executed
     */
    void assignToThread(std::function<void()> function_to_execute);

    /*!
     * \brief function run by each thread that waits till work is available in the queue, and executes it
     * \param i the ID of the thread
     */
    void waitOrWork(int i);

    /*!
     * \brief Destructor
     */
    ~ThreadPool();

    /*!
     * \brief Wait till all current threads complete their current tasks
     */
    void waitTillAllComplete();
};

#endif // THREADPOOL_H
