#include "InvalidJsonException.h"

InvalidJsonException::InvalidJsonException(const std::string& errorDetails) :
	m_errorMsg("Invalid Json Format: " + errorDetails)
{
}

const char* InvalidJsonException::what() const
{
	return m_errorMsg.c_str();
}
