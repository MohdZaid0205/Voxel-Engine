#ifndef STRUCTURES_EXCEPTION_H
#define STRUCTURES_EXCEPTION_H

#include <exception>

namespace Structures {

#pragma region MemoryAccessViolationImplementation
/*
* @brief *Memory Access Violation* exception
*
* @details
* Raised when an operation tries to access memory not allocated to process or using nullpointer as
* valid memory and trying to derefernce it.
* 
* @par Usage
* @code
* int* pointer = nullptr;
* int value = *pointer;
* 
* // rather check as follows
* if (pointer) int value = *pointer;
* else throw MemoryAccessVoilation("cannot deal with nullptr");
* @endcode
*/
class MemoryAccessViolation: public std::exception {
private:
	const char* __message;      // store message for exception
public:
	MemoryAccessViolation(const char* message);    // initialize message
	const char* what();                      // return exception message
};
#pragma endregion

#pragma region IndexOutOfRangeImplementation
    /*
    * @brief *Index Out of Range* exception
    *
    * @details
    * Raised when an operation tries to access an index that is outside the valid bounds of a data structure.
    * Commonly used in dynamic containers such as arrays, linked lists, stacks, and queues.
    *
    * @par Usage
    * @code
    * if (index < 0 || index >= size)
    *     throw IndexOutOfRange("Accessed index is out of valid range.");
    * @endcode
    */
    class IndexOutOfRange : public std::exception {
    private:
        const char* __message;      // store message for exception
    public:
        IndexOutOfRange(const char* message);    // initialize message
        const char* what();                      // return exception message
    };
#pragma endregion

#pragma region ElementNotFoundImplementation
    /*
    * @brief *Element Not Found* exception
    *
    * @details
    * Raised when an operation tries to access or remove an element that does not exist in the structure.
    * Useful in scenarios involving search, delete, or conditional access.
    *
    * @par Usage
    * @code
    * if (!contains(element))
    *     throw ElementNotFound("Specified element was not found.");
    * @endcode
    */
    class ElementNotFound : public std::exception {
    private:
        const char* __message;      // store message for exception
    public:
        ElementNotFound(const char* message);    // initialize message
        const char* what();                      // return exception message
    };
#pragma endregion

};

#include "exceptions.inl"

#endif
