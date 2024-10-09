#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

class Thread_pool{
public:
    Thread_pool(size_t numOfthreads);  // 构造函数
    ~Thread_pool();  // 析构函数

    template<class F>
    void enqueue(F&& f);  // 配合模板。万能引用，可以传递左值和右值
    void stopThreadPool();

private:
    bool stop = false;
    std::mutex mtx;
    std::condition_variable cv;
    std::vector<std::thread> = workers;
    // std::function(void())能够存储、复制和调用任何可以调用的目标，比如普通函数、lambda 表达式、函数对象等。这里调用返回为void的函数
    std::queue<std::function(void())> tasks;

    void worker();
}

ThreadPool::Thread_pool(size_t numOfthreads){
    for(i=0;i<numOfthreads;i++){
    // emplace_back 方法用于在容器末尾直接创建一个对象（这里是线程），避免了额外的拷贝或移动操作。
        workers.emplace_back([this] {this->worker();});
    }
}