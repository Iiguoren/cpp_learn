## templete关键字
template <typename T> 声明了一个模板，T 是一个占位符，表示某种数据类型。在调用函数模板时编译器会根据传入参数生成具体的函数实例。

对于一个返回最大值函数的不同参数类型：
```cpp
int max(int a, int b){
    a>b?a:b;
}

double max(double a, double b){
    a>b?a:b;
}
```
可使用函数模板：
```cpp
template<class T>
T max(T a, T b){
    a>b?a:b;
}

void main(){
    int a = 10;
    int b = 8;
    std::cout<<max(a,b)<<std::endl;  // a,b都是int型返回a
    double da = 9.8;
    double db = 6.8;               
    std::cout<<max(da,db)<<std::endl;  //a,b都是double型返回a
------------------------------------
10
9.8
------------------------------------
}
```
但是如果是
`std::cout<<max(da,b)<<std::endl;`
报错：`no matching function for call to 'max(int&, double&)'`,因为编译器无法推断出模板类型T的值，这里增加double关键字
`std::cout<<max<double>(da,db)<<std::endl;`来表明生成double类型的函数实例，传递的浮点型会被转换为浮点型。

上述的函数实例化称之为隐式实例化，函数模板也可以显示实例化。例如：
`templete float max(float a, float b);`类似于函数声明加上关键字。

函数模板也可以有多个类型参数:
```
template<class T1, class T2>
T2 max(T1 a, T2 b){
    a>b:a?b;
}
```
函数模板也可以有重载:
```
template<class T1, class T2>
T2 max(T1 a, T2 b){
    a>b:a?b;
}

template<class T1, class T2， class T3>
T2 max(T1 a, T2 b, T3 c){
    a>(c>b:c?b):a?(c>b:c?b);
}
```