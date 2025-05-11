#ifndef CORE_LOGGING_H
#define CORE_LOGGING_H

#include <format>
#include <iostream>
#include "platform.h"

#define CORE_CONSOLE_DISABLED 0x66666600

#define CORE_CONSOLE_BA_LOG "LOG"
#define CORE_CONSOLE_FG_LOG 0xffffff00
#define CORE_CONSOLE_BG_LOG 0xffffff00
#define CORE_CONSOLE_XX_LOG CORE_CONSOLE_DISABLED

#define CORE_CONSOLE_BA_INF "INF"
#define CORE_CONSOLE_FG_INF 0x6666ff00
#define CORE_CONSOLE_BG_INF 0x6666ff00
#define CORE_CONSOLE_XX_INF CORE_CONSOLE_DISABLED

#define CORE_CONSOLE_BA_DBG "DBG"
#define CORE_CONSOLE_FG_DBG 0x66ff6600
#define CORE_CONSOLE_BG_DBG 0x66ff6600
#define CORE_CONSOLE_XX_DBG CORE_CONSOLE_DISABLED

#define CORE_CONSOLE_BA_WRN "WRN"
#define CORE_CONSOLE_FG_WRN 0xffff6600
#define CORE_CONSOLE_BG_WRN 0xffff6600
#define CORE_CONSOLE_XX_WRN CORE_CONSOLE_DISABLED

#define CORE_CONSOLE_BA_ERR "ERR"
#define CORE_CONSOLE_FG_ERR 0xff666600
#define CORE_CONSOLE_BG_ERR 0xff666600
#define CORE_CONSOLE_XX_ERR CORE_CONSOLE_DISABLED

namespace Core {

	// Type aliases for terminal color -----------------------------------------------------------------------------+
	using Color = uInt32;		//< Represents a color code (e.g., for foreground/background terminal colors)		|
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

	CORE_API String __fg_color_hex_to_ansi(Color val);
	CORE_API String __bg_color_hex_to_ansi(Color val);

	template<Console::LogPriority P> CORE_API String __get_banner(String of, Color fg, Color bg, Color xx);
	template<Console::LogPriority P> CORE_API String __get_highlight(String on, Color highlight, Color xx);

	template CORE_API String __get_banner<Console::LOW>(String, Color, Color, Color);
	template CORE_API String __get_banner<Console::MED>(String, Color, Color, Color);
	template CORE_API String __get_banner<Console::HIG>(String, Color, Color, Color);

	template CORE_API Core::String Core::__get_highlight<Core::Console::LOW>(String, Color, Color);
	template CORE_API Core::String Core::__get_highlight<Core::Console::MED>(String, Color, Color);
	template CORE_API Core::String Core::__get_highlight<Core::Console::HIG>(String, Color, Color);
	
	template<typename T, typename... Arg>CORE_API void __recurse_output(T item, Arg... args);
	CORE_API void __recurse_output();

	namespace Console {
		template<LogPriority P = LOW, typename T, typename... Args> CORE_API void Log(T msg, Args... args);
		template<LogPriority P = LOW, typename T, typename... Args> CORE_API void Info(T msg, Args... args);
		template<LogPriority P = LOW, typename T, typename... Args> CORE_API void Debug(T msg, Args... args);
		template<LogPriority P = LOW, typename T, typename... Args> CORE_API void Warn(T msg, Args... args);
		template<LogPriority P = LOW, typename T, typename... Args> CORE_API void Error(T msg, Args... args);
	};
};

CORE_API Core::String operator"" _H(const char* str, Core::uInt32 len);	// highlight
CORE_API Core::String operator"" _B(const char* str, Core::uInt32 len);	// bold
CORE_API Core::String operator"" _D(const char* str, Core::uInt32 len);	// dim
CORE_API Core::String operator"" _U(const char* str, Core::uInt32 len);	// underline
CORE_API Core::String operator"" _I(const char* str, Core::uInt32 len); // italics

// define templated -unknown typed classes and functions within header file to avoid liknking exceptions.
template<typename T, typename ... Arg>CORE_API void Core::__recurse_output(T item, Arg ...args){
	std::cout << item << " "; 
	__recurse_output(args...);
}

CORE_API void Core::__recurse_output(){
	std::cout << std::endl;
}

template<Core::Console::LogPriority P, typename T, typename ...Args>
void Core::Console::Log(T msg, Args ...args) {
	__recurse_output( 
		__get_banner<P>(
			CORE_CONSOLE_BA_LOG, 
			CORE_CONSOLE_FG_LOG, 
			CORE_CONSOLE_BG_LOG, 
			CORE_CONSOLE_XX_LOG
		), ":", msg, args...
	);
}

template<Core::Console::LogPriority P, typename T, typename ...Args>
void Core::Console::Info(T msg, Args ...args) {
	__recurse_output(
		__get_banner<P>(
			CORE_CONSOLE_BA_INF, 
			CORE_CONSOLE_FG_INF, 
			CORE_CONSOLE_BG_INF, 
			CORE_CONSOLE_XX_INF
		), ":", msg, args...
	);
}

template<Core::Console::LogPriority P, typename T, typename ...Args>
void Core::Console::Debug(T msg, Args ...args) {
	__recurse_output(
		__get_banner<P>(
			CORE_CONSOLE_BA_DBG,
			CORE_CONSOLE_FG_DBG,
			CORE_CONSOLE_BG_DBG,
			CORE_CONSOLE_XX_DBG
		), ":", msg, args...
	);
}

template<Core::Console::LogPriority P, typename T, typename ...Args>
void Core::Console::Warn(T msg, Args ...args) {
	__recurse_output(
		__get_banner<P>(
			CORE_CONSOLE_BA_WRN,
			CORE_CONSOLE_FG_WRN,
			CORE_CONSOLE_BG_WRN,
			CORE_CONSOLE_XX_WRN
		), ":", msg, args...
	);
}

template<Core::Console::LogPriority P, typename T, typename ...Args>
void Core::Console::Error(T msg, Args ...args) {
	__recurse_output(
		__get_banner<P>(
			CORE_CONSOLE_BA_ERR,
			CORE_CONSOLE_FG_ERR,
			CORE_CONSOLE_BG_ERR,
			CORE_CONSOLE_XX_ERR
		), ":", msg, args...
	);
}

#endif