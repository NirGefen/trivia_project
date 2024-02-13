#pragma once

#include <string>
#include <list>
#include "TriviaQuestionsApi.h"
#include "PlayerResults.h"
class IDatabase
{
public:
	virtual bool doesUserExist(const std::string& username) const = 0;
	virtual bool doesPasswordMatch(const std::string& username, const std::string& password) const = 0;
	virtual void addNewUser(const std::string& username, const std::string& password, const std::string& email) const = 0;
	virtual std::list<Trivia::Question> getQuestions(unsigned int amount) const = 0;
	virtual void addQuestions(const std::list<Trivia::Question>& questionList) const = 0;
	virtual double getPlayerAverageAnswerTime(const std::string& username) const = 0;
	virtual int getNumOfCorrectAnswers(const std::string& username) const = 0;
	virtual int getNumOfTotalAnswers(const std::string& username) const = 0;
	virtual int getNumOfPlayerGames(const std::string& username) const = 0;
	virtual std::vector<std::string> getHighscore(unsigned int topAmount) const = 0;
	virtual void updateGameResults(const Responses::PlayerResults& playerResults) const = 0;

};

