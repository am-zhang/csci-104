#include <ctime>
#include "datetime.h"

using namespace std;

DateTime::DateTime()
{
    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    hour = timeinfo->tm_hour;
    min = timeinfo->tm_min;
    sec = timeinfo->tm_sec;
    year = timeinfo->tm_year + 1900;
    month = timeinfo->tm_mon + 1;
    day = timeinfo->tm_mday;
}

DateTime::DateTime(int hh, int mm, int ss, int year, int month, int day) :
    hour(hh), min(mm), sec(ss), year(year), month(month), day(day)
{
    
}

bool DateTime::operator<(const DateTime& other) const
{
    if(this->year < other.year)
    {
        return true;
    }
    else if(this->year > other.year)
    {
        return false;
    }
    if(this->month < other.month)
    {
        return true;
    }
    else if(this->month > other.month)
    {
        return false;
    }
    if(this->day < other.day)
    {
        return true;
    }
    else if(this->day > other.day)
    {
        return false;
    }
    if(this->hour < other.hour)
    {
        return true;
    }
    else if(this->hour > other.hour)
    {
        return false;
    }
    if(this->min < other.min)
    {
        return true;
    }
    else if(this->min > other.min)
    {
        return false;
    }
    if(this->sec < other.sec)
    {
        return true;
    }
    else if(this->sec > other.sec)
    {
        return false;
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, const DateTime& other)
{
    
    os << other.year << '-';
    if(other.month < 10)
    {
        os << '0';
    }
    os << other.month << '-';
    if(other.day < 10)
    {
        os << '0';
    }
    os << other.day << ' ';
    if(other.hour < 10)
    {
        os << '0';
    }
    os << other.hour << ':';
    if(other.min < 10)
    {
        os << '0';
    }
    os << other.min << ':';
    if(other.sec < 10)
    {
        os << '0';
    }
    os << other.sec;
    return os;
}

std::istream& operator>>(std::istream& is, DateTime& dt)
{
    string y;
    string mo;
    string d;
    string h;
    string mi;
    string s;

    getline(is, y, '-');
    getline(is, mo, '-');
    getline(is, d, ' ');
    getline(is, h, ':');
    getline(is, mi, ':');
    getline(is, s, ' ');

    try
    {
        dt.year = stoi(y);
        dt.month = stoi(mo);
        dt.day = stoi(d);
        dt.hour = stoi(h);
        dt.min = stoi(mi);
        dt.sec = stoi(s);
    }
    catch(...) // if an exception is thrown, sets to current system time/date
    {  
        time_t rawtime;
        struct tm * timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        dt.hour = timeinfo->tm_hour;
        dt.min = timeinfo->tm_min;
        dt.sec = timeinfo->tm_sec;
        dt.year = timeinfo->tm_year + 1900;
        dt.month = timeinfo->tm_mon + 1;
        dt.day = timeinfo->tm_mday;

        return is; 
    }

    return is;
}