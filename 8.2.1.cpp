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
            vec.push_back(buff);
        }
    }
    for(const auto &s : vec)
        cout<<s<<endl;
    
    return 0;
}
