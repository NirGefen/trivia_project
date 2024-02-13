#include "LoggedUser.h"

/***************************************************************
 @ brief: empty ctor for LoggedUser
 [>>] Void
 [<<] X
****************************************************************/
LoggedUser::LoggedUser()
{
	this->m_username = "";
}

/***************************************************************
 @ brief: ctor for LoggedUser
 [>>] const std::string& username: the username of the logged user
 [<<] X
****************************************************************/
LoggedUser::LoggedUser(const std::string& username)
{
	this->m_username = username;
}

/***************************************************************
 @ brief: getter for m_username
 [>>] X
 [<<] std::string: m_username
****************************************************************/
std::string LoggedUser::getUsername() const
{
	return this->m_username;
}

/***************************************************************
 @ brief: setter for m_username
 [>>] const std::string& username: the value to set m_username to
 [<<] X
****************************************************************/
void LoggedUser::setUsername(const std::string& username)
{
	this->m_username = username;
}
