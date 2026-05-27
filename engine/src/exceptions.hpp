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
			enum { Warning, Error, Recoverable_Warning, Recoverable_Error } type;
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
		private:
			Hook _prep = [](const String&) { return true; };
			Hook _comp = [](const String&) { return true; };
			Hook _rest = [](const String&) { return true; };
		private:
			std::function<void()> _does_log = [] {};
			std::function<void()> _pass_log = [] {};
			std::function<void()> _warn_log = [] {};
			std::function<void()> _fail_log = [] {};
		public:
			explicit Runner(Func&& func, Args&&... args);
		public:
			Runner& prepare (Hook func);	// register _prep
			Runner& restore (Hook func);	// register _rest
			Runner& complete(Hook func);	// register _comp
		public:
			template<typename... FArgs> Runner& does(FArgs&&... args) noexcept;
			template<typename... FArgs> Runner& pass(FArgs&&... args) noexcept;
			template<typename... FArgs> Runner& warn(FArgs&&... args) noexcept;
			template<typename... FArgs> Runner& fail(FArgs&&... args) noexcept;
		public:
			// Invoke and get the return value/result if evaluation succeeded
			std::invoke_result_t<Func, Args...> execute(const String& context = "Attempt");
		};

		// Attempt::to( do, arguments... ).<chain>;
		template<typename Func, typename... Args>
		Runner<std::decay_t<Func>, std::decay_t<Args>...> to(Func&& func, Args&&... args);
	};

	template<typename T> using Expected = std::expected<T, Attempt::Status>;
}

#include "exceptions.inl"