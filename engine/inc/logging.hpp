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
