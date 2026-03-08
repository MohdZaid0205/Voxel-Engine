#pragma once

#include "api.hpp"

#define ENGINE_CONSOLE_DISABLED 0x66666600

#define ENGINE_CONSOLE_BA_LOG "LOG"
#define ENGINE_CONSOLE_FG_LOG 0xffffff00
#define ENGINE_CONSOLE_BG_LOG 0xffffff00
#define ENGINE_CONSOLE_XX_LOG ENGINE_CONSOLE_DISABLED

#define ENGINE_CONSOLE_BA_INF "INF"
#define ENGINE_CONSOLE_FG_INF 0x6666ff00
#define ENGINE_CONSOLE_BG_INF 0x6666ff00
#define ENGINE_CONSOLE_XX_INF ENGINE_CONSOLE_DISABLED

#define ENGINE_CONSOLE_BA_DBG "DBG"
#define ENGINE_CONSOLE_FG_DBG 0x66ff6600
#define ENGINE_CONSOLE_BG_DBG 0x66ff6600
#define ENGINE_CONSOLE_XX_DBG ENGINE_CONSOLE_DISABLED

#define ENGINE_CONSOLE_BA_WRN "WRN"
#define ENGINE_CONSOLE_FG_WRN 0xffff6600
#define ENGINE_CONSOLE_BG_WRN 0xffff6600
#define ENGINE_CONSOLE_XX_WRN ENGINE_CONSOLE_DISABLED

#define ENGINE_CONSOLE_BA_ERR "ERR"
#define ENGINE_CONSOLE_FG_ERR 0xff666600
#define ENGINE_CONSOLE_BG_ERR 0xff666600
#define ENGINE_CONSOLE_XX_ERR ENGINE_CONSOLE_DISABLED

namespace Engine {

	// Type aliases for terminal color -----------------------------------------------------------------------------+
	using Color = u32;			//< Represents a color code (e.g., for foreground/background terminal colors)		|
	//--------------------------------------------------------------------------------------------------------------+
	// Logging level flags used to categorize log messages

	enum LogLevel {
		OFF = 0b00000,
		LOG = 0b00001,
		INF = 0b00010,
		DBG = 0b00100,
		WRN = 0b01000,
		ERR = 0b10000,
	};

	// Logging priorities used to indicate message importance
	enum LogPriority {
		LOW = 0b001,
		MED = 0b010,
		HIG = 0b100,
	};

	String __fg_color_hex_to_ansi(Color val);
	String __bg_color_hex_to_ansi(Color val);

	template<LogPriority P> String __get_banner(String of, Color fg, Color bg, Color xx);
	template<LogPriority P> String __get_highlight(String on, Color highlight, Color xx);

	template String __get_banner<LOW>(String, Color, Color, Color);
	template String __get_banner<MED>(String, Color, Color, Color);
	template String __get_banner<HIG>(String, Color, Color, Color);

	template String __get_highlight<LOW>(String, Color, Color);
	template String __get_highlight<MED>(String, Color, Color);
	template String __get_highlight<HIG>(String, Color, Color);

	template<typename T, typename... Arg> void __recurse_output(T item, Arg... args);
	inline void __recurse_output();

	namespace Console {
		template<LogPriority P = LOW, typename T, typename... Args>  void Log(T msg, Args... args);
		template<LogPriority P = LOW, typename T, typename... Args>  void Info(T msg, Args... args);
		template<LogPriority P = LOW, typename T, typename... Args>  void Debug(T msg, Args... args);
		template<LogPriority P = LOW, typename T, typename... Args>  void Warn(T msg, Args... args);
		template<LogPriority P = LOW, typename T, typename... Args>  void Error(T msg, Args... args);
	};

	namespace Attempt {

		enum class Status { PASS, FAIL, WARN };

		template<LogPriority P>
		class Result {
		private:
			Status m_Status;
		public:
			Result(Status status);
		public:
			template<typename T, typename... Args> Result& pass(T msg, Args... args);
			template<typename T, typename... Args> Result& warn(T msg, Args... args);
			template<typename T, typename... Args> Result& fail(T msg, Args... args);
		public:
			bool is_pass() const;
		};

		template<LogPriority P, typename Func>
		class Builder {
		private:
			Func m_Func;
		public:
			Builder(Func f);
		public:
			template<typename T, typename... Args> Result<P> does(T msg, Args... args);
		};

		// TO( <function> ). ...
		template<LogPriority P = LOW, typename Func> Builder<P, Func> to(Func f);
	};
};

Engine::String operator"" _H(const char* str, Engine::u64 len);	// highlight
Engine::String operator"" _B(const char* str, Engine::u64 len);	// bold
Engine::String operator"" _D(const char* str, Engine::u64 len);	// dim
Engine::String operator"" _U(const char* str, Engine::u64 len);	// underline
Engine::String operator"" _I(const char* str, Engine::u64 len);	// italics

// IMPLEMENTATION (Templated functions cannot be placed in .cpp files apparently)

template<typename T, typename ... Arg> void Engine::__recurse_output(T item, Arg ...args) {
	std::cout << item << " ";
	__recurse_output(args...);
}

inline void Engine::__recurse_output() {
	std::cout << std::endl;
}

#ifdef _DEBUG
	template<Engine::LogPriority P, typename T, typename ...Args>
	void Engine::Console::Log(T msg, Args ...args) {
		__recurse_output(
			__get_banner<P>(
				ENGINE_CONSOLE_BA_LOG,
				ENGINE_CONSOLE_FG_LOG,
				ENGINE_CONSOLE_BG_LOG,
				ENGINE_CONSOLE_XX_LOG
			), ":", msg, args...
		);
	}

	template<Engine::LogPriority P, typename T, typename ...Args>
	void Engine::Console::Info(T msg, Args ...args) {
		__recurse_output(
			__get_banner<P>(
				ENGINE_CONSOLE_BA_INF,
				ENGINE_CONSOLE_FG_INF,
				ENGINE_CONSOLE_BG_INF,
				ENGINE_CONSOLE_XX_INF
			), ":", msg, args...
		);
	}

	template<Engine::LogPriority P, typename T, typename ...Args>
	void Engine::Console::Debug(T msg, Args ...args) {
		__recurse_output(
			__get_banner<P>(
				ENGINE_CONSOLE_BA_DBG,
				ENGINE_CONSOLE_FG_DBG,
				ENGINE_CONSOLE_BG_DBG,
				ENGINE_CONSOLE_XX_DBG
			), ":", msg, args...
		);
	}

	template<Engine::LogPriority P, typename T, typename ...Args>
	void Engine::Console::Warn(T msg, Args ...args) {
		__recurse_output(
			__get_banner<P>(
				ENGINE_CONSOLE_BA_WRN,
				ENGINE_CONSOLE_FG_WRN,
				ENGINE_CONSOLE_BG_WRN,
				ENGINE_CONSOLE_XX_WRN
			), ":", msg, args...
		);
	}

	template<Engine::LogPriority P, typename T, typename ...Args>
	void Engine::Console::Error(T msg, Args ...args) {
		__recurse_output(
			__get_banner<P>(
				ENGINE_CONSOLE_BA_ERR,
				ENGINE_CONSOLE_FG_ERR,
				ENGINE_CONSOLE_BG_ERR,
				ENGINE_CONSOLE_XX_ERR
			), ":", msg, args...
		);
	}
#else
	template<Engine::LogPriority P, typename T, typename ...Args>
	void Engine::Console::Log(T msg, Args ...args) {}

	template<Engine::LogPriority P, typename T, typename ...Args>
	void Engine::Console::Info(T msg, Args ...args) {}

	template<Engine::LogPriority P, typename T, typename ...Args>
	void Engine::Console::Debug(T msg, Args ...args) {}

	template<Engine::LogPriority P, typename T, typename ...Args>
	void Engine::Console::Warn(T msg, Args ...args) {}

	template<Engine::LogPriority P, typename T, typename ...Args>
	void Engine::Console::Error(T msg, Args ...args) {}
#endif

// Attempt implementation

template<Engine::LogPriority P>
Engine::Attempt::Result<P>::Result(Status status) : m_Status(status) {}

template<Engine::LogPriority P> template<typename T, typename... Args>
Engine::Attempt::Result<P>& Engine::Attempt::Result<P>::pass(T msg, Args... args) {
	if (m_Status == Status::PASS) Engine::Console::Info<P>("[ ATTEMPT ]:"_D, msg, args...);
	return *this;
}

template<Engine::LogPriority P> template<typename T, typename... Args>
Engine::Attempt::Result<P>& Engine::Attempt::Result<P>::warn(T msg, Args... args) {
	if (m_Status == Status::WARN) Engine::Console::Warn<P>("[ ATTEMPT ]:"_D, msg, args...);
	return *this;
}

template<Engine::LogPriority P> template<typename T, typename... Args>
Engine::Attempt::Result<P>& Engine::Attempt::Result<P>::fail(T msg, Args... args) {
	if (m_Status == Status::FAIL) Engine::Console::Error<P>("[ ATTEMPT ]:"_D, msg, args...);
	return *this;
}

template<Engine::LogPriority P>
bool Engine::Attempt::Result<P>::is_pass() const {
	return m_Status == Status::PASS;
}

template<Engine::LogPriority P, typename Func>
Engine::Attempt::Builder<P, Func>::Builder(Func f) : m_Func(f) {}

template<Engine::LogPriority P, typename Func> template<typename T, typename... Args>
Engine::Attempt::Result<P> Engine::Attempt::Builder<P, Func>::does(T msg, Args... args) {
	Engine::Console::Log<P>("[ ATTEMPT ] (to) :"_D, msg, args...);

	Status final_status = Status::FAIL;

	try {
		using ReturnType = std::invoke_result_t<Func>;

		if constexpr (std::is_same_v<ReturnType, Status>) {
			final_status = m_Func();
		}
		else if constexpr (std::is_same_v<ReturnType, bool>) {
			final_status = m_Func() ? Status::PASS : Status::FAIL;
		}
		else {
			m_Func();
			final_status = Status::PASS;
		}
	}
	catch (const std::exception& e) {
		Engine::Console::Error<P>("[A TTEMPT ]:"_D, e.what());
		final_status = Status::FAIL;
	}
	catch (...) {
		Engine::Console::Error<P>("[ ATTEMPT ]:"_D, "Resulted in unknown Exception");
		final_status = Status::FAIL;
	}

	return Result<P>(final_status);
}

template<Engine::LogPriority P, typename Func>
Engine::Attempt::Builder<P, Func> Engine::Attempt::to(Func f) {
	return Builder<P, Func>(f);
}