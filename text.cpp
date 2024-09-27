#include <thread>
#include <iostream>

class A{
public:
    void foo(){
        
        std::cout<<"foo function\nfoo function\n"<<std::endl;
        std::cout<<"foo function\nfoo function\n"<<std::endl;
        std::cout<<"foo function\nfoo function\n"<<std::endl;
    };
};

int main(int argc, char *argv[]){
    A a;
    std::thread thread1(&A::foo, &a);
    
    return 0;
}