#ifndef STF_PLATFORM_HPP_HEADER_GUARD
#define STF_PLATFORM_HPP_HEADER_GUARD

// compiler settings

#define STF_COMPILER_UNKNOWN 0x00000000

// Visual C++ defines
#define STF_COMPILER_MSVC 0x01000000

// GCC defines
#define STF_COMPILER_GCC 0x02000000

// Clang defines
#define STF_COMPILER_CLANG 0x04000000

#ifdef STF_FORCE_COMPILER_UNKNOWN
#    define STF_COMPILER STF_COMPILER_UNKNOWN
// Clang
#elif defined(__clang__)
#    define STF_COMPILER STF_COMPILER_CLANG
// Visual C++
#elif defined(_MSC_VER)
#    define STF_COMPILER STF_COMPILER_MSVC
// G++
#elif defined(__GNUC__)
#    define STF_COMPILER STF_COMPILER_GCC
#else
#    define STF_COMPILER STF_COMPILER_UNKNOWN
#endif

#ifndef STF_COMPILER
#    error                                                                                                             \
        "STF_COMPILER undefined, your compiler may not be supported by stf. Add #define STF_COMPILER 0 to ignore this message."
#endif // STF_COMPILER

#endif