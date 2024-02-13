#include "Game.h"

Game::Game(const std::vector<GameQuestion>& questions, const Room& room) :
	m_questions(questions), m_maxTimePerQuestion(room.getData().secondsPerQuestion)
{
	for (const auto& username : room.getAllUsernames())
	{
		this->m_players.insert({ username, GameData(questions.size()) });
	}
}


Responses::GetQuestionResponse Game::getQuestionForUser(const std::string& username)
{
	Responses::GetQuestionResponse response;
	if (this->m_players.find(username) == this->m_players.end())
	{
		throw GameException("user not found in game map! this should not happen. immediately fix the code");
	}
	else
	{
		if (this->m_players[username].isDone())
		{
			response.category = "";
			response.question = "";
			response.status = 0;
			response.answers = std::vector<Responses::GetQuestionResponseAnswer>();
		}
		else if (this->m_players[username].gotQuestion())
		{
			throw GameException("You already got your question!");
		}
		else
		{
			response.status = 1;
			response.category = this->m_questions[this->m_players[username].getCurrentQuestionIndex()].getCategory();
			response.question = this->m_questions[this->m_players[username].getCurrentQuestionIndex()].getQuestion();
			response.answers.resize(AMOUNT_OF_GAME_ANSWERS);
			std::vector<std::string> questionAnswers = this->m_questions[this->m_players[username].getCurrentQuestionIndex()].getAnswers();
			std::vector<unsigned int> idMem = this->m_players[username].getIdMemory();
			for (unsigned int i = 0; i < AMOUNT_OF_GAME_ANSWERS; ++i)
			{
				response.answers[i].answerId = i;
				response.answers[i].answer = questionAnswers[idMem[i]];
			}
			this->m_players[username].setGotQuestion(true);

			this->m_players[username].setStartTime(std::chrono::steady_clock::now());
		}
	}
	return response;
}

Responses::SubmitAnswerResponse Game::submitAnswer(const std::string& username, unsigned int answerId)
{
	std::chrono::steady_clock::time_point submitTime = std::chrono::steady_clock::now();
	double timeTook = 0;
	Responses::SubmitAnswerResponse response;
	response.correctAnswerId = 0;
	if (this->m_players.find(username) == this->m_players.end())
	{
		throw GameException("user not found in game map! this should not happen. immediately fix the code");
	}
	else
	{
		timeTook = (std::chrono::duration_cast<std::chrono::microseconds>(submitTime - this->m_players[username].getStartTime()).count()) / MICRO_TO_SEC;
		if (!this->m_players[username].gotQuestion())
		{
			throw GameException("You did not start a question!");
		}
		this->m_players[username].setGotQuestion(false);
		if (timeTook > this->m_maxTimePerQuestion)
		{
			response.status = 0;

		}
		else
		{
			response.status = 1;
		}

		// finding the correct answer id
		std::vector<unsigned int> idMem = this->m_players[username].getIdMemory();
		for (unsigned int i = 0; i < AMOUNT_OF_GAME_ANSWERS; ++i)
		{
			if (this->m_questions[this->m_players[username].getCurrentQuestionIndex()].isCorrect(idMem[i]))
			{
				response.correctAnswerId = i;
			}
		}
		this->m_players[username].update(response.correctAnswerId == answerId, timeTook, this->m_maxTimePerQuestion);

	}
	return response;
}

Responses::GetGameResultsResponse Game::getGameResults() const
{
	Responses::GetGameResultsResponse response;
	Responses::PlayerResults currPlayerResults;
	if (!this->isGameFinished())
	{
		response.status = 0;
	}
	else
	{
		response.status = 1;

		for (auto userData : this->m_players)
		{
			currPlayerResults.username = userData.first;
			currPlayerResults.averageAnswerTime = userData.second.getAverageAnswerTime();
			currPlayerResults.correctAnswerCount = userData.second.getCorrectAnswerCount();
			currPlayerResults.wrongAnswerCount = userData.second.getIncorrectAnswerCount();
			response.results.push_back(currPlayerResults);
		}
	}
	return response;
}

void Game::removePlayer(const std::string & username)
{
	if (this->m_players.find(username) == this->m_players.end())
	{
		throw GameException("user not found in game map! this should not happen. immediately fix the code");
	}
	else
	{
		this->m_players[username].forceFinish();
	}
	
}

bool Game::isGameFinished() const
{
	return std::all_of(this->m_players.begin(), this->m_players.end(), [](const std::pair<std::string, GameData>& tested) {
		return tested.second.isDone();
	});

}

unsigned int Game::getActivePlayers() const
{
	unsigned int count = 0;
	for (const auto& player : this->m_players)
	{
		if (!player.second.isForcedDone())
		{
			count++;
		}
	}
	return count;
}