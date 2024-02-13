#pragma once

#include <exception>
#include <string>
class RoomMaxPlayersLimitReachedException : public std::exception
{
public:
	RoomMaxPlayersLimitReachedException(unsigned int maxLimit);
	virtual const char* what() const override;
private:
	std::string m_errMessage;
};
