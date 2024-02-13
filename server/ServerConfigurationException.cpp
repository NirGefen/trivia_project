#include "ServerConfigurationException.h"

ServerConfigurationException::ServerConfigurationException(const std::string& errorDetails) : 
	m_errorMessage("[ ServerConfigurationException ] -> " + errorDetails)
{
}

const char* ServerConfigurationException::what() const
{
	return m_errorMessage.c_str();
}
