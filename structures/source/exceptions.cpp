#include "exceptions.h"

/*
* @brief constructor for IndexOutOfRange exception
*/
Structures::IndexOutOfRange::IndexOutOfRange(const char* message)
{
	__message = message;
}

/*
* @brief returns exception message for IndexOutOfRange
*/
const char* Structures::IndexOutOfRange::what()
{
	return __message;
}

#pragma endregion

#pragma region ElementNotFoundMethods

/*
* @brief constructor for ElementNotFound exception
*/
Structures::ElementNotFound::ElementNotFound(const char* message)
{
	__message = message;
}

/*
* @brief returns exception message for ElementNotFound
*/
const char* Structures::ElementNotFound::what()
{
	return __message;
}

#pragma endregion
