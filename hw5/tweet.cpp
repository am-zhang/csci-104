#include <sstream>
#include "tweet.h"

using namespace std;

Tweet::Tweet()
{
    isMention = false;
    startMention = false;
}

Tweet::Tweet(User* user, const DateTime& time, const std::string& text) :
    user_(user), time_(time), text_(text)
{
    isMention = false;
    startMention = false;

    stringstream ss(text_);
    string word;
    ss >> word;
    if((!ss.fail()) && (word[0] == '@')) // checks if starts with a mention
    {
        isMention = true;
        startMention = true;
        mentions_.push_back(word.substr(1));
    }
    else if (word[0] == '#')
    {
        for(unsigned int i=0; i<word.size(); i++)
        {
            word[i] = tolower(word[i]); // all lowercase
        }
        hashtags_.insert(word.substr(1));
    }
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
        else if(word[0] == '@')
        {
            isMention = true;
            mentions_.push_back(word.substr(1));
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
    os << t.time_ << ' ' << t.user_->name() << ' ' << t.text_;
    return os;
}

User* Tweet::user() const
{
    return user_;
}

vector<string> Tweet::mentions() const
{
    return mentions_;
}