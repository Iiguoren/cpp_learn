## char*与char[]的区别
### char * 这种方式表示常量指针，char[] 这种表示指针常量
```cpp
void charcode() {
    char* a = "c1";
    *(a+1) = '2';
    cout<<a<<endl;
}

```
*char* 指向内容固定*
上面代码会报错`/bin/sh: line 1: 48910 Bus error: 10 `,此操作声明了一个指向char常量的指针a。在内存常量区分配了一个字符串常量"c1"，返回这个字符常量的地址给a。
由于"c1"是字符串常量，所以其内容无法修改，*(a+1)试图修改字符串第二个值为，所以失败。
```cpp
void charcode() {
    char* a = "c1";
    a = "c2";
    printf("a=%s", a);
}
```
但a是个指针变量，所以可以对a解引用重新更改指向对象。


对于字符串char[]:
```cpp
char str[6] = {"hello"};
```
声明了一个char类型数组str,对数组每一位赋值多余用'/0'，补上。
*数组长度声明就已经固定*
```cpp
 char str[6] = {"hello"};
 str = "world";
```
str指向的数组地址不能发生变化,上述代码报错。但是数组内的字符可以修改；
```cpp
void charcode() {
    char str[6] = {"hello"};
    str[0] = 'H';
    cout<<str<<endl;
}
```
