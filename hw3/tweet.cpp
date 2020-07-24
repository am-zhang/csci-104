#include <sstream>
#include "tweet.h"

using namespace std;

Tweet::Tweet()
{
    
}

Tweet::Tweet(User* user, const DateTime& time, const std::string& text) :
    user_(user), time_(time), text_(text)
{
    stringstream ss(text_);
    string word;
    ss >> word;
    while(!ss.fail())
    {
        if(word[0] == '#')
        {
            for(unsigned int i=0; i<word.size(); i++)
            {
                word[i] = tolower(word[i]); // all lowercase
            }
            hashtags_.insert(word.substr(1));
        }
        word.clear();
        ss >> word;
    }
}

DateTime const & Tweet::time() const
{
    return time_;
}

string const & Tweet::text() const
{
    return text_;
}

set<string> Tweet::hashTags() const
{
    return hashtags_;
}

bool Tweet::operator<(const Tweet& other) const
{
    return (this->time_ < other.time_);
}

std::ostream& operator<<(std::ostream& os, const Tweet& t)
{
    os << t.time_ << ' ' << t.user_->name() << t.text_;
    return os;
}

User* Tweet::user() const
{
    return user_;
}