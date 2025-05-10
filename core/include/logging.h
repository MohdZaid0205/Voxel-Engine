#ifndef CORE_LOGGING_H
#define CORE_LOGGING_H

#include <format>
#include <iostream>
#include "platform.h"

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
			ERR = 0b01000,
			FTL = 0b10000,
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

};

CORE_API Core::String operator"" _H(const char* str, Core::uInt32 len);
CORE_API Core::String operator"" _B(const char* str, Core::uInt32 len);
CORE_API Core::String operator"" _D(const char* str, Core::uInt32 len);
CORE_API Core::String operator"" _U(const char* str, Core::uInt32 len);
CORE_API Core::String operator"" _I(const char* str, Core::uInt32 len);

// define templated -unknown typed classes and functions within header file to avoid liknking exceptions.
template<typename T, typename ... Arg>CORE_API void Core::__recurse_output(T item, Arg ...args){
	std::cout << item << " "; 
	__recurse_output(args...);
}

CORE_API void Core::__recurse_output(){
	std::cout << std::endl;
}

#endif