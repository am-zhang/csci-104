#ifndef DEQUE_H
#define DEQUE_H
#include <stdexcept>

/**
 * Implements a templated, array-based, 
 * double-ended queue.
 *
 * The Deque should allow for amortized O(1) 
 * insertion and removal from either end. 
 * It should dynamically resize, when it becomes
 * full, but never needs to shrink.  
 *
 * It should use a circular buffer approach
 * by tracking the "front" and "back" location.
 *
 */


template <typename T>
class Deque
{
 public:
  /* START - DO NOT CHANGE ANY OF THESE LINES */
  /**
   *  Default constructor 
   *   Create an array of size 1 by default
   */
  Deque();

  /**
   *  Default constructor 
   *   Create an array of the given capacity.
   */
  Deque(size_t capacity);

  /**
   *  Destructor
   */
  ~Deque();

  /**
   *  Returns the number of elements in the Deque. 
   *   - Must run in O(1)
   */
  size_t size() const;

  /**
   *  returns true if the deque is empty
   *   - Must run in O(1)
   */
  bool empty() const;

  /**
   *  returns  the i-th element from the front
   *   - Must run in O(1)
   *   - Must throw std::range_error if i is
   *      an invalid location
   */
  T& operator[](size_t i);

  /**
   *  returns  the i-th element from the front
   *   - Must run in O(1)
   *   - Must throw std::range_error if i is
   *      an invalid location
   */
  T const & operator[](size_t i) const;

  /**
   *  Inserts a new item at the back of the
   *  Deque
   *   - Must run in amortized O(1)
   */
  void push_back(const T& item);

  /**
   *  Inserts a new item at the front of the
   *  Deque
   *   - Must run in amortized O(1)
   */
  void push_front(const T& item);

  /**
   *  Removes the back item from the Deque
   *   - Must run in amortized O(1)
   *   - Simply return if the deque is empty
   */
  void pop_back();

  /**
   *  Removes the front item from the Deque
   *   - Must run in amortized O(1)
   *   - Simply return if the deque is empty
   */
  void pop_front();
  /* END - DO NOT CHANGE ANY OF THESE LINES */
 private:
  /* Add data members and private helper 
   * functions below 
   */
  T* start;
  int head;
  int tail;
  int cap; // max capacity
  int curr; // current size
  
};

/* Implement each Deque<T> member function below 
 * taking care to meet the runtime requirements
 */

template<typename T>
Deque<T>::Deque()
{
   T* temp = new T[1];
   start = temp;
   head = 0;
   tail = 0;
   cap = 1;
   curr = 0;
}

template<typename T>
Deque<T>::Deque(size_t capacity)
{
   if(capacity == 0)
   {
      capacity = 1;
   }
   T* temp = new T[capacity];
   start = temp;
   head = 0;
   tail = 0;
   cap = capacity;
   curr = 0;
}

template<typename T>
Deque<T>::~Deque()
{
   delete [] start;
}

template<typename T>
size_t Deque<T>::size() const
{
   return curr;
}

template<typename T>
bool Deque<T>::empty() const
{
   return (curr == 0);
}

template<typename T>
T& Deque<T>::operator[](size_t i)
{
   if(i < 0 || i > (size_t)curr)
   {
      throw std::range_error("Index is an invalid location.");
   }
   return start[(head + i + cap) % cap];
}

template<typename T>
T const & Deque<T>::operator[](size_t i) const
{
   if(i < 0 || i > (size_t)curr)
   {
      throw std::range_error("Index is an invalid location.");
   }
   return start[(head + i + cap) % cap];
}

template<typename T>
void Deque<T>::push_back(const T& item)
{
   if(curr < cap)
   {
      start[tail] = item;
      tail++;
      
   }
   else
   {
      int newsize = cap*2;
      T* newstart = new T[newsize];
      for(int i=0; i<cap; i++)
      {
         newstart[i] = start[(head + i + cap) % cap];
      }
      delete [] start;
      start = newstart;
      cap *= 2;
      start[curr] = item;
      head = 0;
      tail = curr + 1;
   }
   curr++;
}

template<typename T>
void Deque<T>::push_front(const T& item)
{
   if(curr < cap)
   {
      start[(head - 1 + cap) % cap] = item;
      head--;
   }
   else
   {
      int newsize = cap*2;
      T* newstart = new T[newsize];
      for(int i=0; i<cap; i++)
      {
         newstart[i] = start[(head + i + cap) % cap];
      }
      delete [] start;
      start = newstart;
      cap *= 2;
      start[cap - 1] = item;
      head = -1;
      tail = cap - 2;
   }
   curr++;
}

template<typename T>
void Deque<T>::pop_back()
{
   if(curr == 0)
   {
      return;
   }
   tail = tail - 1;
   curr--;
}

template<typename T>
void Deque<T>::pop_front()
{
   if(curr == 0)
   {
      return;
   }
   head = head + 1;
   curr--;
}

#endif
