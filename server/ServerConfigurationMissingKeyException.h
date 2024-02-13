/************************************************************
@ File: ServrConfigurationMissingKeyException.h
@ Description: A class that represents a missing key server configuration exception
*************************************************************/

#pragma once

// INCLUDES

#include "ServerConfigurationException.h"
class ServerConfigurationMissingKeyException :
	public ServerConfigurationException
{
public:
	ServerConfigurationMissingKeyException(const std::string& key);
};

