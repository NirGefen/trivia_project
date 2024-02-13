#include "ServerConfigurationInvalidJsonException.h"

ServerConfigurationInvalidJsonException::ServerConfigurationInvalidJsonException(const std::string& fileName, const std::string& jsonErrorMessage) : 
	ServerConfigurationException("[ ServerConfigurationInvalidJsonException ] -> Invalid Json Formatting in configuration file " + fileName + ", Error: " + jsonErrorMessage )
{
}
