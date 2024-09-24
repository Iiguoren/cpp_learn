#include "iostream"

class Basic{
public:
    Basic();
    virtual ~Basic();
private:
    void *buf;
};

Basic::Basic(): buf(std::malloc(16)) {}
Basic::~Basic() {
    std::free(buf);
    std::cout<<"basic"<<std::endl;
    }

// 第一个子类
class Child : public Basic{
public:
    Child();
    ~Child();
private:
    void *chbuf;    
};

Child::Child():Basic(), chbuf(std::malloc(8)) {}
Child::~Child() {
    std::free(chbuf);
    std::cout<<"child"<<std::endl;
}

// 第二个子类
class Child2 : public Basic{
public:
    Child2();
    ~Child2();
private:
    void *ch2buf;    
};

Child2::Child2():Basic(), ch2buf(std::malloc(8)) {}
Child2::~Child2() {
    std::free(ch2buf);
    std::cout<<"child2"<<std::endl;
    }

Basic *creat(int num){
    if(num==1)
        return new Child;
    if(num==2)
        return new Child2;
}

void destroy(Basic *b){
    delete b;
}

int main(int argc, char *argv[]){
    auto b = creat(1);
    destroy(b);
}