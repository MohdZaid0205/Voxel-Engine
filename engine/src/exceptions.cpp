#include "exceptions.hpp"

Engine::Attempt::Status 
Engine::Attempt::makeWarning(String name, String message){
	return Status{ Status::WARNING, name, message };
}

Engine::Attempt::Status 
Engine::Attempt::makeError(String name, String message){
	return Status{Status::ERROR, name, message};
}

Engine::Attempt::Status
Engine::Attempt::makeRecoverableWarning(String name, String message){
	return Status{ Status::RECOVERABLE_WARNING, name, message };
}

Engine::Attempt::Status 
Engine::Attempt::makeRecoverableError(String name, String message){
	return Status{Status::RECOVERABLE_ERROR, name, message};
}

// TEMPLATED IMPLEMENTATION ARE PRESENT IN HEADER FILE ITSELF