#include "GameUser.h"

/***************************************************************
 @ brief: empty ctor for GameUser
 [>>] Void
 [<<] X
****************************************************************/
GameUser::GameUser()
{
	this->m_username = "";
}

/***************************************************************
 @ brief: ctor for GameUser
 [>>] const std::string& username: the username of the logged user
 [>>] bool isPlaying: whether the player is still in the game or not
 [>>] int questionsAnswered: how many questions the user has answered
 [<<] X
****************************************************************/
GameUser::GameUser(const std::string& username, bool playingStatus, int questionsAnswered)
{
	this->m_username = username;
	this->m_isPlaying = playingStatus;
	this->m_questionsAnswered = questionsAnswered;
}

/***************************************************************
 @ brief: getter for m_username
 [>>] X
 [<<] std::string: m_username
****************************************************************/
std::string GameUser::getUsername() const
{
	return this->m_username;
}

/***************************************************************
 @ brief: setter for m_username
 [>>] const std::string& username: the value to set m_username to
 [<<] X
****************************************************************/
void GameUser::setUsername(const std::string& username)
{
	this->m_username = username;
}

/***************************************************************
 @ brief: getter for m_isPlaying
 [>>] X
 [<<] bool: m_IsPlaying
****************************************************************/
bool GameUser::isPlaying() const
{
	return this->m_isPlaying;
}

/***************************************************************
 @ brief: setter for m_isPlaying
 [>>] const std::string& : the value to set m_username to
 [<<] X
****************************************************************/
void GameUser::setPlayingStatus(const bool playingStatus)
{
	this->m_isPlaying = playingStatus;
}

/***************************************************************
 @ brief: getter for m_questionsAnswered
 [>>] X
 [<<] int: m_questionsAnswered
****************************************************************/
int GameUser::getQuestionsAnswered() const
{
	return this->m_questionsAnswered;
}

/***************************************************************
 @ brief: setter for m_questionsAnswered (increments by one)
 [>>] X
 [<<] X
****************************************************************/
void GameUser::addAnsweredQuestion()
{
	this->m_questionsAnswered++;
}