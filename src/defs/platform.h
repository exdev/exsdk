// ======================================================================================
// File         : platform.h
// Author       : Wu Jie 
// Last Change  : 06/26/2010 | 08:38:11 AM | Saturday,June
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef PLATFORM_H_1277512693
#define PLATFORM_H_1277512693
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
//  Pre-Define Block
//  In this area user add new defines that will be use in entire system
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: If a macro no defined it will be EX_UNKNOWN
// ------------------------------------------------------------------

#define EX_UNKNOWN  0x00

// ------------------------------------------------------------------
// Desc: Platform define
//  use EX_PLATFORM to judge current operator system.
// ------------------------------------------------------------------

// pc
#define EX_WIN32    0x0001
#define EX_LINUX    0x0002
#define EX_MACOSX   0x0003

// mobile
#define EX_IOS      0x0010
#define EX_ANDROID  0x0020

// console
#define EX_XENON    0x0100
#define EX_PS3      0x0200

// ------------------------------------------------------------------
// Desc: Platform choose
// ------------------------------------------------------------------

// windows 32-bit 
#if defined ( WIN32 ) || defined ( _WIN32 )
    #define EX_PLATFORM EX_WIN32
// linux
#elif defined(linux) || defined(__linux) || defined(__linux__)
    #define EX_PLATFORM EX_LINUX 
// apple
#elif defined(__APPLE__)
// ios
    #if TARGET_OS_IPHONE
        #define EX_PLATFORM EX_IOS
// mac osx
    #else
        #define EX_PLATFORM EX_MACOSX
    #endif
// android
#elif defined(__ANDROID)
    #define EX_PLATFORM EX_ANDROID
// xenon
#elif defined ( __EX_XENON__ )
    #define EX_PLATFORM EX_XENON 
// ps3
#elif defined ( __EX_PS3__ )
    #define EX_PLATFORM EX_PS3
// unknown
#else
    #define EX_PLATFORM EX_UNKNOWN
#endif

// ------------------------------------------------------------------
// Desc: Debug Mode
// ------------------------------------------------------------------

#if defined ( DEBUG ) || defined ( _DEBUG ) || defined ( __EX_DEBUG__ )
    #define EX_DEBUG
#elif defined ( RELEASE ) || defined ( _RELEASE ) || defined ( __EX_RELEASE__ )
    #define EX_RELEASE
#endif

// ------------------------------------------------------------------
// Desc: Check if platform support unicode 
// ------------------------------------------------------------------

// win32
#if ( EX_PLATFORM == EX_WIN32 )
    #define EX_UNICODE_PLATFORM 1
// linux
#elif ( EX_PLATFORM == EX_LINUX )
    #define EX_UNICODE_PLATFORM 1
// mac osx
#elif ( EX_PLATFORM == EX_MACOSX )
    #define EX_UNICODE_PLATFORM 1
// ios
#elif ( EX_PLATFORM == EX_IOS )
    #define EX_UNICODE_PLATFORM 1
// android
#elif ( EX_PLATFORM == EX_ANDROID )
    #define EX_UNICODE_PLATFORM 1
// xenon
#elif ( EX_PLATFORM == EX_XENON )
    #define EX_UNICODE_PLATFORM 0
// ps3
#elif ( EX_PLATFORM == EX_PS3 )
    #define EX_UNICODE_PLATFORM 0
#endif

// ------------------------------------------------------------------
// Desc: UNICODE MODE
// ------------------------------------------------------------------

#if defined ( UNICODE ) || defined ( _UNICODE )
    #define EX_USE_UNICODE 1
#else
    #define EX_USE_UNICODE 0
#endif

// ------------------------------------------------------------------
// Desc: define EX_DLL if we have DLL/_DLL macro
// ------------------------------------------------------------------

#if defined(__EX_DLL__) || defined (_WINDLL)
    #define EX_USE_DLL 1
#endif

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

#if (EX_USE_DLL)
    #if ( EX_PLATFORM == EX_WIN32 )
        #define EX_DLL_EXPORT __declspec(dllexport)
        #define EX_DLL_IMPORT __declspec(dllimport)
    #else
        #define EX_DLL_EXPORT
        #define EX_DLL_IMPORT
    #endif
#else
    #define EX_DLL_EXPORT
    #define EX_DLL_IMPORT
#endif

// #################################################################################
#endif // END PLATFORM_H_1277512693
// #################################################################################
