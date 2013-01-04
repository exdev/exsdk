// ======================================================================================
// File         : types.h
// Author       : Wu Jie 
// Last Change  : 06/26/2010 | 08:40:28 AM | Saturday,June
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef TYPES_H_1277512829
#define TYPES_H_1277512829
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" {
#endif
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// general
///////////////////////////////////////////////////////////////////////////////

#ifndef __cplusplus
    // NOTE: C doesn't have bool keyword
    // NOTE: do not use define, that will replace bool to int in some macro ( such as EX_MEMBER_SERIALIZE )

    #ifdef bool
    #undef bool
    #endif

    typedef int bool;
    #define true 1
    #define false 0

    // NOTE: C doesn't have inline in some compiler
    #define inline __inline
#endif

///////////////////////////////////////////////////////////////////////////////
//  MSVC 
///////////////////////////////////////////////////////////////////////////////

#if ( EX_COMPILER == EX_MSVC )

    // ------------------------------------------------------------------
    // Desc: signed base types
    // ------------------------------------------------------------------

    // typedef signed int       int;
    typedef signed char         int8;
    typedef signed short        int16;
    typedef signed int          int32;
    typedef signed __int64      int64;

    // ------------------------------------------------------------------
    // Desc: unsigned base types
    // ------------------------------------------------------------------

    typedef unsigned int        uint;
    typedef unsigned char       uint8;
    typedef unsigned short      uint16;
    typedef unsigned int        uint32;
    typedef unsigned __int64    uint64;

    // ------------------------------------------------------------------ 
    // Desc: real_t 
    // ------------------------------------------------------------------ 

    #if EX_REAL_PRECISION  == EX_SINGLE
        typedef float real_t;
    #else
        typedef double real_t;
    #endif

    // ------------------------------------------------------------------
    // Desc: NULL
    // ------------------------------------------------------------------

    #ifdef NULL
        #undef NULL
    #endif
    #define NULL 0

    // ------------------------------------------------------------------
    // Desc: max,min size
    // ------------------------------------------------------------------

    #pragma warning( push )
    #pragma warning( disable : 4309 ) 

    #define EX_INT8_MIN    (0x80) // warning C4309: 'initializing' : truncation of constant value
    #define EX_INT8_MAX    (0x7F)
    #define EX_UINT8_MIN   (0x00)
    #define EX_UINT8_MAX   (0xFF)
    #define EX_INT16_MIN   (0x8000) // warning C4309: 'initializing' : truncation of constant value 
    #define EX_INT16_MAX   (0x7FFF)
    #define EX_UINT16_MIN  (0x0000)
    #define EX_UINT16_MAX  (0xFFFF)
    #define EX_INT32_MIN   (0x80000000)
    #define EX_INT32_MAX   (0x7FFFFFFF)
    #define EX_UINT32_MIN  (0x00000000)
    #define EX_UINT32_MAX  (0xFFFFFFFF)
    #define EX_INT64_MIN   (0x8000000000000000)
    #define EX_INT64_MAX   (0x7FFFFFFFFFFFFFFF)
    #define EX_UINT64_MIN  (0x0000000000000000)
    #define EX_UINT64_MAX  (0xFFFFFFFFFFFFFFFF)
    #define EX_FLOAT_MIN   (1.175494351E-38F)
    #define EX_FLOAT_MAX   (3.402823466E+38F)
    #define EX_DOUBLE_MIN  (2.2250738585072014E-308)
    #define EX_DOUBLE_MAX  (1.7976931348623158E+308)

    #pragma warning( pop )

#elif ( EX_COMPILER == EX_GCC )

///////////////////////////////////////////////////////////////////////////////
// Desc: GCC 
///////////////////////////////////////////////////////////////////////////////

    // ------------------------------------------------------------------
    // Desc: signed base types
    // ------------------------------------------------------------------

    // typedef signed int           int;
    typedef signed char             int8;
    typedef signed short            int16;
    typedef signed int              int32;
    typedef signed long long int    int64;

    // ------------------------------------------------------------------
    // Desc: unsigned base types
    // ------------------------------------------------------------------

    typedef unsigned int            uint;
    typedef unsigned char           uint8;
    typedef unsigned short          uint16;
    typedef unsigned int            uint32;
    typedef unsigned long long int  uint64;

    // ------------------------------------------------------------------ 
    // Desc: real 
    // ------------------------------------------------------------------ 

    #if EX_REAL_PRECISION  == EX_SINGLE
        typedef float real_t;
    #else
        typedef double real_t;
    #endif

    // ------------------------------------------------------------------
    // Desc: NULL
    // ------------------------------------------------------------------

    #ifdef NULL
        #undef NULL
    #endif
    #define NULL 0

    // ------------------------------------------------------------------
    // Desc: max,min size
    // ------------------------------------------------------------------

    // undefine the gcc __INT64_C & __UINT64_C
    #undef __INT64_C
    #undef __UINT64_C

    // undefine the gcc MIN/MAX macros
    #undef INT8_MIN
    #undef INT16_MIN
    #undef INT32_MIN
    #undef INT64_MIN
    #undef INT8_MAX
    #undef INT16_MAX
    #undef INT32_MAX
    #undef INT64_MAX
    #undef UINT8_MAX
    #undef UINT16_MAX
    #undef UINT32_MAX
    #undef UINT64_MAX

    #if __WORDSIZE == 64
        #define __INT64_C(c)	c ## L
        #define __UINT64_C(c)	c ## UL
    #else
        #define __INT64_C(c)	c ## LL
        #define __UINT64_C(c)	c ## ULL
    #endif
    
    /* Limits of integral types.  */
    
    /* Minimum of signed integral types.  */
    #define INT8_MIN		(-128)
    #define INT16_MIN		(-32767-1)
    #define INT32_MIN		(-2147483647-1)
    #define INT64_MIN		(-__INT64_C(9223372036854775807)-1)
    /* Maximum of signed integral types.  */
    #define INT8_MAX		(127)
    #define INT16_MAX		(32767)
    #define INT32_MAX		(2147483647)
    #define INT64_MAX		(__INT64_C(9223372036854775807))
    
    /* Maximum of unsigned integral types.  */
    #define UINT8_MAX		(255)
    #define UINT16_MAX		(65535)
    #define UINT32_MAX		(4294967295U)
    #define UINT64_MAX		(__UINT64_C(18446744073709551615))

    // define the EX MIN/MAX const value
    #define EX_INT8_MIN    INT8_MIN
    #define EX_INT8_MAX    INT8_MAX
    #define EX_UINT8_MIN   (0x00)
    #define EX_UINT8_MAX   UINT8_MAX
    #define EX_INT16_MIN   INT16_MIN 
    #define EX_INT16_MAX   INT16_MAX
    #define EX_UINT16_MIN  (0x0000)
    #define EX_UINT16_MAX  UINT16_MAX
    #define EX_INT32_MIN   INT32_MIN
    #define EX_INT32_MAX   INT32_MAX
    #define EX_UINT32_MIN  (0x00000000)
    #define EX_UINT32_MAX  UINT32_MAX
    #define EX_INT64_MIN   INT64_MIN
    #define EX_INT64_MAX   INT64_MAX
    #define EX_UINT64_MIN  (0x0000000000000000)
    #define EX_UINT64_MAX  UINT64_MAX
    #define EX_FLOAT_MIN   (1.175494351E-38F)
    #define EX_FLOAT_MAX   (3.402823466E+38F)
    #define EX_DOUBLE_MIN  (2.2250738585072014E-308)
    #define EX_DOUBLE_MAX  (1.7976931348623158E+308)

#endif // END EX_COMPILER

///////////////////////////////////////////////////////////////////////////////
// platform dependency types 
///////////////////////////////////////////////////////////////////////////////

// TODO { 
// #if ( EX_PLATFORM == EX_WIN32 ) 
//     typedef __m128 vec_f32_t;
//     // typedef uint32 uintptr_t;
// #elif ( EX_PLATFORM == EX_LINUX )
//     typedef __m128 vec_f32_t;
//     typedef uint32 uintptr_t;
// #elif ( EX_PLATFORM == EX_XENON )
//     typedef __vector4 vec_f32_t; 
//     typedef uint32 uintptr_t;
// #elif ( EX_PLATFORM == EX_PS3 )
//     typedef vec_float4 vec_f32_t;
//     // typedef uintptr_t addr_t;
// #endif
// } TODO end 

///////////////////////////////////////////////////////////////////////////////
// exsdk types
///////////////////////////////////////////////////////////////////////////////

typedef size_t strid_t;
typedef unsigned long thread_id_t;

// ######################### 
#ifdef __cplusplus
} // end extern "C"
#endif
// ######################### 

// #################################################################################
#endif // END TYPES_H_1277512829
// #################################################################################


