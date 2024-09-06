#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

int main(){
    fstream ifs("data");
    string buff;
    vector<string> vec;
    if(ifs){
        while(getline(ifs, buff))
        {
            v1.push_back(buff);
        }
    }
    for(const auto &s : v1)
        cout<<s<<endl;
    
    return 0;
}
