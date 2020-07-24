#include <iostream>
#include <stdexcept>
#include <cstring>
#include "str.h"

using namespace std;

Str::Str()
{
  size_ = 0;
  data_ = new char[1];
  data_[0] = '\0';
}

Str::~Str()
{
  delete [] data_;
}

Str::Str(const Str& s)
{
  size_ = s.size_;
  this->data_ = new char[s.size() + 1];
  strcpy(this->data_, s.data_);
}

Str::Str(const char* s)
{
  if(s == NULL) // checks that the string is not empty
  {
    this->data_ = new char[1];
    this->data_[0] = '\0';
    size_ = 0;
  }
  else
  {
    this->data_ = new char[strlen(s) + 1];
    strcpy(this->data_, s);
    size_ = strlen(s);
  }
}

Str& Str::operator=(const char* s)
{
  if(!strcmp(this->data_,s)) return *this; // checks for self-assignment
  delete [] this->data_;
  this->data_ = new char[strlen(s) + 1];
  strcpy(this->data_, s);
  this->size_ = strlen(s);
  return (*this);
}

Str& Str::operator=(const Str& s)
{
  if(!strcmp(this->data_,s.data_)) return *this; // checks for self-assignment
  delete [] this->data_;
  this->data_ = new char[s.size_ + 1];
  strcpy(this->data_, s.data_);
  this->size_ = s.size_;
  return (*this);
}

Str& Str::operator+=(const Str& s)
{
  char* temp = new char[this->size() + s.size() + 1];
  strcpy(temp, this->data_);
  strcat(temp, s.data_);
  delete [] this->data_;
  this->data_ = temp;
  size_ += s.size_;
  return (*this);
}

Str& Str::operator+=(const char* s)
{
  if(s == NULL) // checks if s is empty
  {
    return (*this);
  }
  else
  {
    char* temp = new char[this->size() + strlen(s) + 1];
    strcpy(temp, this->data_);
    strcat(temp, s);
    delete [] this->data_;
    this->data_ = temp;
    size_ += strlen(s);
    return (*this);
  }
}

size_t Str::size() const
{
  return size_;
}

char& Str::operator[](unsigned int i)
{
  if (i < 0 || i > (this->size())-1)
  {
    throw std::out_of_range("Index is out of range");
  }
  return this->data_[i];
}

char const & Str::operator[](unsigned int i) const
{
  if (i < 0 || i > ((this->size())-1))
  {
    throw std::out_of_range("Index is out of range");
  }
  return this->data_[i];
}

bool Str::operator==(const Str& rhs) const
{
  return !(strcmp(this->data_, rhs.data_));
}


bool Str::operator!=(const Str& rhs) const
{
  return strcmp(this->data_, rhs.data_);
}


bool Str::operator>(const Str& rhs) const
{
  int val = strcmp(this->data_, rhs.data_);
  return (val > 0);
}


bool Str::operator<(const Str& rhs) const
{
  int val = strcmp(this->data_, rhs.data_);
  return (val < 0);
}

Str Str::operator+(const Str& rhs) const
{
  Str sum;
  delete [] sum.data_;
  sum.data_ = new char[this->size() + rhs.size() + 1];
  strcpy(sum.data_, this->data_);
  strcat(sum.data_, rhs.data_);
  sum.size_ = this->size_ + rhs.size_;
  return sum;
}

Str Str::operator+(const char* rhs) const
{
  Str sum;
  delete [] sum.data_;
  sum.data_ = new char[this->size() + strlen(rhs) + 1];
  strcpy(sum.data_, this->data_);
  strcat(sum.data_, rhs);
  sum.size_ = this->size_ + strlen(rhs);
  return sum;
}

Str operator+(char* lhs, const Str& rhs)
{
  Str sum;
  delete [] sum.data_;
  sum.data_ = new char[strlen(lhs) + rhs.size() + 1];
  strcpy(sum.data_, lhs);
  strcat(sum.data_, rhs.data_);
  sum.size_ = strlen(lhs) + rhs.size();
  return sum;
}

std::ostream& operator<<(std::ostream& ostr, const Str& s)
{
  for(unsigned int i=0; i<s.size(); i++)
  {
    ostr << s.data_[i];
  }
  return ostr;
}

std::istream& operator>>(std::istream& istr, Str& s)
{
  std::string stemp;
  istr >> stemp;
  s = stemp.c_str();
  return istr;
}

