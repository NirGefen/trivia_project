#include "SqliteDatabase.h"

/***************************************************************
 @ brief: dtor of SqliteDatabase
 [>>] Void
 [<<] X
****************************************************************/
SqliteDatabase::~SqliteDatabase()
{
	this->close();
}

/***************************************************************
 @ brief: empty ctor of SqliteDatabase
 [>>] Void
 [<<] X
****************************************************************/
SqliteDatabase::SqliteDatabase() :
	m_dbHandle(nullptr)
{
	this->open();
}

/***************************************************************
 @ brief: closes the handle to the database of the instance (if it's not nullptr, otherwise nothing occurs)
 [>>] Void
 [<<] Void
****************************************************************/
void SqliteDatabase::close()
{
	if (this->m_dbHandle != nullptr)
	{
		sqlite3_close(this->m_dbHandle);
		this->m_dbHandle = nullptr;
	}
}

/***************************************************************
 @ brief: opens a handle to the database for the instance (only if the handle pointer is null, otherwise nothing happens)
 [>>] Void
 [<<] bool: whether or not the database was succesfully opened (NOTE: if m_dbHandle is not null false will be returned)
****************************************************************/
bool SqliteDatabase::open()
{
	bool success = true;
	if (this->m_dbHandle == nullptr)
	{
		if (sqlite3_open(DB_NAME, &this->m_dbHandle) != SQLITE_OK) // failed to open database
		{
			this->m_dbHandle = nullptr;
			success = false;
		}
		this->initializeTable();
	}
	else
	{
		success = false;
	}
	return success;
}

/***************************************************************
 @ brief: callback that sets a bool pointed to by data to true
 [>>] default callback args, data: the pointer to the boolean to be set to true
 [<<] int (default callback return val)
****************************************************************/
int SqliteDatabase::cb_setBoolTrue(void* data, int argc, char** argv, char** azColName)
{
	if (data != nullptr)
	{
		*((bool*)data) = true;
	}
	return 0;
}

/***************************************************************
 @ brief: checks whether or not a user with a given username exists
 [>>] const std::string& username: the username to be checked
 [<<] bool: whether or not there exists a user with such a username
****************************************************************/
bool SqliteDatabase::doesUserExist(const std::string& username) const
{
	bool userExists = false;
	std::string query = "SELECT * FROM USERS WHERE NAME='" + username + "';";
	this->executeQuery(query, this->cb_setBoolTrue, &userExists);
	return userExists;
}

/***************************************************************
 @ brief: checks whether or not a user with a given username exists and his password matches a given password.
 [>>] const std::string& username: the username to be tested in the query
 [>>] const std::string& password: the password in question of the user
 [<<] bool: whether or not there exists a user with such a username and their password matches the given password
****************************************************************/
bool SqliteDatabase::doesPasswordMatch(const std::string& username, const std::string& password) const
{
	bool passwordMatches = false;
	std::string query = "SELECT * FROM USERS WHERE NAME='" + username + "' AND PASSWORD='" + password + "';";  // fix sql injection in version 5
	this->executeQuery(query, this->cb_setBoolTrue, &passwordMatches);
	return passwordMatches;
}

/***************************************************************
 @ brief: adds a new user entry to the database with given values
 [>>] const std::string& username: the username for the user-entry to be added
 [>>] const std::string& password: the password for the user-entry to be added
 [>>] const std::string& email: the email for the user-entry to be added
 [<<] Void
****************************************************************/
void SqliteDatabase::addNewUser(const std::string& username, const std::string& password, const std::string& email) const
{
	this->executeQuery("INSERT INTO USERS (NAME, PASSWORD, MAIL) VALUES('" + username + "', '" + password + "', '" + email + "');");
	int id = -1;
	id = this->getUserId(username);
	this->executeQuery("INSERT INTO STATISTICS (USER_ID, AVERAGE_ANSWER_TIME, CORRECT_ANSWERS_AMOUNT, INCORRECT_ANSWERS_AMOUNT, TOTAL_GAMES_PLAYED_AMOUNT) VALUES(" + std::to_string(id) + ", 0.0, 0, 0, 0);");


}

/***************************************************************
 @ brief: get a random list of trivia questions from the database with a given demanded length (amount of questions).
 [>>] unsigned int amount: the demanded amount of questions
 [<<] std::list<Trivia::Question>: the list of the queried questions (NOTE: if amount > the amount of questions in the database then simply all of the question in the database will be returned)
****************************************************************/
std::list<Trivia::Question> SqliteDatabase::getQuestions(unsigned int amount) const
{
	std::list<Trivia::Question> outList;
	cb_getQuestionParams callbackParams{ &outList, this };
	if (amount != 0)
	{
		this->executeQuery("SELECT * FROM QUESTIONS ORDER BY RANDOM() LIMIT " + std::to_string(amount) + ";", this->cb_getQuestions, &callbackParams);
	}
	return outList;
}

/***************************************************************
 @ brief: adds all questions in a given list of questions to the database
 [>>] const std::list<Trivia::Question>& questionList: the list of the questions to be added
 [<<] Void
****************************************************************/
void SqliteDatabase::addQuestions(const std::list<Trivia::Question>& questionList) const
{
	for (const auto& question : questionList)
	{
		try
		{
			this->addQuestion(question);
		}
		catch (QueryFailureException & e)
		{
		}
	}
}

/***************************************************************
 @ brief: returns the average answer time of a user whose username is given, or a negative number of the user does not exist
 [>>] const std::string& username: the username of the queried user
 [<<] double: the queried average answer time / a negative number if the user does not exist in the database
****************************************************************/
double SqliteDatabase::getPlayerAverageAnswerTime(const std::string& username) const
{
	double avg = -1.0;
	int id = 0;

	id = this->getUserId(username);
	if (id >= 0)
	{
		this->executeQuery("SELECT AVERAGE_ANSWER_TIME FROM STATISTICS WHERE USER_ID = " + std::to_string(id) + ";", this->cb_setDouble, &avg);
	}
	return avg;
}

/***************************************************************
 @ brief: returns the total number of correctly answered questions of a user whose username is given, or a negative number of the user does not exist
 [>>] const std::string& username: the username of the queried user
 [<<] double: the queried total number of correctly answered questions / a negative number if the user does not exist in the database
****************************************************************/
int SqliteDatabase::getNumOfCorrectAnswers(const std::string& username) const
{
	int totalCorrectAnswers = -1;
	int id = 0;

	id = this->getUserId(username);
	if (id >= 0)
	{
		this->executeQuery("SELECT CORRECT_ANSWERS_AMOUNT FROM STATISTICS WHERE USER_ID = " + std::to_string(id) + ";", this->cb_setInt, &totalCorrectAnswers);
	}
	return totalCorrectAnswers;
}

/***************************************************************
 @ brief: returns the total number of  answered questions of a user whose username is given, or a negative number of the user does not exist
 [>>] const std::string& username: the username of the queried user
 [<<] double: the queried total number of answered questions / a negative number if the user does not exist in the database
****************************************************************/
int SqliteDatabase::getNumOfTotalAnswers(const std::string& username) const
{
	int totalIncorrectAnswers = -1;
	int totalAnswers = -1;
	int id = 0;

	id = this->getUserId(username);
	if (id >= 0)
	{
		this->executeQuery("SELECT CORRECT_ANSWERS_AMOUNT FROM STATISTICS WHERE USER_ID = " + std::to_string(id) + ";", this->cb_setInt, &totalAnswers);
		this->executeQuery("SELECT INCORRECT_ANSWERS_AMOUNT FROM STATISTICS WHERE USER_ID = " + std::to_string(id) + ";", this->cb_setInt, &totalIncorrectAnswers);
		totalAnswers += totalIncorrectAnswers;
	}
	return totalAnswers;
}

/***************************************************************
 @ brief: returns the total number of games played of a user whose username is given, or a negative number of the user does not exist
 [>>] const std::string& username: the username of the queried user
 [<<] double: the queried total number of games played / a negative number if the user does not exist in the database
****************************************************************/
int SqliteDatabase::getNumOfPlayerGames(const std::string& username) const
{
	int totalGamesPlayed = -1;
	int id = 0;

	id = this->getUserId(username);
	if (id >= 0)
	{
		this->executeQuery("SELECT TOTAL_GAMES_PLAYED_AMOUNT FROM STATISTICS WHERE USER_ID = " + std::to_string(id) + ";", this->cb_setInt, &totalGamesPlayed);
	}
	return totalGamesPlayed;
}

/***************************************************************
 @ brief: gets usernames of the top scorers, a given amount.
 [>>] unsigned int topAmount: amount of queried top users in the leaderboards
 [<<] std::vector<std::string>: the usernames of the best scored users in the database, up to a given amount (Specifically returns min(total amount of users in database, queried amount) usernames) in order of the best user to the worst user out ouf them.
****************************************************************/
std::vector<std::string> SqliteDatabase::getHighscore(unsigned int topAmount) const
{
	std::vector<std::string> leaderVector;
	this->executeQuery("SELECT USERS.NAME"
		               ", (CASE WHEN ((STATISTICS.CORRECT_ANSWERS_AMOUNT + STATISTICS.INCORRECT_ANSWERS_AMOUNT) = 0 "
					   "OR STATISTICS.AVERAGE_ANSWER_TIME < 0.000001) THEN 0 "
					   "ELSE ((STATISTICS.CORRECT_ANSWERS_AMOUNT / ((STATISTICS.CORRECT_ANSWERS_AMOUNT + STATISTICS.INCORRECT_ANSWERS_AMOUNT) *  STATISTICS.AVERAGE_ANSWER_TIME)) * 10000) END) "
					   "FROM USERS INNER JOIN STATISTICS WHERE USERS.ID = STATISTICS.USER_ID ORDER BY (2) DESC LIMIT " + std::to_string(topAmount) + ";", this->cb_pushBackString, &leaderVector);
	return leaderVector;
}

void SqliteDatabase::updateGameResults(const Responses::PlayerResults& playerResults) const
{
	unsigned int userId = this->getUserId(playerResults.username);
	double oldAverageAnswerTime = this->getPlayerAverageAnswerTime(playerResults.username);
	unsigned int oldCorrectAnswerCount = this->getNumOfCorrectAnswers(playerResults.username);
	unsigned int oldIncorrectAnswerCount = this->getNumOfTotalAnswers(playerResults.username) - oldCorrectAnswerCount;
	unsigned int oldTotalGamesPlayedAmount = this->getNumOfPlayerGames(playerResults.username);
	this->executeQuery(std::string("UPDATE STATISTICS") +
		" SET CORRECT_ANSWERS_AMOUNT = " + std::to_string(oldCorrectAnswerCount + playerResults.correctAnswerCount) +
		", INCORRECT_ANSWERS_AMOUNT = " + std::to_string(oldIncorrectAnswerCount + playerResults.wrongAnswerCount) +
		", TOTAL_GAMES_PLAYED_AMOUNT = " + std::to_string(oldTotalGamesPlayedAmount + 1) +
		", AVERAGE_ANSWER_TIME = " + std::to_string((oldAverageAnswerTime * ((double)oldCorrectAnswerCount + (double)oldIncorrectAnswerCount) + (double)playerResults.averageAnswerTime * ((double)playerResults.correctAnswerCount + (double)playerResults.wrongAnswerCount)) / ((double)oldCorrectAnswerCount + (double)playerResults.correctAnswerCount + (double)oldIncorrectAnswerCount + (double)playerResults.wrongAnswerCount)) +
		" WHERE USER_ID = " + std::to_string(userId) + ";");

}

/***************************************************************
 @ brief: executes a given query with optional callback and data pointer to pass to that call back
 [>>] const std::string& query: the query to be executed
 [>>] int(*callback)(void*, int, char**, char**): optional callback pointer
 [>>] void* data: optional data pointer to pass to the callback
 [<<] std::vector<std::string>: the usernames of the best scored users in the database, up to a given amount (Specifically returns min(total amount of users in database, queried amount) usernames) in order of the best user to the worst user out ouf them.
****************************************************************/
void SqliteDatabase::executeQuery(const std::string& query, int(*callback)(void*, int, char**, char**), void* data, bool shouldTakeMutex) const
{
	if (shouldTakeMutex)
	{
		std::lock_guard<std::mutex> lck(this->m_mtxDbHandle);
		char* errMessage = nullptr;
		if (sqlite3_exec(this->m_dbHandle, query.c_str(), callback, data, &errMessage) != SQLITE_OK)  // should never happen!
		{
			throw QueryFailureException(std::string(errMessage));
		}
	}
	else
	{
		char* errMessage = nullptr;
		if (sqlite3_exec(this->m_dbHandle, query.c_str(), callback, data, &errMessage) != SQLITE_OK)  // should never happen!
		{
			throw QueryFailureException(std::string(errMessage));
		}
	}
}

/***************************************************************
 @ brief: initializes the database file with tables (if they dont exist)
 [>>] Void
 [<<] Void
****************************************************************/
void SqliteDatabase::initializeTable() const
{

	this->executeQuery( // create users table if it doesn't exist yet
		"CREATE TABLE IF NOT EXISTS `USERS` ("
		"`ID` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
		"`NAME`	TEXT NOT NULL UNIQUE,"
		"`PASSWORD`	TEXT NOT NULL,"
		"`MAIL`	TEXT NOT NULL UNIQUE);"
		"CREATE TABLE IF NOT EXISTS `QUESTIONS` ("
		"`ID` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
		"`QUESTION` TEXT NOT NULL UNIQUE,"
		"`ANSWER` TEXT NOT NULL,"
		"`CATEGORY` TEXT NOT NULL);"
		"CREATE TABLE IF NOT EXISTS `INCORRECT_ANSWERS` ("
		"`ID` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
		"`ANSWER` TEXT NOT NULL,"
		"'QUESTION_ID' INTEGER NOT NULL,"
		"FOREIGN KEY (`QUESTION_ID`)"
		"REFERENCES `QUESTIONS` (`ID`)"
		"	ON DELETE CASCADE);"
		" CREATE TABLE IF NOT EXISTS `STATISTICS` ("
		"`ID` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
		"`CORRECT_ANSWERS_AMOUNT` INTEGER NOT NULL,"
		"`INCORRECT_ANSWERS_AMOUNT` INTEGER NOT NULL,"
		"`TOTAL_GAMES_PLAYED_AMOUNT` INTEGER NOT NULL,"
		"`AVERAGE_ANSWER_TIME` REAL NOT NULL,"
		"'USER_ID' INTEGER UNIQUE NOT NULL,"
		"FOREIGN KEY (`USER_ID`)"
		"REFERENCES `USERS` (`ID`)"
		"	ON DELETE CASCADE);"
		);

}

/***************************************************************
 @ brief: adds a given question to the database
 [>>] const Trivia::Question& questionToAdd: the question to be added
 [<<] Void
****************************************************************/
void SqliteDatabase::addQuestion(const Trivia::Question& questionToAdd) const
{
	this->executeQuery("INSERT INTO QUESTIONS (QUESTION, ANSWER, CATEGORY) VALUES ('" + questionToAdd.questionText + "', '" + questionToAdd.correctAnswer + "', '" + questionToAdd.category + "');");
	int id = this->getQuestionId(questionToAdd.questionText);
	for (const auto& incorrectAnswer : questionToAdd.incorrectAnswers)
	{
		this->executeQuery("INSERT INTO INCORRECT_ANSWERS (ANSWER, QUESTION_ID) VALUES ('" + incorrectAnswer + "', " + std::to_string(id) + ");");
	}
}

/***************************************************************
 @ brief: get a question's id based on its text
 [>>] const std::string& questionText: the text of the question the id of which is queried
 [<<] int: the id of the question the text of which was given, or a negative number if it does not exist in the database
****************************************************************/
int SqliteDatabase::getQuestionId(const std::string& questionText) const
{
	int id = -1;
	this->executeQuery("SELECT ID FROM QUESTIONS WHERE QUESTION = '" + questionText + "';", this->cb_setInt, &id);
	return id;
}

/***************************************************************
 @ brief: get a user's id based on its username
 [>>] const std::string& username: the username of the user the id of which is queried
 [<<] int: the id of the user the username of which was given, or a negative number if it does not exist in the database
****************************************************************/
int SqliteDatabase::getUserId(const std::string& username) const
{
	int id = -1;
	this->executeQuery("SELECT ID FROM USERS WHERE NAME = '" + username + "';", this->cb_setInt, &id);
	return id;
}

/***************************************************************
 @ brief: a callback that sets an int to a resultant int in argv[0] to a given address 
 [>>] default callback args, data: the pointer to the int to be set
 [<<] int (default callback return val)
****************************************************************/
int SqliteDatabase::cb_setInt(void* data, int argc, char** argv, char** azColName)
{
	if (data != nullptr && argc > 0)
	{
		*(int*)data = std::stoi(argv[0]);
	}
	return 0;
}


/***************************************************************
 @ brief: a callback that sets a double to a resultant int in argv[0] to a given address
 [>>] default callback args, data: the pointer to the double to be set
 [<<] int (default callback return val)
****************************************************************/
int SqliteDatabase::cb_setDouble(void* data, int argc, char** argv, char** azColName)
{
	if (data != nullptr && argc > 0)
	{
		*(double*)data = std::stod(argv[0]);
	}
	return 0;
}

/***************************************************************
 @ brief: a callback used by getQuestions to store a resultant queried question in a desired struct (of type Trivia::Question), a pointer to is found in a struct that also contains a pointer to the database pointed to by data
 [>>] default callback args, data: the pointer to the struct that contais the database pointer & the question struct pointer
 [<<] int (default callback return val)
****************************************************************/
int SqliteDatabase::cb_getQuestions(void* data, int argc, char** argv, char** azColName)
{
	cb_getQuestionParams* pCallbackParams = nullptr;
	Trivia::Question queriedQuestion;
	if (data != nullptr)
	{
		pCallbackParams = static_cast<cb_getQuestionParams*>(data);
		queriedQuestion.questionText = argv[1];
		queriedQuestion.correctAnswer = argv[2];
		queriedQuestion.category = argv[3];
		queriedQuestion.incorrectAnswers.clear();
		pCallbackParams->pDatabase->executeQuery("SELECT ANSWER FROM INCORRECT_ANSWERS WHERE QUESTION_ID=" + std::string(argv[0]) + ";",
		pCallbackParams->pDatabase->cb_getQuestionIncorrectAnswers, &queriedQuestion, false);
		pCallbackParams->pOutList->push_back(queriedQuestion);
	}
	return 0;
}

/***************************************************************
 @ brief: a callback used by cb_getQuestions to store the queried incorrect answers. data pointed to a Trivia::Question struct to push the queried incorrect answer to its incorrect answer vector
 [>>] default callback args, data: the pointer to the struct be set up with the query results
 [<<] int (default callback return val)
****************************************************************/
int SqliteDatabase::cb_getQuestionIncorrectAnswers(void* data, int argc, char** argv, char** azColName)
{
	Trivia::Question* pQuestion = nullptr;
	if (data != nullptr)
	{
		pQuestion = static_cast<Trivia::Question*>(data);
		pQuestion->incorrectAnswers.push_back(argv[0]);
	}


	return 0;
}

/***************************************************************
 @ brief: a callback for pushing back a string to a vector<string>
 [>>] default callback args, data: the pointer to the vector<string> to push the queried string to
 [<<] int (default callback return val)
****************************************************************/
int SqliteDatabase::cb_pushBackString(void* data, int argc, char** argv, char** azColName)
{
	std::vector<std::string>* pStrVector = nullptr;
	if (data != nullptr)
	{
		pStrVector = static_cast<std::vector<std::string>*>(data);
		pStrVector->push_back(argv[0]);
	}
	return 0;
}

