#include "logging.h"

COMMON_API Common::String Common::__fg_color_hex_to_ansi(Color val){
    uInt32 r = (val >> 24) & 0xff;
    uInt32 g = (val >> 16) & 0xff;
    uInt32 b = (val >> 8 ) & 0xff;
    return std::format("\x1b[38;2;{};{};{}m", r, g, b);
}

COMMON_API Common::String Common::__bg_color_hex_to_ansi(Color val){
    uInt32 r = (val >> 24) & 0xff;
    uInt32 g = (val >> 16) & 0xff;
    uInt32 b = (val >> 8 ) & 0xff;
    return std::format("\x1b[48;2;{};{};{}m", r, g, b);
}

template<Common::Console::LogPriority P>
COMMON_API Common::String Common::__get_banner(String of, Color fg, Color bg, Color xx) {
	switch (P)
	{
	case Common::Console::LOW:
		return std::format("{}[  {}  ]{}", __fg_color_hex_to_ansi(xx), of, "\x1b[0m");
	case Common::Console::MED:
		return std::format("{}[  {}  ]{}", __fg_color_hex_to_ansi(fg), of, "\x1b[0m");
	case Common::Console::HIG:
		return std::format("{}{}[  {}  ]{}", __fg_color_hex_to_ansi(0), __bg_color_hex_to_ansi(bg), of, "\x1b[0m");
	default:
		return std::format("{}[  {}  ]{}", "", of, "");
	}
}

template<Common::Console::LogPriority P>
COMMON_API Common::String Common::__get_highlight(String on, Color highlight, Color xx){
	switch (P)
	{
	case Common::Console::LOW:
		return std::format("{}{}{}", __fg_color_hex_to_ansi(xx), on, "\x1b[0m");
	case Common::Console::MED:
		return std::format("{}{}{}", __fg_color_hex_to_ansi(xx), on, "\x1b[0m");
	case Common::Console::HIG:
		return std::format("{}{}{}", __fg_color_hex_to_ansi(highlight), on, "\x1b[0m");
	default:
		return std::format("{}{}{}", "", on, "");
	}
}

template Common::String Common::__get_banner<Common::Console::LOW>(String, Color, Color, Color);
template Common::String Common::__get_banner<Common::Console::MED>(String, Color, Color, Color);
template Common::String Common::__get_banner<Common::Console::HIG>(String, Color, Color, Color);

template Common::String Common::__get_highlight<Common::Console::LOW>(String, Color, Color);
template Common::String Common::__get_highlight<Common::Console::MED>(String, Color, Color);
template Common::String Common::__get_highlight<Common::Console::HIG>(String, Color, Color);

COMMON_API Common::String operator""_H(const char* str, Common::uInt64 len){
	return std::format("<%@H>{}</%@H>", str);
}

COMMON_API Common::String operator""_B(const char* str, Common::uInt64 len) {
	return std::format("\x1b[1m{}\x1b[22m", str);
}

COMMON_API Common::String operator""_D(const char* str, Common::uInt64 len){
	return std::format("\x1b[2m{}\x1b[22m", str);
}

COMMON_API Common::String operator""_I(const char* str, Common::uInt64 len){
	return std::format("\x1b[3m{}\x1b[23m", str);
}

COMMON_API Common::String operator""_U(const char* str, Common::uInt64 len){
	return std::format("\x1b[4m{}\x1b[24m", str);
}