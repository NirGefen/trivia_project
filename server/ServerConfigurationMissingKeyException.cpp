#include "ServerConfigurationMissingKeyException.h"

ServerConfigurationMissingKeyException::ServerConfigurationMissingKeyException(const std::string& key) :
	ServerConfigurationException("[ ServerConfigurationMissingKeyException ] -> Missing Key: " + key)
{
}
