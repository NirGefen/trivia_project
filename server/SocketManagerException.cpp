#include "SocketManagerException.h"

SocketManagerException::SocketManagerException(const std::string& errorDetails) :
	m_errorMsg("[ SocketManagerException ] -> " + errorDetails)
{
}

const char* SocketManagerException::what() const
{
	return m_errorMsg.c_str();
}
