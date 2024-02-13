#pragma once

#include <string>

class GameUser
{
public:
	GameUser();
	GameUser(const std::string& username, bool playingStatus, int questionsAnswered);
	std::string getUsername() const;
	bool isPlaying() const;
	int getQuestionsAnswered() const;
	void setUsername(const std::string& username);
	void setPlayingStatus(bool playingStatus);
	void addAnsweredQuestion();
private:
	std::string m_username;
	bool m_isPlaying;
	int m_questionsAnswered;
};

