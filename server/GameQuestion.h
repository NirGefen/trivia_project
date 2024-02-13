#pragma once

#include <string>
#include <vector>
class GameQuestion
{
public:
	GameQuestion() : m_question(""), m_category(""), m_correctAnswerIndex(0) {};
	GameQuestion(const std::string& question, const std::string& category, const std::vector<std::string> answers, unsigned int correctAnswerIndex = 0);
	bool isCorrect(unsigned int answerIndex) const;
	std::string getQuestion() const;
	std::string getCategory() const;
	std::vector<std::string> getAnswers() const;
	GameQuestion& operator =(const GameQuestion& other);
	GameQuestion(const GameQuestion& other);
private:
	std::string m_question;
	std::string m_category;
	std::vector<std::string> m_answers;
	unsigned int m_correctAnswerIndex;

};

