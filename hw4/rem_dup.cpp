#include "rem_dup_lib.h"
#include <fstream>
#include <sstream>
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

    string line1;
    string line2;
    getline(ifile, line1);
    getline(ifile, line2);
    stringstream ss1(line1);
    stringstream ss2(line2);
    int input;

    ss1 >> input;
    Item* head1 = nullptr;
    if(!ss1.fail())
    {
        head1 = append(head1, input);
        ss1 >> input;
    }
    while(!ss1.fail()) // reads in first line
    {
        append(head1, input);
        ss1 >> input;
    }
    
    ss2 >> input;
    Item* head2 = nullptr;
    if(!ss2.fail())
    {
        head2 = append(head2, input);
        ss2 >> input;
    }
    while(!ss2.fail()) // reads in second line
    {
        append(head2, input);
        ss2 >> input;
    }

    removeConsecutive(head1);
    Item* head3 = concatenate(head1, head2);

    Item* temp = head3;
    while(temp != nullptr) // outputs to file
    {
        ofile << temp->val << ' ';
        temp = temp->next;
    }

    delete_list(head1);
    delete_list(head2);
    delete_list(head3);

    return 0;
}