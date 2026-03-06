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

	namespace Console {
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
	};

	String __fg_color_hex_to_ansi(Color val);
	String __bg_color_hex_to_ansi(Color val);

	template<Console::LogPriority P> String __get_banner(String of, Color fg, Color bg, Color xx);
	template<Console::LogPriority P> String __get_highlight(String on, Color highlight, Color xx);

	template String __get_banner<Console::LOW>(String, Color, Color, Color);
	template String __get_banner<Console::MED>(String, Color, Color, Color);
	template String __get_banner<Console::HIG>(String, Color, Color, Color);

	template String __get_highlight<Console::LOW>(String, Color, Color);
	template String __get_highlight<Console::MED>(String, Color, Color);
	template String __get_highlight<Console::HIG>(String, Color, Color);

	template<typename T, typename... Arg> void __recurse_output(T item, Arg... args);
	inline void __recurse_output();

	namespace Console {
		template<LogPriority P = LOW, typename T, typename... Args>  void Log(T msg, Args... args);
		template<LogPriority P = LOW, typename T, typename... Args>  void Info(T msg, Args... args);
		template<LogPriority P = LOW, typename T, typename... Args>  void Debug(T msg, Args... args);
		template<LogPriority P = LOW, typename T, typename... Args>  void Warn(T msg, Args... args);
		template<LogPriority P = LOW, typename T, typename... Args>  void Error(T msg, Args... args);
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
	template<Engine::Console::LogPriority P, typename T, typename ...Args>
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

	template<Engine::Console::LogPriority P, typename T, typename ...Args>
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

	template<Engine::Console::LogPriority P, typename T, typename ...Args>
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

	template<Engine::Console::LogPriority P, typename T, typename ...Args>
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

	template<Engine::Console::LogPriority P, typename T, typename ...Args>
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
	template<Engine::Console::LogPriority P, typename T, typename ...Args>
	void Engine::Console::Log(T msg, Args ...args) {}

	template<Engine::Console::LogPriority P, typename T, typename ...Args>
	void Engine::Console::Info(T msg, Args ...args) {}

	template<Engine::Console::LogPriority P, typename T, typename ...Args>
	void Engine::Console::Debug(T msg, Args ...args) {}

	template<Engine::Console::LogPriority P, typename T, typename ...Args>
	void Engine::Console::Warn(T msg, Args ...args) {}

	template<Engine::Console::LogPriority P, typename T, typename ...Args>
	void Engine::Console::Error(T msg, Args ...args) {}
#endif
