#include "setops.h"
#include <iostream>

using namespace std;

set<string> operator&(const set<string>& s1, const set<string>& s2)
{
    set<string> intersects;
    if (s1.size() >= s2.size()) // checks which set is longer
    {
        for(set<string>::iterator it = s1.begin(); it != s1.end(); ++it)
        {
            if (s2.find(*it) != s2.end())
            {
                intersects.insert(*it); // adds an element if it's also found in the other set
            }
        }
    }
    else
    {
        for(set<string>::iterator it = s2.begin(); it != s2.end(); ++it)
        {
            if (s1.find(*it) != s1.end())
            {
                intersects.insert(*it);
            }
        }
    }
    return intersects;
}

set<string> operator|(const set<string>& s1, const set<string>& s2)
{
    set<string> unions;
    for(set<string>::iterator it = s1.begin(); it != s1.end(); ++it)
    {
        if (unions.find(*it) == unions.end())
        {
            unions.insert(*it); // adds new elements in set 1, checking for repeats
        }
    }
    for(set<string>::iterator it = s2.begin(); it != s2.end(); ++it)
    {
        if (unions.find(*it) == unions.end())
        {
            unions.insert(*it); // repeats for set 2
        }
    }
    return unions;
}

set<string> operator-(const set<string>& s1, const set<string>& s2)
{
    set<string> differences;
    for(set<string>::iterator it = s1.begin(); it != s1.end(); ++it)
    {
        if (s2.find(*it) == s2.end())
        {
            differences.insert(*it); // adds elements from set 1 that aren't in set 2
        }
    }
    return differences;
}