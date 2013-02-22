// ======================================================================================
// File         : exSDK.c
// Author       : Wu Jie 
// Last Change  : 06/26/2010 | 21:03:19 PM | Saturday,June
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include "exSDK.h"

///////////////////////////////////////////////////////////////////////////////
// compile message 
///////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------
//! @mainpage exSDK manual
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
    #pragma message("exSDK predefine log")
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

const char *ex_sdk_ver () { return "1.0.0"; }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_sdk_init () {
    ex_assert ( __initialized == false );

    if ( __initialized )
        return -1;

    ex_log ( "[exSDK] Initializing..." );

    // init Allegro
    ex_log ( "[exSDK] Initializing Allegro..." );
    if ( al_init () == false ) {
        ex_log ( "[exSDK] Error: Could not init Allegro!" );
        return -1;
    }
    al_init_image_addon();
    al_init_primitives_addon();

    // init memory
    ex_log ( "[exSDK] Initializing memory..." );
    if ( ex_mem_init () != 0 ) {
        ex_log ( "[exSDK] Error: Could not init memory!" );
        return -1;
    }

    // init fsys
    ex_log ( "[exSDK] Initializing fsys..." );
    if ( ex_fsys_init () != 0 ) {
        ex_log ( "[exSDK] Error: Could not init fsys!" );
        return -1;
    }

    // init lua
    ex_log ( "[exSDK] Initializing lua..." );
    if ( ex_lua_init () != 0 ) {
        ex_log ( "[exSDK] Error: Could not init lua!" );
        return -1;
    }

    __initialized = true;
    ex_log ( "[exSDK] Initialized!" );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_sdk_deinit () {
    ex_assert ( __initialized );

    if ( __initialized == false )
        return;

    ex_log ( "[exSDK] Closing..." );

    ex_log ( "[exSDK] Closing lua..." );
    ex_lua_deinit ();

    ex_log ( "[exSDK] Closing fsys..." );
    ex_fsys_deinit ();

    ex_log ( "[exSDK] Closing memory..." );
    ex_mem_deinit ();

    __initialized = false;
    ex_log ( "[exSDK] Closed!" );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_sdk_initialized () {
    return __initialized;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_sdk_open_project ( const char *_path ) {
    ex_assert ( _path != NULL );

    // if the media_path exists, use it. if not, try to search it in the app/ directory
    if ( ex_os_exists (_path) == false ) {
        ex_log ( "[exSDK] Error: Can't load project at %s", _path );
        return -1;
    }

    ex_log ( "[exSDK] Open project: %s", _path  );

    // set write dir
    if ( ex_fsys_set_write_dir(_path) != 0 )
        return -1;

    // mount the write dir. NOTE: set write dir doesn't means you mount it.
    if ( ex_fsys_mount( _path, "__project__", true ) != 0 )
        return -1;

    // load builtin modules
    // TODO: think about cross reference problem, to solve this, a package.preload is needed
    // my solution is, first add everything to package.preload, then load each module excactly
    // search builtin/modules/ and add each folder in as module
    // NOTE: Consider use package.preload, in luaL_openlibs function, there have some example. 
    ex_lua_dofile ( ex_lua_main_state(), "builtin/modules/init.lua" );

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_sdk_close_project () {
    // TODO: set_write_dir to default.
    // TODO: unmount project dir
}

