# iostream
## 标准库中的头文件与对象

* 类型是对数据的抽象描述，用于定义数据的性质、存储方式、操作规则等。
* 对象是类型的实例，是在程序运行时实际占据内存的实体。

标准库中有三个头文件，iostream.h,fstream.h,sstream,h;
iostream.h中定义了从流(stream)中读取数据的六个类型；
fstream中定义了从文件中读取数据的六个类型；
sstream中定义了从内存的string中读取数据的六个类型，见下表。
|头文件|类型|
|-----|----|
|iostream|istream, wistream从流读取数据|
||ostream, wostream 向流写入数据|
||iostream, wiostream 读写流|
|fstream|ifstream, wifstream从文件读取数据|
||ofstream,wofstream从文件总写入数据|
||iofstream,wiofstream读写文件|
|sstream|istringstream,wistringstream从string中读取数据|
||ostringstream,wostringstream向string中写入数据|
||stringstream,wstringstream读写string数据|
w开头的类型是用来读取宽字符类型wchar_t。

不同io类型是通过继承机制实现的。ifstream和istringstream都是继承自istream。因此可以用ifstream和istringstream来读写流的数据。
同理，类型ofstream和ostringstream都继承自ostream。
* io对象不能拷贝和赋值

* >>是“提取运算符”（extraction operator），用于从流中提取数据。所以当你使用istringstream时，>>表示“从这个流中提取数据”。

* <<运算符相反，它是“插入运算符”（insertion operator），用于将数据插入到流中，比如向cout插入数据。

## istream/ostream输入输出流
输入输出流对象为cin/cout。这是标准库内置的对象不用重新创建。
```cpp
int a = 10;
std::cout<<a<<std::endl;
# endl相当于换行符
return 0;
```
使用<<插入操作符将数据发送到输出流；>>提取操作符用于从输入流独取数据。
### 确认流的状态：
```cpp
while (cin>>word)
    //ok:读取成功
```
输入成功返回true,反之返回false；

### 流的状态类型:iostate
流对象的rdstate成员返回一个iostate值，表示其状态。
```cpp
aotu old_state =cin.rdstate();//返回cin当前状态
cin.cleal();//清空cin状态
process_input(cin);//使用cin
cin.setstate(old_state);//!!!把cin的状态置为之前的状态
```

## 缓冲区
每个输出流都管理一个缓冲区，保存程序读写的数据。
### 缓冲刷新：
* 程序结束
* 缓冲区满
* 使用操作符例如endl刷新缓冲区
* 输出操作后，使用unitbuf设置流的内部状态
* 被关联的流在读写时会被刷新
```cpp
cout<<"hi!"<<endl;
//输出Hi和一个换行，然后刷新缓冲区
cout<<"hi!"<<flush;
//输出hi然后刷新缓冲区
cout<<"hi"<<ends;
//输出hi和一个空字符然后刷新缓冲区
```
**unitbuf**如果希望每次输出操作后都刷新缓冲区，使用unitbuf操作符，在每次写操作后进行一次flush。
**nounitbuf**重置流，恢复正常刷新机制。

### 关联输入和输出流
若一输入流被关联到一个输出流时，任何试图从输入流读取数据的操作都会先刷新关联的输出流。标准库中，**cin和cout是关联的。**
`cin>>ival;`


## 文件流
头文件中ifstream定义了三个类型支持文件IO:
ifstream,oftream,fstream;
```cpp
ifstream in(ifile); //构造一个ifstream并打开给定文件
ofstream out; //输出文件流并未关联任何文件
```

```cpp
ifstream input(argv[1]); //打开销售记录文件
ofstream output(argv[2]); // 打开输出文件
Sales data total; //保存销售总额的变量
if(read(input,total)){ //读取第一条销售记录
    Sales data trans; //保存下一条销售记录的变量
    while(read(input,trans)){ //读取剩余记录
        if (total.isbn()== trans.isbn()) //检查isbn
            total.combine(trans); //更新销售总额
        else {
        print(output,total)<< endl;// 打印结果
        total = trans; //处理下一本书
        }
    }
print(output,total)<< endl;}//打印最后一本书的销售额
else
    cerr<<"No data?!"<< endl;//文件中无输入数据
```
`std::istream::read`是 C++ 标准库中 istream 类的一个成员函数，用于从输入流中读取原始字节数据到一个字符数组或缓冲区中。它通常用于读取二进制数据或以字节为单位读取大量数据。
```cpp
#include <iostream>
using namespace std;
int main() {
    const int size = 10;  // 定义缓冲区大小
    char buffer[size];    // 创建字符缓冲区
    cout << "Enter up to 10 characters: ";
    cin.read(buffer, size);  // 从标准输入读取最多size个字符
    cout << "You entered: ";
    cout.write(buffer, cin.gcount());  // 使用 write 函数输出已读取的字符数
    cout << endl;
    return 0;
}
```
`cin.gcount()`返回上一次读取操作中实际读取的字符数。

### open和colse
如果定义了一个空文件流对象，随后何以用open来将他和文件关联起来。对一个已经被打开的文件流open会失败，failbit被置位；
```cpp
ifstream in(ifile);
ofstream out;
out.open(ifile + ".copy");
```
如果open失败failbit置位true；

```cpp
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	ifstream ifs("data");
	vector<string> v1;
	string buf;

	if(ifs)
	{
		while(ifs >> buf)
		{
			v1.push_back(buf);
		}
	}

	for(const auto &s : v1)
		cout << s << endl;

	return 0;
}
```
vector中每个元素为一个单词，operator>>（流提取运算符）用于从输入流中读取数据时，以空白字符（如空格、制表符、换行符等）作为分隔符来读取内容。每次 ifs >> buf 的调用都会从文件流 ifs 中读取下一个单词，直到遇到空白字符为止。

### 文件模式
|模式|作用||
|----|----|----|
|in|只读|只可以对ifstream和fstream使用|
|out|只写|只可以对ofstream和fstream使用|
|app|写操作前定位末尾|使用app隐式使用out|
|ate|打开文件后定位末尾||
|trunc|截断|out下默认trunc|
|binary|二进制方式IO||
*使用方法*：
```cpp
ofstream out; //定义空文件输出流
out.open("file"); //默认out trunc
out.close(); //关闭out使用其他文件
out.open("precious", ofstream::app) //模式out app
out.close();
```

## string流
### istringstream:
对字符串进行读操作
读取名字：
```cpp
istringstream record(line); //将字符串输入流绑定line
record >> info.name;  //将line的字符串输入到结构体的name,默认第一个“ ”结束
```
### ostringstream:
对字符串进行读操作
```cpp
ostringstream formatted, badNums;  //创建两个字符串输出流
badNums<<" "<<nums; //存入badNums
formatted<<" "<<format(nums); //存入formatted
```
