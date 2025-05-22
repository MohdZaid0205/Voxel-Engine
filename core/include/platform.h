#ifndef CORE_PLATFORM_H
#define CORE_PLATFORM_H

#if defined(BUILD_PLATFORM_WIN)
    #ifdef BUILD_CORE
        #define CORE_API __declspec(dllexport)
    #else
        #define CORE_API __declspec(dllimport)
    #endif
#else
    #define CORE_API
#endif

#include "pch.h"

namespace Core {

    // Fundamental types -------------------------------------------------------------------------------+
    using Byte = char;                      //< 1-byte signed value, general-purpose small data         |
    using uByte = unsigned char;            //< 1-byte unsigned value, for raw data or byte-level access|
    //--------------------------------------------------------------------------------------------------|
    using Int32 = int;                      //< 4-byte signed integer                                   |
    using Int64 = long long int;            //< 8-byte signed integer                                   |
    using uInt32 = unsigned int;            //< 4-byte unsigned integer                                 |
    using uInt64 = unsigned long long int;  //< 8-byte unsigned integer                                 |
    //--------------------------------------------------------------------------------------------------|
    using Float32 = float;                  //< 4-byte floating point, used for most calculations       |
    using Float64 = double;                 //< 8-byte floating point, used for high-precision math     |
    //--------------------------------------------------------------------------------------------------+

    // Complex Vector types ----------------------------------------------------------------------------+
    using Vec2i = Int32[2];                 //< 2D vector with signed integers                          |
    using Vec2u = uInt32[2];                //< 2D vector with unsigned integers                        |
    using Vec2f = Float32[2];               //< 2D vector with floats                                   |
    //--------------------------------------------------------------------------------------------------|
    using Vec3i = Int32[3];                 //< 3D vector with signed integers                          |
    using Vec3u = uInt32[3];                //< 3D vector with unsigned integers                        |
    using Vec3f = Float32[3];               //< 3D vector with floats                                   |
    //--------------------------------------------------------------------------------------------------|
    using Vec4i = Int32[4];                 //< 4D vector with signed integers                          |
    using Vec4u = uInt32[4];                //< 4D vector with unsigned integers                        |
    using Vec4f = Float32[4];               //< 4D vector with floats                                   |
    //--------------------------------------------------------------------------------------------------+

    // Custom Definitions ------------------------------------------------------------------------------+
    using String = std::string;             //< Wrap around inbuilt definition of string                |
    //--------------------------------------------------------------------------------------------------+
};

#endif