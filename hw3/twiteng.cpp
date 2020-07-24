#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include "twiteng.h"
#include "tweet.h"

using namespace std;

TwitEng::TwitEng()
{
    
}

TwitEng::~TwitEng()
{
    map<string, User*>::iterator it;
    for(it = all_users.begin(); it != all_users.end(); ++it)
    {
        delete it->second;
    }
    for(unsigned int i=0; i<all_tweets.size(); i++)
    {
        delete all_tweets[i];
    }
}

bool TwitEng::parse(char* filename)
{
    ifstream ifile(filename);

    int num = 0;
    ifile >> num; // number of users
    if(ifile.fail())
    {
        return true;
    }
    
    string space;
    getline(ifile, space);

    for(int i=0; i<num; i++) // only parses users and following
    {
        string line;
        std::getline(ifile, line);
        
        stringstream ss(line);
        string name;
            
        ss >> name; // first name of the line

        if(ifile.fail())
        {
            return true;
        }

        map<string, User*>::iterator it = all_users.find(name);
        if (it == all_users.end()) // if user isn't already in the map
        {
            User* new_user = new User(name);
            all_users.insert(make_pair(name, new_user)); // adds new user to the map
        }

        map<string, User*>::iterator find_it = all_users.find(name);

        while(!ss.fail())
        {
            string follows;
            ss >> follows;

            if(follows != "")
            {
                map<string, User*>::iterator follow_it = all_users.find(follows);
                if (follow_it == all_users.end()) // if follower isn't already in the map
                {
                    User* new_user = new User(follows);
                    all_users.insert(make_pair(follows, new_user)); // adds new follower to the map
                }

                map<string, User*>::iterator add_it = all_users.find(follows);
                if(add_it != all_users.end())
                {
                    (find_it->second)->addFollowing(add_it->second);
                }
            }
        }
    }

    string line;
    std::getline(ifile, line);
    while(!ifile.fail())
    {
        if(line != "") // skips blank lines
        {
            stringstream ss(line);
            DateTime tweet_date;

            ss >> tweet_date; // stores the date of the tweet

            string tweet_name;
            ss >> tweet_name; // stores the author of the tweet

            string tweet_text;
            std::getline(ss, tweet_text); // stores the text of the tweet

            addTweet(tweet_name, tweet_date, tweet_text); // adds tweet
        }
        std::getline(ifile, line);
    }
    return false;
}

void TwitEng::addTweet(const string& username, const DateTime& time, const string& text)
{
    map<string, User*>::iterator it = all_users.find(username); // finds the user
    if (it == all_users.end()) // makes a new user if they didn't already exist
    {
        User* new_user = new User(username);
        all_users.insert(make_pair(username, new_user)); 
    }

    map<string, User*>::iterator new_it = all_users.find(username);
    if (new_it != all_users.end())
    {
        Tweet* new_tweet = new Tweet(new_it->second, time, text);
        all_tweets.push_back(new_tweet); // adds tweet to the main tweet vector
        new_it->second->addTweet(new_tweet); // adds tweet to the user's vector
        set<string> store_hash = new_tweet->hashTags();
        if(store_hash.size() > 0) // if there's at least one hashtag in the tweet
        {
            for(set<string>::iterator set_it = store_hash.begin(); set_it != store_hash.end(); ++set_it)
            {
                string current = *set_it;
                map<string, vector<Tweet*>>::iterator hashtag_it = hashtags_tweets.find(current);
                if (hashtag_it != hashtags_tweets.end()) // if the hashtag is found, puts into vector
                {
                    (hashtag_it->second).push_back(new_tweet);
                }
                else // otherwise creates a new string/vector pair
                {
                    vector<Tweet*> new_hashtag;
                    new_hashtag.push_back(new_tweet);
                    hashtags_tweets.insert(make_pair(current, new_hashtag));
                }
            } 
        }
    }
}

vector<Tweet*> TwitEng::search(vector<string>& terms, int strategy)
{
    vector<Tweet*> results;
    if(strategy == 0) // AND
    {
        // find the vector of tweets with first entered hashtag
        map<string, vector<Tweet*>>::iterator it = hashtags_tweets.find(terms[0]);
        if(it != hashtags_tweets.end())
        {
            vector<Tweet*> first_hash = it->second;
            for(unsigned int i=0; i<first_hash.size(); i++) // for every tweet that matches the first hashtag
            {
                bool intersects = true;
                for(unsigned int j=0; j<terms.size(); j++)
                {
                    set<string> check_tweets = first_hash[i]->hashTags(); // check if it has every other hashtag
                    if(check_tweets.find(terms[j]) == check_tweets.end())
                    {
                        intersects = false;
                        break;
                    }
                }
                if(intersects)
                {
                    results.push_back(first_hash[i]);
                }
            }
        }
        return results;
    }
    else if(strategy == 1) // OR
    {
        set<Tweet*> check_results; // to eliminate duplicates, copies over to vector later
        for(unsigned int i=0; i<terms.size(); i++) // for every search term
        {
            map<string, vector<Tweet*>>::iterator it = hashtags_tweets.find(terms[i]);
            if(it != hashtags_tweets.end()) // finds the hashtag in the map
            {
                for(unsigned int j=0; j<it->second.size(); j++) // for every matching tweet
                {
                    if(check_results.find(it->second[j]) == check_results.end()) // inserts only if tweet isn't found
                    {
                        check_results.insert(it->second[j]);
                    }
                }
            }
        }
        for(set<Tweet*>::iterator it = check_results.begin(); it != check_results.end(); ++it)
        {
            results.push_back(*it); // copies over all tweets from set into vector
        }
    }
    return results;
}

void TwitEng::dumpFeeds()
{
    map<string, User*>::iterator it;
    for(it = all_users.begin(); it != all_users.end(); ++it) // for every user
    {
        string file_name;
        file_name = it->first + ".feed"; // names a new file
        ofstream ofile(file_name);
        ofile << it->first << endl; // first line is name
        vector<Tweet*> feed_tweet = (it->second)->getFeed();
        for (unsigned int i=0; i<feed_tweet.size(); i++) // getFeed() returns vector of Tweet*
        {
            ofile << *(feed_tweet[i]); // dereferences tweet and outputs using overloaded <<
            if(i < feed_tweet.size()-1)
            {
                ofile << endl; // takes care of newlines
            }
        }
        ofile.close();
    }
}