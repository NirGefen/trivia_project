/************************************************************
@ File: ServrConfigurationInvalidJsonException.h
@ Description: A class that represents an invalid json server configuration exception
*************************************************************/

#pragma once

// INCLUDES
#include "ServerConfigurationException.h"

class ServerConfigurationInvalidJsonException :
	public ServerConfigurationException
{
public:
	ServerConfigurationInvalidJsonException(const std::string& fileName, const std::string&);
};

