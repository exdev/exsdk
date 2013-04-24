// ======================================================================================
// File         : main.c
// Author       : Wu Jie 
// Last Change  : 01/05/2013 | 17:44:08 PM | Saturday,January
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

#include "allegro5/allegro.h"
#include "exsdk.h"

#if ( EX_PLATFORM == EX_MACOSX )
    #define main _al_mangled_main
#endif

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
extern void main_loop ();
// ------------------------------------------------------------------ 

int main ( int _argc, char **_argv ) {

    // ======================================================== 
    // init 
    // ======================================================== 

    // init exsdk ( including allegro ) 
    if ( ex_sdk_init() != 0 ) {
        ex_log ( "Could not init exsdk!" );
        return 1;
    }

    // load builtin modules
    ex_log ( "[exSDK] Loading builtin modules" );
    ex_lua_dofile ( ex_lua_main_state(), "builtin/modules/init.lua" );

    // push arguments to app.arguments in lua
    ex_lua_app_init ( ex_lua_main_state(), _argc, _argv );

    // execute main.lua if exists  
    if ( ex_fsys_exists ("main.lua") )
        ex_lua_dofile ( ex_lua_main_state(), "main.lua" );

    // ======================================================== 
    // main-loop 
    // ======================================================== 

    main_loop ();

    // ======================================================== 
    // de-init 
    // ======================================================== 

    // deinits 
    ex_sdk_deinit ();

    return 0;
}

