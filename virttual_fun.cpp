#include <iostream>
using namespace std;
class A
{
    void fun1() {};
    void fun2() {};
    virtual void vfunc() {};
};
A a;

int main(int argc, char* argv[]){
    cout<<"sizeof(a)="<<sizeof(a)<<endl;
}