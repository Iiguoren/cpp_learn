#include <iostream>

template<class T>
T max(T a, T b){
    a>b?a:b;
}

int main(){
    int a = 10;
    int b = 8;
    std::cout<<max(a,b)<<std::endl;  // a,b都是int型返回a
    double da = 9.8;
    double db = 6.8;               
    std::cout<<max(da,db)<<std::endl;  //a,b都是double型返回a
    return 0;
}