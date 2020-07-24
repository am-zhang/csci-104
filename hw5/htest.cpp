#include "hsort.h"
#include <iostream>

using namespace std;

int main()
{
    vector<int> data;
    data.push_back(2);
    data.push_back(1);
    data.push_back(6);
    data.push_back(3);
    data.push_back(4);
    data.push_back(8);
    data.push_back(5);
    hsort(data, std::less<int>());
    for(unsigned int i=0; i<data.size(); i++)
    {
        cout << data[i] << " ";
    }
    cout << endl;
    return 0;
}