#ifndef COMMON_PLATFORM_H
#define COMMON_PLATFORM_H

// TODO: Add support for linux, implementation. (halted for linux implementation).
#if defined(BUILD_PLATFORM_WIN)
    
	// build common api for current context, it may be used to export by common package but for
	// importing by Engine, structures and also byuser defined projects.
	#ifdef BUILD_COMMON
        #define COMMON_API __declspec(dllexport)
    #else
        #define COMMON_API __declspec(dllimport)
    #endif
	
	// build engine api for engine solution, (this may move to engine/platform.h not yet decided
	// but following part is necessary for engine to be used as shared lib.
	#ifdef BUILD_ENGINE
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif
	
#else
    #define COMMON_API
    #define ENGINE_API
#endif

#include "pch.h"

namespace Common {

    /*
    * So `size_t` could have been used for supporting both x86 and x64, but it ends up messing up when you secifcally need
    * to use 64 bits, there are workarounds for this however, it may be considered in future for this project.
    * 
    * --------------------------------------------------------------------------------------------------+
    * we can make allocate_int( <bytes> ); to control how many bytes are needed                         |
    * this may use 2 32bit ints to store a 64 bit int if needed                                         |
    * this is jyst a workaround, just noted this down for future self                        ¯\_(")_/¯  |
    * --------------------------------------------------------------------------------------------------+
    * 
    * TODO: impliment cross-architecture support (x86 & x64), XIntXX may become redundant remeber to make changes
    *       to all file that uses such.                                                         
    */

    // Fundamental types -------------------------------------------------------------------------------+
    using Byte = char;                      //< 1-byte signed value, general-purpose small data         |
    using uByte = unsigned char;            //< 1-byte unsigned value, for raw data or byte-level access|
    //--------------------------------------------------------------------------------------------------|
    using sInt32 = int;                     //< 4-byte signed integer                                   |
    using sInt64 = long long int;           //< 8-byte signed integer                                   |
    using uInt32 = unsigned int;            //< 4-byte unsigned integer                                 |
    using uInt64 = unsigned long long int;  //< 8-byte unsigned integer                                 |
    //--------------------------------------------------------------------------------------------------|
    using Float32 = float;                  //< 4-byte floating point, used for most calculations       |
    using Float64 = double;                 //< 8-byte floating point, used for high-precision math     |
    //--------------------------------------------------------------------------------------------------+

    // Complex Vector types ----------------------------------------------------------------------------+
    using Vec2i = sInt32[2];                //< 2D vector with signed integers                          |
    using Vec2u = uInt32[2];                //< 2D vector with unsigned integers                        |
    using Vec2f = Float32[2];               //< 2D vector with floats                                   |
    //--------------------------------------------------------------------------------------------------|
    using Vec3i = sInt32[3];                //< 3D vector with signed integers                          |
    using Vec3u = uInt32[3];                //< 3D vector with unsigned integers                        |
    using Vec3f = Float32[3];               //< 3D vector with floats                                   |
    //--------------------------------------------------------------------------------------------------|
    using Vec4i = sInt32[4];                //< 4D vector with signed integers                          |
    using Vec4u = uInt32[4];                //< 4D vector with unsigned integers                        |
    using Vec4f = Float32[4];               //< 4D vector with floats                                   |
    //--------------------------------------------------------------------------------------------------+

    // Custom Definitions ------------------------------------------------------------------------------+
    using String = std::string;             //< Wrap around inbuilt definition of string                |
    //--------------------------------------------------------------------------------------------------+
};

#include "platform.inl"

#endif