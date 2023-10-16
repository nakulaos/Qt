#pragma once

#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <stdexcept>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>
#include "EventLoop.h"

class ThreadPool{
    public:
    explicit ThreadPool(unsigned int _size= std::thread::hardware_concurrency());
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool(ThreadPool &&) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;
    ThreadPool &operator=(ThreadPool &&) = delete;
    ~ThreadPool();

    template<class F,class... Args>
    auto Add(F &&f,Args&&... args)
    ->std::future<typename std::invoke_result<F, Args...>::type>;


    private:
    std::vector<std::thread> workers_;  // 所有线程
    std::queue<std::function<void()>> tasks_; 
    std::mutex  queue_mutex_;
    std::condition_variable cv_;
    std::atomic<bool> stop_{false};
};

template <class F, class... Args>
auto ThreadPool::Add(F &&f, Args &&...args)
    -> std::future<typename std::invoke_result<F, Args...>::type>{
    // 类模板 std::future 提供访问异步操作结果的机制
    // invoke_result_of 返回推导类型
    using return_type = typename std::invoke_result<F,Args...>::type; //return_type是F(Args)的类型
    //
    auto task = std::make_shared<std::packaged_task<return_type()>>
    (std::bind(std::forward<F>(f),std::forward<Args>(args)...));

    std::future<return_type> res = task->get_future();

    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        
        if(stop_){
            throw std::runtime_error("enqueued on stopped ThreadPool");
        }
        
        tasks_.emplace([task]() { (*task)(); });
    }
    cv_.notify_one();
    return res;

}