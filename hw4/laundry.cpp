#include "stack.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    ifstream ifile(argv[1]);
    ofstream ofile(argv[2]);

    if (ifile.fail())
    {
        cout << "Failed to open file!" << endl;
        return 1;
    }

    Stack<int> pile;
    int input;
    ifile >> input;

    while(!ifile.fail())
    {
        if(input == 0 || input == -1)
        {
            pile.push(input);
            ifile >> input;
        }
        else
        {
            for(int i=0; i<input; i++)
            {
                if(pile.top() == 0)
                {
                    ofile << "black ";
                }
                else
                {
                    ofile << "white ";
                }
                pile.pop();
            }
            ifile >> input;
            if(!ifile.fail())
            {
                ofile << endl;
            }
        }
    }

    return 0;
}