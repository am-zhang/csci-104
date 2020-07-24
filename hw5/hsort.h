#include <vector>
#include <iostream>

// heapify() helper function
// loc - Location to start the heapify() process
// effsize - Effective size (number of items in the vector that
//           are part of the heap). Useful for performing heap-sort in place.
template <typename T, typename Comparator >
void heapify(std::vector<T>& data, size_t loc, size_t effsize, Comparator& c )
{
    if((loc >= ((effsize + 2) / 2)) || ((2 * loc + 1) >= effsize)) // returns if leaf node
    {
        return;
    }
    int lesserChild = (2 * loc) + 1; // start with left
    if((2 * loc) + 2 < effsize) // if right child exists
    {
        int rChild = lesserChild + 1;
        if(c(data[lesserChild], data[rChild])) // comparison
        {
            lesserChild = rChild;
        }
    }
    if(c(data[loc], data[lesserChild])) // comparison
    {
        T temp = data[loc];
        data[loc] = data[lesserChild];
        data[lesserChild] = temp;

        heapify(data, lesserChild, effsize, c);
    }
}

template <typename T, typename Comparator >
void hsort(std::vector<T>& data, Comparator c = Comparator())
{
    for(int i=(data.size()-2)/2; i>=0; i--)
    {
        heapify(data, i, data.size(), c);
    }

    for(int i=data.size()-1; i>0; i--)
    {
        T temp = data[0];
        data[0] = data[i];
        data[i] = temp;

        heapify(data, 0, i, c);
    }
}