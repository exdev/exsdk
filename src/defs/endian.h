// ======================================================================================
// File         : endian.h
// Author       : Wu Jie 
// Last Change  : 01/18/2011 | 12:03:00 PM | Tuesday,January
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef ENDIAN_H_1295323381
#define ENDIAN_H_1295323381
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" { 
#endif
// ######################### 

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

#define EX_LIL_ENDIAN       1234
#define EX_BIG_ENDIAN       4321

// Little-endian operating systems:
// Linux on x86, x64, Alpha and Itanium
// Mac OS X on x86, x64
// OpenVMS on VAX, Alpha and Itanium
// Solaris on x86, x64, PowerPC
// Tru64 UNIX on Alpha
// Windows on x86, x64 and Itanium
// Microsoft Xbox 1

// Big-endian operating systems:
// AIX on POWER
// AmigaOS on PowerPC and 680x0
// HP-UX on Itanium and PA-RISC
// Linux on MIPS, SPARC, PA-RISC, POWER, PowerPC, 680x0, ESA/390, and z/Architecture
// Mac OS on PowerPC and 680x0
// Mac OS X on PowerPC
// MVS and DOS/VSE on ESA/390, and z/VSE and z/OS on z/Architecture
// Solaris on SPARC
// Microsoft Xbox 360, PlayStation 3, Nintendo Wii

#ifndef EX_BYTEORDER
#ifdef __linux__
    #include <endian.h>
    #define EX_BYTEORDER  __BYTE_ORDER
#else /* __linux __ */
    #if defined(__hppa__) || \
        defined(__m68k__) || defined(mc68000) || defined(_M_M68K) || \
        (defined(__MIPS__) && defined(__MISPEB__)) || \
        defined(__ppc__) || defined(__POWERPC__) || defined(_M_PPC) || \
        defined(__sparc__)
            #define EX_BYTEORDER	EX_BIG_ENDIAN
    #else
            #define EX_BYTEORDER	EX_LIL_ENDIAN
    #endif
#endif /* __linux __ */
#endif /* !EX_BYTEORDER */

// DISABLE { 
// win32
// #if ( EX_PLATFORM == EX_WIN32 )
//     #define EX_BYTEORDER   EX_LIL_ENDIAN
// // linux
// #elif ( EX_PLATFORM == EX_LINUX )
//     #define EX_BYTEORDER   EX_LIL_ENDIAN
// // mac osx
// #elif ( EX_PLATFORM == EX_MACOSX )
//     #define EX_BYTEORDER   EX_BIG_ENDIAN
// // xenon
// #elif ( EX_PLATFORM == EX_XENON )
//     #define EX_BYTEORDER   EX_BIG_ENDIAN
// // ps3
// #elif ( EX_PLATFORM == EX_PS3 )
//     #define EX_BYTEORDER   EX_BIG_ENDIAN
// // ios
// #elif ( EX_PLATFORM == EX_IOS )
//     #define EX_BYTEORDER   EX_LIL_ENDIAN
// // android
// #elif ( EX_PLATFORM == EX_ANDROID )
//     #define EX_BYTEORDER   EX_LIL_ENDIAN
// #endif
// } DISABLE end 

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 


// #################################################################################
#endif // END ENDIAN_H_1295323381
// #################################################################################


