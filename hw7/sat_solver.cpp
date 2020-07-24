#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "avlbst.h"

using namespace std;

bool solveHelper(int currClause, int numClauses, AVLTree<int, int>& values, vector<vector<int>>& clauses); // recursive helper function

void solve(int numVars, int numClauses, AVLTree<int, int>& values, vector<vector<int>>& clauses); // calls solveHelper

bool isValid(AVLTree<int, int>& values, vector<int>& curr); // returns true if solution is found for one clause

bool verify(int numClauses, AVLTree<int, int>& values, vector<vector<int>>& clauses); // returns true if solution works for all clauses

bool solveHelper(int currClause, int numClauses, AVLTree<int, int>& values, vector<vector<int>>& clauses)
{
    if(currClause == numClauses)
    {
        return true;
    }
    if(isValid(values, clauses[currClause])) // checks if current clause works without changing variables
    {
        if(!solveHelper(currClause+1, numClauses, values, clauses))
        {
            return false;
        }
        return true;
    }

    for(unsigned int i=0; i<clauses[currClause].size(); i++) // iterates through every variable in the current clause
    {
        int currVar = abs(clauses[currClause][i]);

        AVLTree<int,int>::iterator it = values.find(currVar);
        if(it != values.end())
        {
            if(it->second == -1) // finds unassigned variables
            {
                if(clauses[currClause][i] < 0) // if negative, tries 0
                {
                    it->second = 0;
                    if(solveHelper(currClause+1, numClauses, values, clauses))
                    {
                        return true;
                    }
                }
                else // if positive, tries 1
                {
                    it->second = 1;
                    if(solveHelper(currClause+1, numClauses, values, clauses))
                    {
                        return true;
                    }
                }
                it->second = -1; // if both fail, reset then try changing another variable
            }
        }
    }
    
    return false;
}

void solve(int numVars, int numClauses, AVLTree<int, int>& values, vector<vector<int>>& clauses)
{
    solveHelper(0, numClauses, values, clauses);
}

bool isValid(AVLTree<int, int>& values, vector<int>& curr)
{
    for(unsigned int i=0; i<curr.size(); i++) // goes through every variable until it finds true
    {
        int currVar = abs(curr[i]);
        bool currBool = false;
        AVLTree<int,int>::iterator it = values.find(currVar);
        if(it != values.end()) 
        {
            if(it->second == -1)
            {
                continue;
            }
            currBool = it->second;
        }
        if(curr[i] < 0 && currBool == 0) 
        {
            return true;
        }
        else if(curr[i] > 0 && currBool == 1)
        {
            return true;
        }
    }
    return false;
}

bool verify(int numClauses, AVLTree<int, int>& values, vector<vector<int>>& clauses)
{
    for(int i=0; i<numClauses; i++) // runs isValid on every clause
    {
        if(!isValid(values, clauses[i]))
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        cerr << "Usage ./sat_solver input_file output_file" << endl;
    }
    ifstream ifile(argv[1]);
    ofstream ofile(argv[2]);
    if(ifile.fail())
    {
        cout << "Failed to open file!" << endl;
        return 1;
    }

    string line;
    getline(ifile, line);
    if(ifile.fail())
    {
      cout << "Unable to extract line." << endl;
      return 1;
    }

    while(line[0] == 'c') // clears comments
    {
        getline(ifile, line);
    }

    stringstream ss(line);
    ss.ignore(5);
    int numVars;
    int numClauses;
    ss >> numVars >> numClauses;

    AVLTree<int, int> values;
    for(int i=1; i<=numVars; i++) // populates AVLTree with unassigned values
    {
        values.insert(make_pair(i,-1)); // -1 is unassigned
    }

    vector<vector<int>> clauses;
    clauses.resize(numClauses);
    for(int i=0; i<numClauses; i++) // populates clauses vector
    {
        getline(ifile, line);
        stringstream ssClause(line);
        int single;
        ssClause >> single;
        while(single != 0)
        {
            clauses[i].push_back(single);
            ssClause >> single;
        }
    }

    solve(numVars, numClauses, values, clauses);

    if(!verify(numClauses, values, clauses)) // writes into ofile
    {
        ofile << "No solution";
    }
    else
    {
        for(int i=1; i<=numVars; i++)
        {
            AVLTree<int,int>::iterator it = values.find(i);
            if(it != values.end())
            {
                if(it->second == 1 || it->second == 0) // skips unassigned variables
                {
                    ofile << it->first << " = " << it->second << endl;
                }
            }
        }
    }

    ofile.close();
    return 0;
}