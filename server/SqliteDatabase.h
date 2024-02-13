#pragma once

#include <iostream>
#include "IDatabase.h"
#include "sqlite3.h"
#include "include/nlohmann/json.hpp"
#include <algorithm>
#include <string>
#include "QueryFailureException.h"

using json = nlohmann::json;


#define DB_NAME "triviaDB.sqlite"

class SqliteDatabase : public IDatabase
{
public:
	SqliteDatabase();
	~SqliteDatabase();
	bool doesUserExist(const std::string& username) const override;
	bool doesPasswordMatch(const std::string& username, const std::string& password) const override;
	void addNewUser(const std::string& username, const std::string& password, const std::string& email) const override;
	std::list<Trivia::Question> getQuestions(unsigned int amount) const override;
	void addQuestions(const std::list<Trivia::Question>& questionList) const override;
	double getPlayerAverageAnswerTime(const std::string& username) const override;
	int getNumOfCorrectAnswers(const std::string& username) const override;
	int getNumOfTotalAnswers(const std::string& username) const override;
	int getNumOfPlayerGames(const std::string& username) const override;
	std::vector<std::string> getHighscore(unsigned int topAmount) const override;
	void updateGameResults(const Responses::PlayerResults& playerResults) const override;
private:
	sqlite3* m_dbHandle;
	mutable std::mutex m_mtxDbHandle;
	void close();
	bool open();
	void executeQuery(const std::string& query, int(*callback)(void*, int, char**, char**) = nullptr, void* data = nullptr, bool shouldTakeMutex = true) const;
	void initializeTable() const;
	void addQuestion(const Trivia::Question& questionToAdd) const;
	int getQuestionId(const std::string& questionText) const;
	int getUserId(const std::string& username) const;
	static int cb_setBoolTrue(void* data, int argc, char** argv, char** azColName);
	static int cb_setInt(void* data, int argc, char** argv, char** azColName);
	static int cb_setDouble(void* data, int argc, char** argv, char** azColName);
	static int cb_getQuestions(void* data, int argc, char** argv, char** azColName);
	static int cb_getQuestionIncorrectAnswers(void* data, int argc, char** argv, char** azColName);
	static int cb_pushBackString(void* data, int argc, char** argv, char** azColName);
};

typedef struct cb_getQuestionParams
{
	std::list<Trivia::Question>* pOutList;
	const SqliteDatabase* pDatabase;
}cb_getQuestionParams;