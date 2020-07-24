#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) 
{
    ifstream ifile(argv[1]);
    ofstream ofile(argv[2]);

    if (argc != 3)
    {
        cout << "Incorrect number of arguments, please provide input and output files." << endl;
        return 1;
    }
    if (ifile.fail())
    {
        cout << "Failed to open file!" << endl;
        return 1;
    }

    int num = 0;
    ifile >> num;
    if (ifile.fail() || num == 0) // checks if integer on first line is read correctly
    {
        ofile << 0;
        return 1;
    }

    int* pairs = new int[num]; // dynamically allocates new array to store numbers
    for (int i=0; i<num; i++)
    {
        ifile >> pairs[i];
    }

    for (int i=0; i<num/2; i++)
    {
        ofile << (pairs[i] + pairs[num-1-i]);
        if (i != (num/2) - 1)
        {
            ofile << endl;
        }
    }
    if (num%2 == 1) // if there is an odd number of integers, adds middle to itself
    {
        ofile << endl << 2*pairs[num/2];
    }

    delete [] pairs; // deallocates the array

    ifile.close();
    ofile.close();
    return 0;
}