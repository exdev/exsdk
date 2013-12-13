// ======================================================================================
// File         : exsdk.c
// Author       : Wu Jie 
// Last Change  : 12/13/2013 | 12:12:06 PM | Friday,December
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
// compile message 
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------
//! @mainpage exsdk manual
//! 
//! Index
//! - Modules
//!   - @subpage Math
//-----------------------------------------------------------

// ========================================================
// define EX_SHOW_COMPILE_MESSAGE
// ========================================================

#define EX_SHOW_COMPILE_MESSAGE 1

// ========================================================
// define compile message for MSVC
// ========================================================

#if (EX_COMPILER == EX_MSVC)
    // log title
    #pragma message(" ")
    #pragma message("==========================================")
    #pragma message("exsdk predefine log")
    #pragma message("==========================================")
    #pragma message(" ")
    #pragma message("<<<<<<")
    
    // log compiler
    #if (EX_COMPILER == EX_MSVC)
        #pragma message("compiler ms-vc: "EX_STRING_EXPAND(EX_COMPILER_VER))
    #elif (EX_COMPILER == EX_GCC)
        #pragma message("compiler gcc: "EX_STRING_EXPAND(EX_COMPILER_VER))
    #else
        #pragma message("compiler unknown: ")
    #endif

    // log configuration
    #if defined (EX_DEBUG)
        #pragma message("configuration: debug")
    #elif defined (EX_RELEASE)
        #pragma message("configuration: release")
    #else
        #pragma message("configuration: unknown (please add macro __EX_DEBUG__/__EX_RELEASE__ in compiler's preprocess macros)")
    #endif
    
    // log platform
    #if ( EX_PLATFORM == EX_WIN32 )
        #pragma message("platform: win32")
    #elif ( EX_PLATFORM == EX_LINUX )
        #pragma message("platform: linux")
    #elif ( EX_PLATFORM == EX_MACOSX )
        #pragma message("platform: mac osx")
    #elif ( EX_PLATFORM == EX_IOS )
        #pragma message("platform: ios")
    #elif ( EX_PLATFORM == EX_ANDROID )
        #pragma message("platform: android")
    #elif ( EX_PLATFORM == EX_XENON )
        #pragma message("platform: xenon")
    #elif ( EX_PLATFORM == EX_PS3 )
        #pragma message("platform: ps3")
    #else
        #pragma message("platform: unknown")
    #endif

    // unicode platform
    #if EX_UNICODE_PLATFORM
        #pragma message("unicode platform: true")
    #else
        #pragma message("unicode platform: false")
    #endif

    // use unicode
    #if EX_USE_UNICODE
        #pragma message("use unicode: true")
    #else
        #pragma message("use unicode: false")
    #endif
    
    // log endian
    #if ( EX_BYTEORDER == EX_BIG_ENDIAN )
        #pragma message("endian: big")
    #elif ( EX_BYTEORDER == EX_LIL_ENDIAN )
        #pragma message("endian: little")
    #else
        #pragma message("endian: unknown")
    #endif

    // log use dll or not
    #if (EX_USE_DLL == 1)
        #pragma message("targe type: dll")
    #else
        #pragma message("targe type: lib")
    #endif

    // log memory configuration
    #if EX_USE_MEMORY_MANAGER
        #pragma message("memory manager: enable")
    #else
        #pragma message("memory manager: disable")
    #endif

    #pragma message(">>>>>>")
    #pragma message(" ")

// ========================================================
// define compile message for GCC
// ========================================================

#elif (EX_COMPILER == EX_GCC)

    // log compiler
    #if (EX_COMPILER == EX_MSVC)
        #warning "compiler ms-vc"
    #elif (EX_COMPILER == EX_GCC)
        #warning "compiler gcc"
    #else
        #warning "compiler unknown"
    #endif

    // log configuration
    #if defined (EX_DEBUG)
        #warning "configuration: debug"
    #elif defined (EX_RELEASE)
        #warning "configuration: release"
    #else
        #warning "configuration: unknown (please add macro __EX_DEBUG__/__EX_RELEASE__ in compiler's preprocess macros)"
    #endif
    
    // log platform
    #if ( EX_PLATFORM == EX_WIN32 )
        #warning "platform: win32"
    #elif ( EX_PLATFORM == EX_LINUX )
        #warning "platform: linux"
    #elif ( EX_PLATFORM == EX_MACOSX )
        #warning "platform: mac osx"
    #elif ( EX_PLATFORM == EX_IOS )
        #warning "platform: ios"
    #elif ( EX_PLATFORM == EX_ANDROID )
        #warning "platform: android"
    #elif ( EX_PLATFORM == EX_XENON )
        #warning "platform: xenon"
    #elif ( EX_PLATFORM == EX_PS3 )
        #warning "platform: ps3"
    #else
        #warning "platform: unknown"
    #endif

    // unicode platform
    #if EX_UNICODE_PLATFORM
        #warning "unicode platform: true"
    #else
        #warning "unicode platform: false"
    #endif

    // use unicode
    #if EX_USE_UNICODE
        #warning "use unicode : true"
    #else
        #warning "use unicode : false"
    #endif
    
    // log endian
    #if ( EX_BYTEORDER == EX_BIG_ENDIAN )
        #warning "byte order: big endian"
    #elif ( EX_BYTEORDER == EX_LIL_ENDIAN )
        #warning "byte order: little endian"
    #else
        #warning "byte order: unknown"
    #endif

    // log use dll or not
    #if (EX_USE_DLL == 1)
        #warning "targe type: dll"
    #else
        #warning "targe type: lib"
    #endif

    // log memory configuration
    #if EX_USE_MEMORY_MANAGER
        #warning "memory manager: enable"
    #else
        #warning "memory manager: disable"
    #endif
#endif

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

static bool __initialized = false;

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

const char *ex_sdk_ver () { return "0.9.0b"; }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_sdk_init () {
    ex_assert ( __initialized == false );

    if ( __initialized )
        return -1;

    ex_log ( "[exsdk] Initializing..." );

    // init memory
    ex_log ( "[exsdk] Initializing memory..." );
    if ( ex_mem_init () != 0 ) {
        ex_log ( "[exsdk] Error: Could not init memory!" );
        return -1;
    }

    // init fsys
    ex_log ( "[exsdk] Initializing fsys..." );
    if ( ex_fsys_init () != 0 ) {
        ex_log ( "[exsdk] Error: Could not init fsys!" );
        return -1;
    }

    // init font
    ex_log ( "[exsdk] Initializing font..." );
    if ( ex_font_init () != 0 ) {
        ex_log ( "[exsdk] Error: Could not init font!" );
        return -1;
    }

    // init painter
    ex_log ( "[exsdk] Initializing painter..." );
    if ( ex_painter_init () != 0 ) {
        ex_log ( "[exsdk] Error: Could not init ui!" );
        return -1;
    }

    __initialized = true;
    ex_log ( "[exsdk] Initialized!" );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_sdk_deinit () {
    ex_assert ( __initialized );

    if ( __initialized == false )
        return;

    ex_log ( "[exsdk] Closing..." );

    ex_log ( "[exsdk] Closing painter..." );
    ex_painter_deinit ();

    ex_log ( "[exsdk] Closing font..." );
    ex_font_deinit ();

    ex_log ( "[exsdk] Closing fsys..." );
    ex_fsys_deinit ();

    ex_log ( "[exsdk] Closing memory..." );
    ex_mem_deinit ();

    __initialized = false;
    ex_log ( "[exsdk] Closed!" );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_sdk_initialized () {
    return __initialized;
}

