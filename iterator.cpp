#include <iostream>
#include <vector>
using namespace std;

int main(int argv, char** argc)
{
    vector<int> vec = {1,2,3,4,5,6};
    for(vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
        {
            cout << *it << endl; // 注：迭代器不是指针
        }
    return 0;
}