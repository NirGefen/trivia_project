/************************************************************
@ File: ServrConfigurationException.h
@ Description: A general class that represents an exception related to the config of the server
*************************************************************/

#pragma once

// INCLUDES
#include <exception>
#include <string>
#include <fstream>

class ServerConfigurationException :
	public std::exception
{
public:
	ServerConfigurationException(const std::string& errorDetails);
	virtual const char* what() const override;
private:
	std::string m_errorMessage;
};

