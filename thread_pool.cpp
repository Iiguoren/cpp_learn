#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <queue>
#include <functional>
class Thread_pool{
public:
    Thread_pool(size_t numOfthreads);  // 构造函数
    ~Thread_pool();  // 析构函数

    template<class F>
    void enqueue(F&& f);  // 配合模板。万能引用，可以传递左值和右值
    void stopThreadPool();

private:
    bool stop = false;  // 作为临界资源只会被获得锁的线程访问
    std::mutex mtx;
    std::condition_variable cv;
    std::vector<std::thread> workers;
    // std::function(void())能够存储、复制和调用任何可以调用的目标，比如普通函数、lambda 表达式、函数对象等。这里调用返回为void的函数
    std::queue<std::function<void()>> tasks;

    void worker();  //任务
};

Thread_pool::Thread_pool(size_t numOfthreads){
    for(int i=0;i<numOfthreads;i++){
    // emplace_back 方法用于在容器末尾直接创建一个对象（这里是线程），避免了额外的拷贝或移动操作。
        workers.emplace_back([this] {this->worker();});
    }
}

Thread_pool::~Thread_pool() {
    stopThreadPool();  // 确保线程池关闭时停止所有线程
}

template<class F>  
void Thread_pool::enqueue(F&& f){  // 万能引用
    std::unique_lock<std::mutex> lock(mtx);
    tasks.emplace(std::forward<F>(f));
    cv.notify_one();  // 唤醒一个线程
}

void Thread_pool::stopThreadPool() {
    {
        std::unique_lock<std::mutex> lock(mtx);
        stop = true;  // 设置停止标志
    }
    cv.notify_all();  // 唤醒所有线程

    // 等待所有线程完成
    for (std::thread& worker : workers) {
       if (worker.joinable()) //唤醒线程后线程自动退出，退出的线程无法join这里让没有退出的线程join否则报错
            worker.join();    // 等待线程结束
    }
}

void Thread_pool::worker(){
    while(true){
       std::function<void()> task;
    {//限制锁的范围
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]{
            return !tasks.empty() || stop;
        });

        if (stop && tasks.empty()) {
            std::cout<<1<<std::endl;
                return;
            }

        // 从任务队列中取出一个任务
        task = std::move(tasks.front());  //front()返回一个左值的引用，通过move转换为右值引用移动资源
        tasks.pop();  // 移除已取出的任务
    }
        task();
    }
}

int main(){
    Thread_pool pool(4);

    for(int i = 0; i<8; i++){
        pool.enqueue([i]{
            std::cout << "Task " << i << " is being processed by thread"
            << std::this_thread::get_id() << std::endl;  // lamba表达式构造一个函数
        });
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));  // 模拟一些延迟
    pool.stopThreadPool();  // 关闭线程池

    return 0;
}