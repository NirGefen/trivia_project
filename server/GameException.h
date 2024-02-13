#pragma once

#include <exception>
#include <string>
class GameException :
	public std::exception
{
public:
	GameException(const std::string& errorDetails);
	virtual const char* what() const override;
private:
	std::string m_errorMessage;
};