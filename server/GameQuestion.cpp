#include "GameQuestion.h"

GameQuestion::GameQuestion(const std::string& question, const std::string& category, const std::vector<std::string> answers, unsigned int correctAnswerIndex) :
	m_question(question), m_category(category), m_answers(answers), m_correctAnswerIndex(correctAnswerIndex)
{
}

bool GameQuestion::isCorrect(unsigned int answerIndex) const
{
	return this->m_correctAnswerIndex == answerIndex;
}

std::string GameQuestion::getQuestion() const
{
	return this->m_question;
}

std::string GameQuestion::getCategory() const
{
	return this->m_category;
}

std::vector<std::string> GameQuestion::getAnswers() const
{
	return this->m_answers;
}

GameQuestion& GameQuestion::operator=(const GameQuestion& other)
{
	if (this != &other)
	{
		this->m_answers.clear();
		for (const auto& answer : other.getAnswers())
		{
			this->m_answers.push_back(answer);
		};
		this->m_category = other.m_category;
		this->m_correctAnswerIndex = other.m_correctAnswerIndex;
		this->m_question = other.m_question;
	}
	return *this;
}

GameQuestion::GameQuestion(const GameQuestion& other)
{
	*this = other;
}
