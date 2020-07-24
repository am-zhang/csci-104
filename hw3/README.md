HW3 consists of one main file that can be compiled and run:  
twitter.cpp

Our semester project involved modelling a microblog site such as Twitter. At a high level, a microblog site is based on the following components:  
1. Users that follow other users (this forms a graph with users as vertices and follow relationships as directed edges)  
2. A timeline for each user (user x) that shows their posts as well as others' posts from those that user x follows and eventually posts with appropriate @ mentions  
3. Quick lookup/indexing of tagged keywords (hashtags)  

For the first part of the project, we focused on parsing users and their feeds as well as searching for tweets based on hashtags.  
For now, while texts may contain @username mentions we simply show these as text in the tweet.  

We also added the ability to search tweets by hashtags. Once the program loads, we allow the user to search for tweets that match a given set of hashtags or quit and write the feeds. In an AND search the user may provide any number of hashtags and see which tweets match ALL of those hashtags. An OR search yields any tweet that matches ANY of the provided hashtags. This search runs in time O(k log n) where n = number of hashtags used in the system (at the cost of some memory storage).

This can be compiled by entering _make_ at the command line.  

A sample invocation of twitter would be:  
./twitter twitter.dat  

This program relies on changes made to:  
user.cpp  
datetime.cpp  
tweet.cpp  
twiteng.cpp  
cmdhandler.cpp  

Please check the comments in the above programs for any clarifications.
