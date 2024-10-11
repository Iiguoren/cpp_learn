#include <thread>
#include <mutex>
#include <iostream>

int a = 0;
std::mutex mtx;
void func(){
    for(int i = 0; i<20000; i++){
        mtx.lock();
        a+=1;
        mtx.unlock();
    }
}

int main(int argc, char *argv[]){
    std::thread thread1(func);
    std::thread thread2(func);

    thread1.join();
    thread2.join();

    std::cout<< a << std::endl;

    return 0;
}