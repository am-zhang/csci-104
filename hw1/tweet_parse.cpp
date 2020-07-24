#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) 
{

    ifstream ifile(argv[1]);
    if (ifile.fail())
    {
        cout << "Failed to open file!" << endl;
        return 1;
    }

    vector<string> users; // stores unique users
    vector<string> hashtags; // stores unique hashtags

    string word;
    string line;
    int count = 0;

    getline(ifile, line);
    if (ifile.fail()) // checks if first line is valid
    {
        cout << "Failed to extract line." << endl;
        return 1;
    }

    while (!ifile.fail())
    {
        if (line != "") // checks that the line is not empty
        {
            stringstream line_ss(line); // for every line, make a stringstream to parse words
            line_ss >> word;

            while (!line_ss.fail())
            {
                bool unique = true;
                if(word[0] == '@') // checks if the word is a user
                {
                    if (users.size() == 0)
                    {
                        users.push_back(word);
                    }
                    else // checks if unique
                    {
                        for (unsigned int i=0; i<users.size(); i++)
                        {
                            if (word == users[i])
                            {
                                unique = false;
                                break;
                            }
                        }
                        if (unique)
                        {
                            users.push_back(word);
                        }
                    }
                }
                else if(word[0] == '#') // checks if the word is a hashtag
                {
                    if (hashtags.size() == 0)
                    {
                        hashtags.push_back(word);
                    }
                    else // checks if unique
                    {
                        for (unsigned int i=0; i<hashtags.size(); i++)
                        {
                            if (word == hashtags[i])
                            {
                                unique = false;
                                break;
                            }
                        }
                        if (unique)
                        {
                            hashtags.push_back(word);
                        }
                    }
                }
                word.clear();
                line_ss >> word; // checks the next word
            }

            count++; // counts number of lines aka tweets
            word.clear();
            line.clear();
        }
        getline(ifile, line); // gets the next line
        
    }

    cout << "1. Number of tweets=" << count << endl;
    cout << "2. Unique users" << endl;
    for (unsigned int i=0; i<users.size(); i++) 
    {
        cout << users[i].substr(1) << endl; // doesn't print the @
    }
    cout << "3. Unique hashtags" << endl;
    for (unsigned int i=0; i<hashtags.size(); i++) 
    {
        cout << hashtags[i].substr(1) << endl; // doesn't print the #
    }

    return 0;
}