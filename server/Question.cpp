#include "Question.h"
const std::string Trivia::Question::k_questionText = "question";
const std::string Trivia::Question::k_correctAnswer = "correct_answer";
const std::string Trivia::Question::k_category = "category";
const std::string Trivia::Question::k_incorrectAnswers = "incorrect_answers";

void Trivia::to_json(json& outputJson, const Trivia::Question& questionToConvert)
{
	outputJson = json{ { Trivia::Question::k_category, questionToConvert.category },
	{ Trivia::Question::k_correctAnswer, questionToConvert.correctAnswer },
	{ Trivia::Question::k_incorrectAnswers, questionToConvert.incorrectAnswers },
	{ Trivia::Question::k_questionText, questionToConvert.questionText } };
}

void Trivia::from_json(const json& jsonToConvert, Trivia::Question& outputQuestion)
{
	jsonToConvert.at(Trivia::Question::k_questionText).get_to(outputQuestion.questionText);
	jsonToConvert.at(Trivia::Question::k_correctAnswer).get_to(outputQuestion.correctAnswer);
	jsonToConvert.at(Trivia::Question::k_category).get_to(outputQuestion.category);
	jsonToConvert.at(Trivia::Question::k_incorrectAnswers).get_to<std::vector<std::string>>(outputQuestion.incorrectAnswers);
}
