#include "exceptions.hpp"

Engine::Attempt::Status 
Engine::Attempt::makeWarning(String name, String message){
	return Status{ Status::Warning, name, message };
}

Engine::Attempt::Status 
Engine::Attempt::makeError(String name, String message){
	return Status{Status::Error, name, message};
}

Engine::Attempt::Status
Engine::Attempt::makeRecoverableWarning(String name, String message){
	return Status{ Status::Recoverable_Warning, name, message };
}

Engine::Attempt::Status 
Engine::Attempt::makeRecoverableError(String name, String message){
	return Status{Status::Recoverable_Error, name, message};
}

// TEMPLATED IMPLEMENTATION ARE PRESENT IN HEADER FILE ITSELF