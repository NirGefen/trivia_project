#include "GameException.h"

GameException::GameException(const std::string& errorDetails) :
	m_errorMessage(errorDetails)
{
}

const char* GameException::what() const
{
	return this->m_errorMessage.c_str();
}
