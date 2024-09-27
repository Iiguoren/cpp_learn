#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void printID(int id){
    std::unique_lock<std::mutex> ul(mtx);  // 自动LOCK
    while(!ready) cv.wait(ul);  // 当ready==false,线程阻塞，释放LOCK,唤醒线程后当线程==true,print
    std::cout<< "thread"<<" "<<id<<std::endl;  // 等待唤醒，打印
}

void go(){
    std::unique_lock<std::mutex> ul(mtx);  // 自动LOCK
    ready = true;  // 复位ready
    cv.notify_one();  // 唤醒一个阻塞的线程/启动一个线程。
}

int main(int argc, char *argv[]){
    std::thread threads[5]; //创建一个元素为thread的数组
    for(int i=0; i<5; i++){
        threads[i] = std::thread(printID, i);
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    go();  // 唤醒所有线程

    for (auto& th : threads) th.join();  // 等待所有线程
    return 0;
}