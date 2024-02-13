#pragma once

#include <exception>
#include <string>
class GameDoesNotExistException : public std::exception
{
public:
	GameDoesNotExistException(unsigned int id);
	virtual const char* what() const override;
private:
	std::string m_errMessage;
};


