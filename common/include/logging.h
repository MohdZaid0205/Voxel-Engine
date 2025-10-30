#ifndef COMMON_LOGGING_H
#define COMMON_LOGGING_H

#include "platform.h"
#include "pch.h"

#define COMMON_CONSOLE_DISABLED 0x66666600

#define COMMON_CONSOLE_BA_LOG "LOG"
#define COMMON_CONSOLE_FG_LOG 0xffffff00
#define COMMON_CONSOLE_BG_LOG 0xffffff00
#define COMMON_CONSOLE_XX_LOG COMMON_CONSOLE_DISABLED

#define COMMON_CONSOLE_BA_INF "INF"
#define COMMON_CONSOLE_FG_INF 0x6666ff00
#define COMMON_CONSOLE_BG_INF 0x6666ff00
#define COMMON_CONSOLE_XX_INF COMMON_CONSOLE_DISABLED

#define COMMON_CONSOLE_BA_DBG "DBG"
#define COMMON_CONSOLE_FG_DBG 0x66ff6600
#define COMMON_CONSOLE_BG_DBG 0x66ff6600
#define COMMON_CONSOLE_XX_DBG COMMON_CONSOLE_DISABLED

#define COMMON_CONSOLE_BA_WRN "WRN"
#define COMMON_CONSOLE_FG_WRN 0xffff6600
#define COMMON_CONSOLE_BG_WRN 0xffff6600
#define COMMON_CONSOLE_XX_WRN COMMON_CONSOLE_DISABLED

#define COMMON_CONSOLE_BA_ERR "ERR"
#define COMMON_CONSOLE_FG_ERR 0xff666600
#define COMMON_CONSOLE_BG_ERR 0xff666600
#define COMMON_CONSOLE_XX_ERR COMMON_CONSOLE_DISABLED

namespace Common {

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

	COMMON_API String __fg_color_hex_to_ansi(Color val);
	COMMON_API String __bg_color_hex_to_ansi(Color val);

	template<Console::LogPriority P> COMMON_API String __get_banner(String of, Color fg, Color bg, Color xx);
	template<Console::LogPriority P> COMMON_API String __get_highlight(String on, Color highlight, Color xx);

	template COMMON_API String __get_banner<Console::LOW>(String, Color, Color, Color);
	template COMMON_API String __get_banner<Console::MED>(String, Color, Color, Color);
	template COMMON_API String __get_banner<Console::HIG>(String, Color, Color, Color);

	template COMMON_API Common::String Common::__get_highlight<Common::Console::LOW>(String, Color, Color);
	template COMMON_API Common::String Common::__get_highlight<Common::Console::MED>(String, Color, Color);
	template COMMON_API Common::String Common::__get_highlight<Common::Console::HIG>(String, Color, Color);
	
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

COMMON_API Common::String operator"" _H(const char* str, Common::uInt64 len);	// highlight
COMMON_API Common::String operator"" _B(const char* str, Common::uInt64 len);	// bold
COMMON_API Common::String operator"" _D(const char* str, Common::uInt64 len);	// dim
COMMON_API Common::String operator"" _U(const char* str, Common::uInt64 len);	// underline
COMMON_API Common::String operator"" _I(const char* str, Common::uInt64 len);	// italics

// templated implementations must be included in inline file.
#include "logging.inl"

#endif