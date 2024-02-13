#include "ServerConfigurationLoadFileException.h"

ServerConfigurationLoadFileException::ServerConfigurationLoadFileException(const std::string& fileName) :
	ServerConfigurationException("[ ServerConfigurationLoadFileException ] -> Error while loading " + fileName)
{
}
