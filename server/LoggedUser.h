#pragma once

#include <string>

class LoggedUser
{
public:
	LoggedUser();
	LoggedUser(const std::string& username);
	std::string getUsername() const;
	void setUsername(const std::string& username);
private:
	std::string m_username;
};

