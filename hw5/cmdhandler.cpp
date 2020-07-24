#include "cmdhandler.h"
#include "util.h"
using namespace std;

QuitHandler::QuitHandler()
{

}

QuitHandler::QuitHandler(Handler* next)
  : Handler(next)
{

}

bool QuitHandler::canHandle(const std::string& cmd) const
{
	return cmd == "QUIT";

}

Handler::HANDLER_STATUS_T QuitHandler::process(TwitEng* eng, std::istream& instr) const
{
	eng->dumpFeeds();
	return HANDLER_QUIT;
}

AndHandler::AndHandler()
{

}

AndHandler::AndHandler(Handler* next)
	: Handler(next)
{

}

bool AndHandler::canHandle(const std::string& cmd) const
{
	return cmd == "AND";
}

Handler::HANDLER_STATUS_T AndHandler::process(TwitEng* eng, std::istream& instr) const
{
	vector<string> terms;
	string word;
	instr >> word;
	if (instr.fail())
	{
		return HANDLER_ERROR;
	}
	while(!instr.fail())
	{
		convLower(word);
		terms.push_back(word);
		word.clear();
		instr >> word;
	}
	vector<Tweet*> results = eng->search(terms, 0);
	displayHits(results);
	return HANDLER_OK;
}

OrHandler::OrHandler()
{

}

OrHandler::OrHandler(Handler* next)
	: Handler(next)
{

}

bool OrHandler::canHandle(const std::string& cmd) const
{
	return cmd == "OR";
}

Handler::HANDLER_STATUS_T OrHandler::process(TwitEng* eng, std::istream& instr) const
{
	vector<string> terms;
	string word;
	instr >> word;
	if (instr.fail())
	{
		return HANDLER_ERROR;
	}
	while(!instr.fail())
	{
		convLower(word);
		terms.push_back(word);
		word.clear();
		instr >> word;
	}
	vector<Tweet*> results = eng->search(terms, 1);
	displayHits(results);
	return HANDLER_OK;
}

TweetHandler::TweetHandler()
{

}

TweetHandler::TweetHandler(Handler* next)
	: Handler(next)
{

}

bool TweetHandler::canHandle(const std::string& cmd) const
{
	return cmd == "TWEET";
}

Handler::HANDLER_STATUS_T TweetHandler::process(TwitEng* eng, std::istream& instr) const
{
	DateTime tweet_now;
	string tweet_user;
	instr >> tweet_user;
	if (instr.fail())
	{
		return HANDLER_ERROR;
	}
	string tweet_text;
	getline(instr, tweet_text);
	if (instr.fail())
	{
		return HANDLER_ERROR;
	}
	eng->addTweet(tweet_user, tweet_now, tweet_text);
	return HANDLER_OK;
}

FollowHandler::FollowHandler()
{

}

FollowHandler::FollowHandler(Handler* next)
	: Handler(next)
{

}

bool FollowHandler::canHandle(const std::string& cmd) const
{
	return cmd == "FOLLOW";
}

Handler::HANDLER_STATUS_T FollowHandler::process(TwitEng* eng, std::istream& instr) const
{
	string user;
	instr >> user;
	if (instr.fail())
	{
		return HANDLER_ERROR;
	}

	string follow;
	instr >> follow;
	if (instr.fail())
	{
		return HANDLER_ERROR;
	}

	eng->addFollower(user, follow);
	return HANDLER_OK;
}

SaveHandler::SaveHandler()
{

}

SaveHandler::SaveHandler(Handler* next)
	: Handler(next)
{

}

bool SaveHandler::canHandle(const std::string& cmd) const
{
	return cmd == "SAVE";
}

Handler::HANDLER_STATUS_T SaveHandler::process(TwitEng* eng, std::istream& instr) const
{
	string filename;
	instr >> filename;
	if (instr.fail())
	{
		return HANDLER_ERROR;
	}
	eng->save(filename);
	return HANDLER_OK;
}