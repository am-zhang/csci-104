#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <vector>
#include <map>
#include "setops.h"

using namespace std;

int main(int argc, char *argv[])
{
    ifstream ifile(argv[1]);
    ifstream cmdfile(argv[2]);
    ofstream ofile(argv[3]);

    if (argc != 4)
    {
        cout << "Incorrect number of arguments! Requires input, command, and output files." << endl;
        return 1;
    }
    if (ifile.fail() || cmdfile.fail())
    {
        cout << "Failed to open file!" << endl;
        return 1;
    }

    map<string, set<string>> majors;
    set<string> students;

    string line;
    string name;
    string major;

    getline(ifile, line, ','); // extracts the first name
    if (ifile.fail())
    {
        cout << "Failed to extract line." << endl;
        return 1;
    }
    while (!ifile.fail())
    {
        stringstream line_name(line);
        line_name >> name;
        while (!line_name.fail()) // discards ending whitespace
        {
            name.push_back(' ');
            string append;
            line_name >> append; // stores the entire name
            name += append;
        }

        line.clear();
        getline(ifile, line); // proceeds to extract the majors
        stringstream line_major(line);
        line_major >> major;
        while(!line_major.fail())
        {
            for (unsigned int i=0; i<major.size(); i++)
            {
                major[i] = toupper(major[i]); // capitalize letters
            }
            map<string, set<string>>::iterator it = majors.find(major);
            if (it == majors.end()) // if the major doesn't exist yet, create new entry in map
            {
                students.insert(name);
                majors.insert(make_pair(major, students));
            }
            else // if the major exists, insert new name in set of students
            {
                (it->second).insert(name);
            }
            
            major.clear();
            students.clear();
            line_major >> major;
        }

        name.clear();
        line.clear();
        major.clear();
        students.clear();
        getline(ifile, line, ',');
    }

    string cmdmajor;
    string singlemajor;
    getline(cmdfile, cmdmajor); // read the majors in the cmd file
    if (cmdfile.fail())
    {
        cout << "Failed to extract major." << endl;
        return 1;
    }
    while (!cmdfile.fail())
    {
        ofile << cmdmajor << endl;
        stringstream line_major(cmdmajor);
        vector<string> multimajor;
        line_major >> singlemajor;
        while(!line_major.fail())
        {
            for (unsigned int i=0; i<singlemajor.size(); i++)
            {
                singlemajor[i] = toupper(singlemajor[i]); // capitalizes lowercase letters
            }
            multimajor.push_back(singlemajor); // stores multiple majors to look up later
            singlemajor.clear();
            line_major >> singlemajor;
        }
        if (multimajor.size() == 1) // if only one major is entered
        {
            map<string, set<string>>::iterator it = majors.find(multimajor[0]);
            if (it != majors.end()) // find the major to look up the students
            {
                for(set<string>::iterator itset = (it->second).begin(); itset != (it->second).end(); ++itset)
                {
                    ofile << *itset << endl; // prints students associated with the major
                }
            }
        }
        else // if multiple (double, triple) majors are entered
        {
            set<string> intersect;
            map<string, set<string>>::iterator it = majors.find(multimajor[0]);
            if (it != majors.end())
            {
                intersect = it->second;
            }
            for (unsigned int i=1; i<multimajor.size(); i++)
            {
                map<string, set<string>>::iterator it = majors.find(multimajor[i]);
                if (it != majors.end()) // finds intersection of the majors
                {
                    intersect = intersect & it->second;
                }
            }
            for(set<string>::iterator itset = intersect.begin(); itset != intersect.end(); ++itset)
            {
                ofile << *itset << endl; // prints students associated with the majors
            }
        }

        ofile << endl;
        multimajor.clear();
        getline(cmdfile, cmdmajor);
    }

    ifile.close();
    cmdfile.close();
    ofile.close();
    return 0;
}