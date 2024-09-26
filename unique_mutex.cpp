#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>
int a = 0;

std::timed_mutex mtx;

void func(){
    for(int i = 0; i<2; i++){
        std::unique_lock<std::timed_mutex> um(mtx, std::defer_lock);
        if(um.try_lock_for(std::chrono::seconds(2))){
            std::this_thread::sleep_for(std::chrono::seconds(2));
            a++;
        }
    }
}
int main(){
    std::thread t1(func);
    std::thread t2(func);
    t1.join();
    t2.join();

    std::cout<<a<<std::endl;
    return 0;
}
