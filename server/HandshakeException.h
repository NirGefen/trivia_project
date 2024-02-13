#pragma once

#include <exception>
#include <string>

class HandshakeException :
	public std::exception
{
public:
	HandshakeException(const std::string& errorDetails);
	virtual const char* what() const override;
private:
	std::string m_errorMessage;
};

