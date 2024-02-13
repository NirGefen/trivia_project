#pragma once

#include <exception>
#include <string>
class InvalidJsonException : public std::exception
{
public:
	InvalidJsonException(const std::string& errorDetails);
	virtual const char* what() const override;
private:
	std::string m_errorMsg;
};

