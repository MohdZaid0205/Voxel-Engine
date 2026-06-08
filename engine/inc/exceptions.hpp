#pragma once

#include "api.hpp"
#include "logging.hpp"

namespace Engine {

	// EXCEPTIONS AND WARNING ----------------------------------------------------------+
	// In general using std::exception adds overhead of creating stack and propagating	|
	// exceptions over the stack and is very resource consuming. Try/catch statements	|
	// introduce unnecessary level of guards that may slowdown the execution speed and	|
	// efficiency of our engine.														|
	// ---------------------------------------------------------------------------------+
	// This module aims to reduce overhead of using exception and make it recoverable.

	// ATTEMPT ::to( do... )

	namespace Attempt {

		struct Status {
			enum { 
				Warning				= 0b01, 
				Error				= 0b10, 
				Recoverable_Warning, 
				Recoverable_Error 
			} type;
			String name;		// .. NAME of WARNING/ERROR
			String mess;		// .. associated MESSAGE
		};

		// constructor for ERRORS and WARNINGS
		struct Status makeWarning				(String name, String message);
		struct Status makeError					(String name, String message);
		struct Status makeRecoverableWarning	(String name, String message);
		struct Status makeRecoverableError		(String name, String message);

		// expected output from an attemptable function


		// RUNNER ----------------------------------------------------------------------+
		// runner is the system that forms the basis of an attempt, runner is inspired	|
		// heavily by transaction pattern, an attempt may or may not be recoverable, and|
		// recoverability is defined as per what type of warning or error is raised by	|
		// the function, transaction always gets prepared but restore only happens if	|
		// underlying error is recoverable.												|
		// -----------------------------------------------------------------------------+

		template<typename Func, typename... Args>
		class Runner {
		private:
			bool _eval = false;
			Func _func;
			std::tuple<Args...> _args;
			std::invoke_result_t<Func, Args...> _result;
		private:
			using Hook = std::function<bool(const String&)>;
