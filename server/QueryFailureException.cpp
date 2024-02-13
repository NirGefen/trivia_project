#include "QueryFailureException.h"

QueryFailureException::QueryFailureException(const std::string& errorDetails) :
	m_errorMessage(errorDetails)
{
}

const char* QueryFailureException::what() const
{
	return this->m_errorMessage.c_str();
}
