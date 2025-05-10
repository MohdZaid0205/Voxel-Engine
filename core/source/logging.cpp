#include "logging.h"

CORE_API Core::String Core::__fg_color_hex_to_ansi(Color val){
    uInt32 r = (val >> 24) & 0xff;
    uInt32 g = (val >> 16) & 0xff;
    uInt32 b = (val >> 8 ) & 0xff;
    return std::format("\x1b[38;2;{};{};{}m", r, g, b);
}

CORE_API Core::String Core::__bg_color_hex_to_ansi(Color val){
    uInt32 r = (val >> 24) & 0xff;
    uInt32 g = (val >> 16) & 0xff;
    uInt32 b = (val >> 8 ) & 0xff;
    return std::format("\x1b[48;2;{};{};{}m", r, g, b);
}

template<Core::Console::LoggingPriority P>
CORE_API Core::String Core::__get_banner(String of, Color fg, Color bg, Color xx) {
	switch (P)
	{
	case Core::Console::LOW:
		return std::format("{}[  {}  ]{}", __fg_color_hex_to_ansi(xx), of, "\x1b[0m");
	case Core::Console::MED:
		return std::format("{}[  {}  ]{}", __fg_color_hex_to_ansi(fg), of, "\x1b[0m");
	case Core::Console::HIG:
		return std::format("{}{}[  {}  ]{}", __fg_color_hex_to_ansi(0), __bg_color_hex_to_ansi(bg), of, "\x1b[0m");
	default:
		return std::format("{}[  {}  ]{}", "", of, "");
	}
}

template<Core::Console::LoggingPriority P>
CORE_API Core::String Core::__get_highlight(String on, Color highlight, Color xx){
	switch (P)
	{
	case Core::Console::LOW:
		return std::format("{}{}{}", __fg_color_hex_to_ansi(xx), on, "\x1b[0m");
	case Core::Console::MED:
		return std::format("{}{}{}", __fg_color_hex_to_ansi(xx), on, "\x1b[0m");
	case Core::Console::HIG:
		return std::format("{}{}{}", __fg_color_hex_to_ansi(highlight), on, "\x1b[0m");
	default:
		return std::format("{}{}{}", "", on, "");
	}
}

template Core::String Core::__get_banner<Core::Console::LOW>(String, Color, Color, Color);
template Core::String Core::__get_banner<Core::Console::MED>(String, Color, Color, Color);
template Core::String Core::__get_banner<Core::Console::HIG>(String, Color, Color, Color);

template Core::String Core::__get_highlight<Core::Console::LOW>(String, Color, Color);
template Core::String Core::__get_highlight<Core::Console::MED>(String, Color, Color);
template Core::String Core::__get_highlight<Core::Console::HIG>(String, Color, Color);

CORE_API Core::String operator""_H(const char* str, Core::uInt32 len){
	return std::format("<%@H>{}</%@H>", str);
}

CORE_API Core::String operator""_B(const char* str, Core::uInt32 len) {
	return std::format("\x1b[1m{}\x1b[22m", str);
}

CORE_API Core::String operator""_D(const char* str, Core::uInt32 len){
	return std::format("\x1b[2m{}\x1b[22m", str);
}

CORE_API Core::String operator""_I(const char* str, Core::uInt32 len){
	return std::format("\x1b[3m{}\x1b[23m", str);
}

CORE_API Core::String operator""_U(const char* str, Core::uInt32 len){
	return std::format("\x1b[4m{}\x1b[24m", str);
}