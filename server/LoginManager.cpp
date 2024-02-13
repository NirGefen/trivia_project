#include "LoginManager.h"

/***************************************************************
 @ brief: ctor for LoginManager
 [>>] IDatabase* database: a pointer to the database class instance to be used by LoginManager for queries
 [<<] Void
****************************************************************/
LoginManager::LoginManager(IDatabase* database) :
	m_database(database)
{
}

/***************************************************************
 @ brief: signup a new user
 [>>] const std::string& username: the username for the new user
 [>>] const std::string& password: the password for the new user
 [>>] const std::string& email: the email for the new user
 [<<] bool: whether or not the user was signed up successfully (if false is returned then the username was an empty string or a user with such a username already existed
****************************************************************/
bool LoginManager::signup(const std::string& username, const std::string& password, const std::string& email) const
{
	if (!this->m_database->doesUserExist(username) && username.length() && email.length() >= 3 && password.length())
	{
		this->m_database->addNewUser(username, password, email);
		return true;
	}
	return false;
}

/***************************************************************
 @ brief: login a user
 [>>] const std::string& username: the username to login with
 [>>] const std::string& password: the password to login with
 [<<] bool: whether or not the user was logged in successfully (if false is returned, the user is already logged in or the password did not match the username / the username does not exist in the database)
****************************************************************/
bool LoginManager::login(const std::string& username, const std::string& password)
{
	if (!this->isUserLoggedIn(username))
	{
		if (this->m_database->doesPasswordMatch(username, password))
		{
			std::lock_guard<std::mutex> lck(this->m_mtxLoggedUsers);
			this->m_loggedUsers.push_back(LoggedUser(username));
			return true;
		}
	}
	return false;
}

/***************************************************************
 @ brief: logout a user (does nothing if they are not logged in / no user with such a username exists)
 [>>] const std::string& username: the username of the user to logout
 [<<] Void
****************************************************************/
void LoginManager::logout(const std::string& username)
{
	std::lock_guard<std::mutex> lck(this->m_mtxLoggedUsers);
	bool removed = false;
	for (unsigned int i = 0; i < this->m_loggedUsers.size() && !removed; i++)
	{
		if (m_loggedUsers[i].getUsername() == username)
		{
			this->m_loggedUsers.erase(this->m_loggedUsers.begin() + i);
			removed = true;
		}
	}
}

/***************************************************************
 @ brief: set the databse pointer of the LoginManager
 [>>] IDatabase* pDatabase: the address to set the database pointer of the instance to
 [<<] Void
****************************************************************/
void LoginManager::setDatabase(IDatabase* pDatabase)
{
	this->m_database = pDatabase;
}

/***************************************************************
 @ brief: check whether or not a user with a given username exists and is logged in
 [>>] const std::string& username: the queried username
 [<<] bool: whether or not a user with a given username exists and is logged in
****************************************************************/
bool LoginManager::isUserLoggedIn(const std::string& username)
{
	std::lock_guard<std::mutex> lck(this->m_mtxLoggedUsers);
	for (unsigned int i = 0; i < this->m_loggedUsers.size(); i++)
	{
		if (m_loggedUsers[i].getUsername() == username)
		{
			return true;
		}
	}
	return false;
}
