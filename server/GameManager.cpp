#include "GameManager.h"

GameManager::GameManager(IDatabase* database) :
	m_database(database), m_idCounter(0)
{
}

unsigned int GameManager::createGame(const Room& room)
{
	std::list<Trivia::Question> queriedQuestionList = this->m_database->getQuestions(room.getData().numOfQuestionsInGame);
	std::vector<GameQuestion> formattedQuestions(queriedQuestionList.size());
	unsigned int currQuestionIndex = 0;
	std::vector<std::string> answers;
	for (const auto& triviaQuestion : queriedQuestionList)
	{
		answers.clear();
		answers.push_back(triviaQuestion.correctAnswer);
		for (const auto& answer : triviaQuestion.incorrectAnswers)
		{
			answers.push_back(answer);
		}
		formattedQuestions[currQuestionIndex] = GameQuestion(triviaQuestion.questionText, triviaQuestion.category, answers);
		currQuestionIndex++;
	}
	this->m_idCounter++;
	Game newGame(formattedQuestions, room);
	std::lock_guard<std::mutex> lck(this->m_mtxGames);
	this->m_games.insert(std::make_pair(this->m_idCounter++, newGame));
	return this->m_idCounter - 1;
}

void GameManager::deleteGame(unsigned int gameId)
{
	if (this->m_games.find(gameId) == this->m_games.end())
	{
		throw GameException("deleteGame: game does not exist. should not be visible to users. if you see this message please send a screenshot to an administrator!");
	}
	Responses::GetGameResultsResponse resultsForStatUpdate = this->m_games[gameId].getGameResults();
	this->m_games.erase(gameId);
	for (const auto& playerResult : resultsForStatUpdate.results)
	{
		try
		{
			this->m_database->updateGameResults(playerResult);
		}
		catch (...)
		{ }
	}

}

Responses::GetQuestionResponse GameManager::getQuestionForUser(const std::string& username, unsigned int gameId)
{
	std::lock_guard<std::mutex> lck(this->m_mtxGames);
	if (this->m_games.find(gameId) == this->m_games.end())
	{
		throw GameException("getQuestionForUser: game does not exist. should not be visible to users. if you see this message please send a screenshot to an administrator!");
	}
	return this->m_games[gameId].getQuestionForUser(username);
}

Responses::SubmitAnswerResponse GameManager::submitAnswer(const std::string& username, unsigned int answerId, unsigned int gameId)
{
	std::lock_guard<std::mutex> lck(this->m_mtxGames);
	if (this->m_games.find(gameId) == this->m_games.end())
	{
		throw GameException("submitAnswer: game does not exist. should not be visible to users. if you see this message please send a screenshot to an administrator!");
	}
	return this->m_games[gameId].submitAnswer(username, answerId);
}

Responses::GetGameResultsResponse GameManager::getGameResults(unsigned int gameId) const
{
	std::lock_guard<std::mutex> lck(this->m_mtxGames);
	if (this->m_games.find(gameId) == this->m_games.end())
	{
		throw GameException("getGameResults: game does not exist. should not be visible to users. if you see this message please send a screenshot to an administrator!");
	}
	return this->m_games.at(gameId).getGameResults();
}


// returns true iff the removedplayer was the last player
bool GameManager::removePlayer(const std::string& username, unsigned int gameId)
{
	bool wasLast = false;
	std::lock_guard<std::mutex> lck(this->m_mtxGames);
	if (this->m_games.find(gameId) == this->m_games.end())
	{
		throw GameException("removePlayer: game does not exist. should not be visible to users. if you see this message please send a screenshot to an administrator!");
	}
	this->m_games[gameId].removePlayer(username);
	if (!this->m_games[gameId].getActivePlayers())
	{
		this->deleteGame(gameId);
		wasLast = true;
	}
	return wasLast;
}

void GameManager::setDatabase(IDatabase* database)
{
	this->m_database = database;
}
