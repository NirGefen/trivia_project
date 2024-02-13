#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

#define AMOUNT_OF_GAME_ANSWERS 4

class GameData
{
public:

	GameData() : m_forcedDone(false), m_gotQuestion(false), m_correctAnswerCount(0), m_wrongAnswerCount(0), m_averageAnswerTime(0){};
	GameData(unsigned int questionCount);
	unsigned int getCurrentQuestionIndex() const;
	unsigned int getAmntTotalQuestionsAnswered() const;
	unsigned int getCorrectAnswerCount() const;
	unsigned int getIncorrectAnswerCount() const;
	double getAverageAnswerTime() const;
	void update(bool wasCorrect, double answerTime, double maxTimePerQuestion);
	bool isDone() const;
	bool isForcedDone() const;
	std::vector<unsigned int> getIdMemory() const;
	std::chrono::steady_clock::time_point getStartTime() const;
	void setStartTime(std::chrono::steady_clock::time_point startTime);
	void forceFinish();
	bool gotQuestion();
	void setGotQuestion(bool gotQuestion);
private:
	bool m_forcedDone;
	bool m_gotQuestion;
	std::vector<unsigned int> m_questionPermutation;
	std::vector<unsigned int> m_idMemory;
	unsigned int m_correctAnswerCount;
	unsigned int m_wrongAnswerCount;
	double m_averageAnswerTime;
	std::chrono::steady_clock::time_point m_startTime;
};