#include "HandshakeException.h"

HandshakeException::HandshakeException(const std::string& errorDetails) :
	m_errorMessage("[ HandshakeException ] -> " + errorDetails)
{

}

const char* HandshakeException::what() const
{
	return this->m_errorMessage.c_str();
}
