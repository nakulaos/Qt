#include <functional>
#include <mutex>
#include <thread>
#include "ThreadPool.h"

ThreadPool::ThreadPool(unsigned int _size) : stop_(false) {
    for (unsigned int i = 0; i < _size; i++) {
        workers_.emplace_back(
            // lamada表达式
            [this]() {
                while (true) {
                    std::function<void()> task;
                    {
                        // 单有互斥体是没有用的，还要有锁
                        // 在这个{}作用域内对std::mutex加锁，出了作用域会自动解锁，不需要调用unlock()
                        std::unique_lock<std::mutex> lock(queue_mutex_);
                        cv_.wait(lock, [this]() {
                            // 等待条件变量，条件为任务队列不为空或线程池停止
                            return stop_ || !tasks_.empty();
                        });
                        if (stop_ && tasks_.empty()) {
                            // //任务队列为空并且线程池停止，退出线程
                            return;
                        }

                        //  // 从任务队列头取出一个任务
                        task = tasks_.front();
                        tasks_.pop();
                    }
                    task();
                }
            });
    }
}

ThreadPool::~ThreadPool(){
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        stop_ = true;
    }
    cv_.notify_all();

    for(std::thread& th:workers_){
        if(th.joinable()){
            th.join();
        }
    }
}