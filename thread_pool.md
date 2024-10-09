```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

class ThreadPool {
public:
    ThreadPool(size_t numThreads);
    ~ThreadPool();

    // 向任务队列添加任务
    template<class F>
    void enqueue(F&& f);

    void stopThreadPool();

private:
    std::vector<std::thread> workers;  // 工作线程
    std::queue<std::function<void()>> tasks;  // 任务队列

    std::mutex mtx;
    std::condition_variable condition;
    bool stop = false;

    void worker();  // 工作线程执行的函数
};

ThreadPool::ThreadPool(size_t numThreads) {
    for (size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back([this] { this->worker(); });
    }
}

ThreadPool::~ThreadPool() {
    stopThreadPool();  // 确保线程池关闭时停止所有线程
}

template<class F>
void ThreadPool::enqueue(F&& f) {
    {
        std::unique_lock<std::mutex> lock(mtx);
        tasks.emplace(std::forward<F>(f));  // 添加任务到队列
    }
    condition.notify_one();  // 唤醒一个线程
}

void ThreadPool::stopThreadPool() {
    {
        std::unique_lock<std::mutex> lock(mtx);
        stop = true;  // 设置停止标志
    }
    condition.notify_all();  // 唤醒所有线程以便它们能够退出
    for (std::thread& worker : workers) {
        worker.join();  // 等待所有线程完成工作
    }
}

void ThreadPool::worker() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(mtx);
            condition.wait(lock, [this] {
                return !tasks.empty() || stop;  // 等待直到有任务或停止信号
            });

            // 如果停止标志已设置并且任务队列为空，退出线程
            if (stop && tasks.empty()) {
                return;
            }

            task = std::move(tasks.front());  // 从队列中取出一个任务
            tasks.pop();  // 移除已取出的任务
        }

        task();  // 执行任务
    }
}

int main() {
    ThreadPool pool(4);  // 创建包含4个线程的线程池

    // 向线程池添加任务
    for (int i = 0; i < 8; ++i) {
        pool.enqueue([i] {
            std::cout << "Task " << i << " is being processed by thread "
                      << std::this_thread::get_id() << std::endl;
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));  // 模拟一些延迟
    pool.stopThreadPool();  // 关闭线程池

    return 0;
}



```