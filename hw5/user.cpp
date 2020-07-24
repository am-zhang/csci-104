#include <algorithm>
#include "user.h"
#include "tweet.h" // for the TweetComp function
#include "hsort.h" // for the hsort function

using namespace std;

User::User(string name) :
    name_(name)
{
    
}

User::~User()
{
    
}

string User::name() const
{
    return name_;
}

set<User*> User::followers() const
{
    return followers_;
}

set<User*> User::following() const
{
    return following_;
}

list<Tweet*> User::tweets() const
{
    return tweets_;
}

void User::addFollower(User* u)
{
    followers_.insert(u);
}

void User::addFollowing(User* u)
{
    following_.insert(u);
}

void User::addTweet(Tweet* t)
{
    tweets_.push_front(t);
}

vector<Tweet*> User::getFeed()
{
    for(set<User*>::iterator it = following_.begin(); it != following_.end(); ++it)
    {
        for(list<Tweet*>::iterator listit = (*it)->tweets_.begin(); listit != (*it)->tweets_.end(); ++listit)
        {
            if (!((*listit)->startMention)) // if it doesn't starts with a mention, shows up in main
            {
                feed_.push_back(*listit);
            }
            else
            {
                vector<string> mentioned = (*listit)->mentions();
                if (mentioned[0] == name_) // if mentioned and follow each other, shows up in main
                {
                    feed_.push_back(*listit);
                }
            }
        }
    }

    list<Tweet*>::iterator listit;
    for(listit = tweets_.begin(); listit != tweets_.end(); ++listit)
    {
        feed_.push_back(*listit);
    }

    hsort(feed_, TweetComp());

    return feed_;
}

vector<Tweet*> User::getMentionsFeed()
{
    hsort(mentionsfeed_, TweetComp());
    return mentionsfeed_;
}

void User::addMention(Tweet* t)
{
    mentionsfeed_.push_back(t);
}