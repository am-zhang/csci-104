#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
 public:
  /// Constructs an m-ary heap for any m >= 2
  Heap(int m, PComparator c = PComparator());

  /// Destructor as needed
  ~Heap();

  /// Adds an item
  void push(const T& item);

  /// returns the element at the top of the heap 
  ///  max (if max-heap) or min (if min-heap)
  T const & top() const;

  /// Removes the top element
  void pop();

  /// returns true if the heap is empty
  bool empty() const;

 private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> data;
  int size;
  void heapify(int loc);
  int m;
  PComparator c;
};

// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c) : 
  size(0), m(m), c(c) 
{
  
}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap()
{

}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item)
{
  data.push_back(item);
  int loc = size;
  int parent = (loc-1)/m;
  while((parent >= 0) && (c(data[loc], data[parent])))
  {
    T temp = data[loc];
    data[loc] = data[parent];
    data[parent] = temp;
    loc = parent;
    parent = (loc-1)/m;
  }
  size++;
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const
{
  return (size == 0);
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::heapify(int loc)
{
  if((m * loc + 1) >= size) // returns if leaf node
  {
      return;
  }
  int lesserChild = (m * loc) + 1; // start with left
  for(int i=1; i<=m; i++) // loops through right children
  {
    if((m * loc) + i < size) // if right child exists
    {
      int rChild = (m * loc) + i;
      if(c(data[rChild], data[lesserChild])) // comparison
      {
        lesserChild = rChild;
      }
    }
  }

  if(c(data[lesserChild], data[loc])) // comparison
  {
    T temp = data[loc];
    data[loc] = data[lesserChild];
    data[lesserChild] = temp;
    heapify(lesserChild);
  }
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::logic_error("can't top an empty heap");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element
  return data[0];
}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    throw std::logic_error("can't pop an empty heap");
  }
  data[0] = data[size-1];
  data.pop_back();
  heapify(0);
  size--;
}



#endif

