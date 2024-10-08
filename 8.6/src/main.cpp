#include <iostream>
#include <fstream>
#include "Sales_data.h"

using namespace std;

int main(int argc, char* argv[]){
    
    if(argc != 2){
        cerr << "请给出文件名" << endl;
        return -1;
    }

    ifstream in(argv[1]);  //定义文件输入流
    if(!in){
        cerr<<"无法打开输入文件"<<endl;
        return -1;
    }

    Sales_data total;

    if(read(in, total)){
        Sales_data trans;
        while(read(in,trans)){
            if(total.isbn() == trans.isbn())
                total.combine(trans);
            else{
                kprint(cout, total)<<endl;
                total = trans;
            }
        }
        kprint(cout, total) << endl;
    }
    else{
        cerr<<"没有数据"<<endl;
    }

    system("pause");
    return 0;
}