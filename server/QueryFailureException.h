#pragma once

#include <exception>
#include <string>
class QueryFailureException :
	public std::exception
{
public:
	QueryFailureException(const std::string& errorDetails);
	virtual const char* what() const override;
private:
	std::string m_errorMessage;
};