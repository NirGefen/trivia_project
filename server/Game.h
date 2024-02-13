#pragma once

#include "GameData.h"
#include "LoggedUser.h"
#include "Room.h"
#include "GameQuestion.h"
#include "GameException.h"
#include "GetQuestionResponse.h"
#include "SubmitAnswerResponse.h"
#include "GetGameResultsResponse.h"
#include "PlayerResults.h"

#define SUBMIT_SUCCESS_STATUS 1
#define SUBMIT_TOO_LATE_STATUS 0
#define MICRO_TO_SEC 1000000.0
class Game
{
public:
	Game() : m_maxTimePerQuestion(0) {};
	Game(const std::vector<GameQuestion>& questions, const Room& room);
	Responses::GetQuestionResponse getQuestionForUser(const std::string& username);
	Responses::SubmitAnswerResponse submitAnswer(const std::string& username, unsigned int answerId);
	Responses::GetGameResultsResponse getGameResults() const;
	void removePlayer(const std::string& username);
	bool isGameFinished() const ;
	unsigned int getActivePlayers() const;
private:
	std::vector<GameQuestion> m_questions;
	std::map<std::string, GameData> m_players;
	double m_maxTimePerQuestion;
};

