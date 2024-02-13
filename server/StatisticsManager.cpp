#include "StatisticsManager.h"

/***************************************************************
 @ brief: ctor for StatisticsManager
 [>>] IDatabase* database: a pointer to the database interface to be used by the manager
 [<<] X
****************************************************************/
StatisticsManager::StatisticsManager(IDatabase* database) :
	m_database(database)
{
}

/***************************************************************
 @ brief: get statistics of a given user with the highscores (NOTE: if username does not exist in the database the return value is undefined. (technically negative numbers). shouldn't happen anyways within the code as this is only called with LoggedUser which we know exists)
 [>>] const std::string& username: the username for the query
 [<<] Responses::GetStatisticsResponse: a struct containing the queried information.
****************************************************************/
Responses::GetStatisticsResponse StatisticsManager::getStatistics(const std::string& username)
{
	Responses::GetStatisticsResponse statsResponse;
	statsResponse.highscores = this->getHighscore();
	statsResponse.userStats = this->getUserStatistics(username);
	return statsResponse;
}

/***************************************************************
 @ brief: get statistics of a given user (NOTE: if username does not exist in the database the return value is undefined. (technically negative numbers). shouldn't happen anyways within the code as this is only called with LoggedUser which we know exists)
 [>>] const std::string& username: the username for the query
 [<<] Responses::UserStatistics: the statistics of the queried user (negative values for most stats if it does not exist. again, we dont need to check here that it exists anyways, this leaves some undefined behaviour, but again, we stuck to a UML that had some design issues)
****************************************************************/
Responses::UserStatistics StatisticsManager::getUserStatistics(const std::string& username)
{
	Responses::UserStatistics userStats;
	userStats.averageAnswerTime = this->m_database->getPlayerAverageAnswerTime(username);
	userStats.totalAnswers = this->m_database->getNumOfTotalAnswers(username);
	userStats.totalCorrectAnswers = this->m_database->getNumOfCorrectAnswers(username);
	userStats.totalGamesPlayed = this->m_database->getNumOfPlayerGames(username);
	userStats.score = (userStats.totalAnswers > 0 && userStats.averageAnswerTime > 0 && userStats.totalCorrectAnswers > 0) ? (userStats.totalCorrectAnswers / (userStats.totalAnswers * (userStats.averageAnswerTime))) * 10000 : 0;
	userStats.username = username;
	return userStats;
}

/***************************************************************
 @ brief: get the statistics of top users
 [>>] Void
 [<<] std::vector<Responses::UserStatistics>: the statistics of the top users (up to a constant amount stored in the constant amount) in order of their scores (top to worst) 
 ****************************************************************/
std::vector<Responses::UserStatistics> StatisticsManager::getHighscore()
{
	const unsigned int amount = 5;
	std::vector<std::string> topUsernames = this->m_database->getHighscore(amount);
	std::vector<Responses::UserStatistics> highScores;
	for (auto user : topUsernames)
	{
		highScores.push_back(this->getUserStatistics(user));
	}
	return highScores;
}

void StatisticsManager::setDatabase(IDatabase* database)
{
	this->m_database = database;
}