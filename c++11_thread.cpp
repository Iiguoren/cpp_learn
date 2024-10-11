#include <iostream>
#include <thread>
#include <string>
void printhelloworld(std::string msg){
    std::cout<<msg<<std::endl;
    return;
}

int main(int argv, char *argc[]){
    std::thread thread1(printhelloworld, "hello thread");
    thread1.join();
    return 0;
}

