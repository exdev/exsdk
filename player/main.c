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
    int i = 0;

    // init exsdk ( including allegro ) 
    if ( ex_sdk_init() != 0 ) {
        ex_log ( "Could not init exsdk!" );
        return 1;
    }

    // TODO { 
    // parse arguments
    while ( i < _argc ) {
        ex_log( "argument[%d] = %s", i, _argv[i] );
        ++i;
    }
    // } TODO end 

    // load init 
    ex_lua_dofile ( ex_lua_main_state(), "startup.lua" );

    // parsing main.lua
    // ex_lua_run_interpretor ( ex_lua_main_state() );
    ex_lua_parse_main ( ex_lua_main_state() );

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

