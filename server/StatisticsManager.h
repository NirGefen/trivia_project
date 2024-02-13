#pragma once

#include <string>
#include "UserStatistics.h"
#include "IDatabase.h"
#include "GetStatisticsResponse.h"

class StatisticsManager
{
public:
	StatisticsManager() : m_database(nullptr){};
	StatisticsManager(IDatabase* database);
	Responses::GetStatisticsResponse getStatistics(const std::string& username);
	void setDatabase(IDatabase* database);
private:
	IDatabase* m_database;
	Responses::UserStatistics getUserStatistics(const std::string& username);
	std::vector<Responses::UserStatistics> getHighscore();
};
