#include "logging.hpp"

Engine::String Engine::__fg_color_hex_to_ansi(Color val) {
	u32 r = (val >> 24) & 0xff;
	u32 g = (val >> 16) & 0xff;
	u32 b = (val >> 8) & 0xff;
	return std::format("\x1b[38;2;{};{};{}m", r, g, b);
}

Engine::String Engine::__bg_color_hex_to_ansi(Color val) {
	u32 r = (val >> 24) & 0xff;
	u32 g = (val >> 16) & 0xff;
	u32 b = (val >> 8) & 0xff;
	return std::format("\x1b[48;2;{};{};{}m", r, g, b);
}

template<Engine::Console::LogPriority P>
Engine::String Engine::__get_banner(String of, Color fg, Color bg, Color xx) {
	switch (P)
	{
	case Engine::Console::LOW:
		return std::format("{}[  {}  ]{}", __fg_color_hex_to_ansi(xx), of, "\x1b[0m");
	case Engine::Console::MED:
		return std::format("{}[  {}  ]{}", __fg_color_hex_to_ansi(fg), of, "\x1b[0m");
	case Engine::Console::HIG:
		return std::format("{}{}[  {}  ]{}", __fg_color_hex_to_ansi(0), __bg_color_hex_to_ansi(bg), of, "\x1b[0m");
	default:
		return std::format("{}[  {}  ]{}", "", of, "");
	}
}

template<Engine::Console::LogPriority P>
Engine::String Engine::__get_highlight(String on, Color highlight, Color xx) {
	switch (P)
	{
	case Engine::Console::LOW:
		return std::format("{}{}{}", __fg_color_hex_to_ansi(xx), on, "\x1b[0m");
	case Engine::Console::MED:
		return std::format("{}{}{}", __fg_color_hex_to_ansi(xx), on, "\x1b[0m");
	case Engine::Console::HIG:
		return std::format("{}{}{}", __fg_color_hex_to_ansi(highlight), on, "\x1b[0m");
	default:
		return std::format("{}{}{}", "", on, "");
	}
}

template Engine::String Engine::__get_banner<Engine::Console::LOW>(String, Color, Color, Color);
template Engine::String Engine::__get_banner<Engine::Console::MED>(String, Color, Color, Color);
template Engine::String Engine::__get_banner<Engine::Console::HIG>(String, Color, Color, Color);

template Engine::String Engine::__get_highlight<Engine::Console::LOW>(String, Color, Color);
template Engine::String Engine::__get_highlight<Engine::Console::MED>(String, Color, Color);
template Engine::String Engine::__get_highlight<Engine::Console::HIG>(String, Color, Color);

Engine::String operator""_H(const char* str, Engine::u64 len) {
	return std::format("<%@H>{}</%@H>", str);
}

Engine::String operator""_B(const char* str, Engine::u64 len) {
	return std::format("\x1b[1m{}\x1b[22m", str);
}

Engine::String operator""_D(const char* str, Engine::u64 len) {
	return std::format("\x1b[2m{}\x1b[22m", str);
}

Engine::String operator""_I(const char* str, Engine::u64 len) {
	return std::format("\x1b[3m{}\x1b[23m", str);
}

Engine::String operator""_U(const char* str, Engine::u64 len) {
	return std::format("\x1b[4m{}\x1b[24m", str);
}