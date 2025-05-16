
# Logger System Documentation (For Contributors)

This document provides in-depth technical documentation of the `Core::Console` logging system. It is intended for **contributors** who want to extend, maintain, or understand the internal workings of the logger.

---

## Overview

The logger is a templated system for structured, color-coded console output. It supports:

- Multiple **log levels** (e.g., `LOG`, `INF`, `ERR`)
- Configurable **priority levels** (`LOW`, `MED`, `HIG`)
- ANSI-styled **banners** and **highlights**
- Recursive variadic templates for flexible message formatting
- Custom styling with user-defined literals (e.g., `_B`, `_H`, `_U`)

This design avoids linking issues by defining all templated functions in the header.

---

## Logging Levels and Priorities (For Contributors)

The logging system supports two orthogonal mechanisms: **Levels** and **Priorities**. As a contributor, it's important to understand their roles to extend or modify the logger consistently.

TODO: impliment log level behaviour.

### 🔹 Levels (`Core::Console::LogLevel`)

Levels categorize the **type or purpose** of log messages:

- `OFF` – Disable logging
- `LOG` – General-purpose messages
- `INF` – Informational messages (e.g., service started)
- `DBG` – Debugging output
- `WRN` – Warnings
- `ERR` – Errors and failures

These levels are useful for filtering and consistent formatting.

### 🔹 Priorities (`Core::Console::LogPriority`)

Priorities indicate the **severity** of a message:

- `LOW` – Non-urgent (default)
- `MED` – Moderately important
- `HIG` – Critical or high-urgency

Log functions are templated by priority, allowing compile-time customization.

---

## Color and Style Configuration

Each log level has predefined macros for banner label, foreground color, background color, and optional disabled fallback.

Example for `LOG`:
```cpp
#define CORE_CONSOLE_BA_LOG "LOG"
#define CORE_CONSOLE_FG_LOG 0xffffff00
#define CORE_CONSOLE_BG_LOG 0xffffff00
#define CORE_CONSOLE_XX_LOG CORE_CONSOLE_DISABLED
```

These use 32-bit hex values (`0xRRGGBBAA`) for color and can be mapped to ANSI escape sequences via helper functions.

---

## Log Output Implementation

The following internal helpers define the structure and formatting of logs:

### 🔸 `__get_banner<P>()`

Creates the colored label for a log (e.g., `[LOG]`, `[ERR]`) based on priority and color.

### 🔸 `__get_highlight<P>()`

Returns a stylized string with highlight formatting.

### 🔸 `__recurse_output(...)`

Template function that recursively prints any number of arguments to `std::cout`.

---

## Logging API

These are the main entry points for writing log messages. All functions are templated with an optional priority:

```cpp
template<LogPriority P = LOW, typename T, typename... Args>
void Log(T msg, Args... args);
void Info(...)
void Debug(...)
void Warn(...)
void Error(...)
```

### Example Usage

```cpp
Core::Console::Log("System boot complete.");
Core::Console::Error<Core::Console::HIG>("Critical failure at", moduleName);
```

---

## Styling Helpers

To simplify inline styling, the system provides user-defined string literal operators:

| Literal | Effect     |
|---------|------------|
| `_B`    | Bold       |
| `_D`    | Dim        |
| `_U`    | Underline  |
| `_I`    | Italics    |
| `_H`    | Highlight  |

Example:

```cpp
std::cout << "Warning: "_B << "Overheating detected!" << std::endl;
```

---

## Adding New Log Levels or Styles

To introduce a new log level:

1. Add a new value in `enum LogLevel`
2. Define corresponding macros (`CORE_CONSOLE_BA_XXX`, `FG`, `BG`, `XX`)
3. Implement a new `LogXXX()` wrapper (optional)
4. Add formatting logic if needed

---

## Design Goals

- **Modular and extensible:** Easy to define new log types
- **Human-readable logs:** ANSI color and consistent formatting
- **Developer-friendly:** Recursive variadic output and style literals

---

## Final Notes

- All output uses `std::cout`; redirecting logs to a file or stream may require refactoring `__recurse_output`.
- Colors assume terminal support for ANSI codes.
- You can disable or override styles with `CORE_CONSOLE_DISABLED`.

Contributions are welcome. Please follow the format and style conventions outlined above when extending the system.

## Future for Logging Module

To support multi-threaded logging and improve traceability, the logging system is planned to evolve with the following architectural enhancements:

- 🧩 Observer-based Output Handling.
- 📦 Observable Log Queue.
- 🧵 Thread-Aware Trace.
