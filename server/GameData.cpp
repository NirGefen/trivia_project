#include "GameData.h"

GameData::GameData(unsigned int questionCount) :
	m_averageAnswerTime(0), m_correctAnswerCount(0), m_wrongAnswerCount(0), m_forcedDone(false), m_gotQuestion(false)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	this->m_questionPermutation.resize(questionCount);
	this->m_idMemory.resize(AMOUNT_OF_GAME_ANSWERS);
	for (unsigned int i = 0; i < questionCount; ++i)
	{
		this->m_questionPermutation[i] = i;
	}
	for (unsigned int i = 0; i < AMOUNT_OF_GAME_ANSWERS; ++i)
	{
		this->m_idMemory[i] = i;
	}
	std::shuffle(this->m_questionPermutation.begin(), this->m_questionPermutation.end(), rng);
	std::shuffle(this->m_idMemory.begin(), this->m_idMemory.end(), rng);
}

// returns the amount of questions if the user is done.
unsigned int GameData::getCurrentQuestionIndex() const
{
	if (this->isDone())
	{
		return this->m_questionPermutation.size();
	}
	return this->m_questionPermutation[this->getAmntTotalQuestionsAnswered()];
}

unsigned int GameData::getAmntTotalQuestionsAnswered() const
{
	return this->m_wrongAnswerCount + this->m_correctAnswerCount;
}

unsigned int GameData::getCorrectAnswerCount() const
{
	return this->m_correctAnswerCount;
}

unsigned int GameData::getIncorrectAnswerCount() const
{
	return this->m_wrongAnswerCount;
}

double GameData::getAverageAnswerTime() const
{
	return this->m_averageAnswerTime;
}

void GameData::update(bool wasCorrect, double answerTime, double maxTimePerQuestion)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	unsigned int totalQuestionsAnswered = this->getAmntTotalQuestionsAnswered();
	this->m_averageAnswerTime = (std::min(this->m_averageAnswerTime, maxTimePerQuestion) * (totalQuestionsAnswered) + answerTime) / ((double)totalQuestionsAnswered + 1);
	if (answerTime <= maxTimePerQuestion)
	{
		if (wasCorrect)
		{
			this->m_correctAnswerCount++;
		}
		else
		{
			this->m_wrongAnswerCount++;
		}
	}
	else
	{
		this->m_wrongAnswerCount++;
	}
	std::shuffle(this->m_idMemory.begin(), this->m_idMemory.end(), rng); // updating the id mapping

}

bool GameData::isDone() const
{
	return (this->getAmntTotalQuestionsAnswered() >= this->m_questionPermutation.size()) || this->m_forcedDone;
}

bool GameData::isForcedDone() const
{
	return this->m_forcedDone;
}

std::vector<unsigned int> GameData::getIdMemory() const
{
	return this->m_idMemory;
}

std::chrono::steady_clock::time_point GameData::getStartTime() const
{
	return this->m_startTime;
}

void GameData::setStartTime(std::chrono::steady_clock::time_point startTime)
{
	this->m_startTime = startTime;
}

void GameData::forceFinish()
{
	this->m_forcedDone = true;
}

bool GameData::gotQuestion()
{
	return this->m_gotQuestion;
}

void GameData::setGotQuestion(bool gotQuestion)
{
	this->m_gotQuestion = gotQuestion;
}
