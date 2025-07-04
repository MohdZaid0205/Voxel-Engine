#include "arrays.h"

using namespace Structures;

Structures::Exceptions::IndexOutOfRange::IndexOutOfRange(const char* message){
	__message = message;
}

const char* Structures::Exceptions::IndexOutOfRange::what() noexcept {
	return __message;
}

Structures::Exceptions::ElementNotFound::ElementNotFound(const char* message){
	__message = message;
}

const char* Structures::Exceptions::ElementNotFound::what() noexcept {
	return __message;
}