#pragma once
#include "IDatabase.h"
#include "Room.h"
#include "Game.h"
#include <mutex>
#include <map>

class GameManager
{
public:
	GameManager(IDatabase* database);
	~GameManager() {};
	unsigned int createGame(const Room& room);
	Responses::GetQuestionResponse getQuestionForUser(const std::string& username, unsigned int gameId);
	Responses::SubmitAnswerResponse submitAnswer(const std::string& username, unsigned int answerId, unsigned int gameId);
	Responses::GetGameResultsResponse getGameResults(unsigned int gameId) const;
	bool removePlayer(const std::string& username, unsigned int gameId);
	void setDatabase(IDatabase* database);
private:
	void deleteGame(unsigned int gameId);
	mutable std::mutex m_mtxGames;
	unsigned int m_idCounter;
	IDatabase* m_database;
	std::map<unsigned int, Game> m_games;
};

