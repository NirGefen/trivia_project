#pragma once

#include <exception>
#include <string>
class SocketManagerException : public std::exception
{
public:
	SocketManagerException(const std::string& errorDetails);
	virtual const char* what() const override;
private:
	std::string m_errorMsg;
};

