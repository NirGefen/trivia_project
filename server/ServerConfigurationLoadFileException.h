/************************************************************
@ File: ServrConfigurationLoadFileException.h
@ Description: A class that represents a load file server configuration exception
*************************************************************/

#pragma once

// INCLUDES
#include "ServerConfigurationException.h"

class ServerConfigurationLoadFileException :
	public ServerConfigurationException
{
public:
	ServerConfigurationLoadFileException(const std::string& fileName);
};
