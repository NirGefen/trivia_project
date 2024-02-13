#pragma once

#include "IDatabase.h"
#include "LoggedUser.h"
#include "QueryFailureException.h"
#include <vector>
#include <mutex>

class LoginManager
{
public:
	LoginManager(IDatabase* database);
	bool signup(const std::string& username, const std::string& password, const std::string& email) const;
	bool login(const std::string& username, const std::string& password);
	void logout(const std::string& username);
	void setDatabase(IDatabase* pDatabase);
private:
	IDatabase* m_database;
	std::vector<LoggedUser> m_loggedUsers;
	mutable std::mutex m_mtxLoggedUsers;
	bool isUserLoggedIn(const std::string& username);
	
};

