#include "GameDoesNotExistException.h"

GameDoesNotExistException::GameDoesNotExistException(unsigned int id) :
	m_errMessage("Error! there is no game with id " + std::to_string(id) + " ! Please send a screenshot of this message to the administrators.")
{
}

const char* GameDoesNotExistException::what() const
{
	return this->m_errMessage.c_str();
}
