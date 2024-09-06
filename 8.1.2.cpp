#include <iostream>
using namespace std;
istream &test(istream &is){
    int temp = 0;
    while(is>>temp)
        cout<<temp<<endl;
    is.clear();
    return is;
}

int main(int argc, char* argv[])
{
    int Temp;
    test(cin)>>Temp;
    cout<<Temp<<endl;
    return 0;
}
