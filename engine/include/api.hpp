#pragma once

// TODO: Add support for linux, implementation. (halted for linux implementation).
#if defined(BUILD_PLATFORM_WIN)

    // build engine api for engine solution, (this may move to engine/platform.h not yet
    // decided but following part is necessary for engine to be used as shared lib.
    #ifdef BUILD_ENGINE
        #define ENGINE_API extern "C" __declspec(dllexport)
    #else
        #define ENGINE_API extern "C" __declspec(dllimport)
    #endif

#else
    #error Voxel Engine only supports WINDOWS for now
#endif

#include <limits>
#include <cstdint>
#include <string>

namespace Engine {
    // .. (signed integers)
    using i8  = int8_t;
    using i16 = int16_t;
    using i32 = int32_t;
    using i64 = int64_t;
    // .. (limits associated with values) ----------------------------------------------+
    constexpr i8  i8_MIN  = std::numeric_limits<i8 >::min();        //                  |
    constexpr i16 i16_MIN = std::numeric_limits<i16>::min();        //                  |
    constexpr i32 i32_MIN = std::numeric_limits<i32>::min();        //                  |
    constexpr i64 i64_MIN = std::numeric_limits<i64>::min();        //                  |
    // ---------------------------------------------------------------------------------+
    constexpr i8  i8_MAX  = std::numeric_limits<i8 >::max();        //                  |
    constexpr i16 i16_MAX = std::numeric_limits<i16>::max();        //                  |
    constexpr i32 i32_MAX = std::numeric_limits<i32>::max();        //                  |
    constexpr i64 i64_MAX = std::numeric_limits<i64>::max();        //                  |
    // ---------------------------------------------------------------------------------+
    

    // .. (unsigned integers)
    using u8  = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;
    // .. (limits associated with values) ----------------------------------------------+
    constexpr u8  U8_MIN  = std::numeric_limits<u8 >::min();        //                  |
    constexpr u16 U16_MIN = std::numeric_limits<u16>::min();        //                  |
    constexpr u32 U32_MIN = std::numeric_limits<u32>::min();        //                  |
    constexpr u64 U64_MIN = std::numeric_limits<u64>::min();        //                  |
    // ---------------------------------------------------------------------------------+
    constexpr u8  u8_MAX  = std::numeric_limits<u8 >::max();        //                  |
    constexpr u16 u16_MAX = std::numeric_limits<u16>::max();        //                  |
    constexpr u32 u32_MAX = std::numeric_limits<u32>::max();        //                  |
    constexpr u64 u64_MAX = std::numeric_limits<u64>::max();        //                  |
    // ---------------------------------------------------------------------------------+

    // .. (identity element)
    using id8  = i8;
    using id16 = i16;
    using id32 = i32;
    using id64 = i64;
    // .. (invalid identity to represent NONE) -----------------------------------------+
    constexpr id8  id8_INVALID  = 0xff;                             // -1 = NONE        |
    constexpr id16 id16_INVALID = 0xffff;                           // -1 = NONE        |
    constexpr id32 id32_INVALID = 0xffff'ffff;                      // -1 = NONE        |
    constexpr id64 id64_INVALID = 0xffff'ffff'ffff'ffff;            // -1 = NONE        |
    // ---------------------------------------------------------------------------------+

    // .. (id for general purpose)
    using idxx = id16;
    // .. (invalid identity to represent NONE) -----------------------------------------+
    constexpr idxx idxx_INVALID = id16_INVALID;                     // -1 = NONE        |
    // ---------------------------------------------------------------------------------+

    // .. (decimal numbers)
    using f32 = float;
    using f64 = double;

    // .. (string)
    using String = std::string;
}