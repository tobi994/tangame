//! \file Platform.hpp
//! Macros and utility functions to facilitate programming on all of Gosu's supported platforms.

#ifndef GOSU_PLATFORM_HPP
#define GOSU_PLATFORM_HPP

#ifdef __BIG_ENDIAN__
#define IDENTITY_FUN bigToNative
#define IDENTITY_FUN2 nativeToBig
#define CONV_FUN littleToNative
#define CONV_FUN2 nativeToLittle
#else
#define IDENTITY_FUN littleToNative
#define IDENTITY_FUN2 nativeToLittle
#define CONV_FUN bigToNative
#define CONV_FUN2 nativeToBig
#endif

#include <algorithm>

namespace Gosu
{
    template<typename T> T IDENTITY_FUN(T t) { return t; }
    template<typename T> T IDENTITY_FUN2(T t) { return t; }
    
    template<typename T>
    T CONV_FUN(T t)
    {
        char* begin = reinterpret_cast<char*>(&t);
        std::reverse(begin, begin + sizeof t);
        return t;
    }

    template<typename T> T CONV_FUN2(T t) { return CONV_FUN(t); }
}

#undef IDENTITY_FUN
#undef IDENTITY_FUN2
#undef CONV_FUN
#undef CONV_FUN2

#ifdef _MSC_VER
#define GOSU_NORETURN __declspec(noreturn)
#endif

#ifdef __GNUC__
#define GOSU_NORETURN __attribute__ ((noreturn))
#endif

#ifdef WIN32
# define GOSU_IS_WIN
#else
# define GOSU_IS_UNIX
# if defined(__linux) || defined(__FreeBSD__)
#  define GOSU_IS_X
# else
#  define GOSU_IS_MAC
# endif
#endif

#endif
