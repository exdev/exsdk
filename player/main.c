// ======================================================================================
// File         : main.c
// Author       : Wu Jie 
// Last Change  : 01/05/2013 | 17:44:08 PM | Saturday,January
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

#if ( EX_PLATFORM == EX_MACOSX )
    #define main _al_mangled_main
#endif

int main (void) {
    ex_file_t *file;
    char path[MAX_PATH];

    // init 
    if ( ex_sdk_init() != 0 ) {
        ex_log ( "Could not init exsdk!" );
        return 1;
    }

    // load project
    strncpy ( path, ex_fsys_app_dir(), MAX_PATH );
    strcat ( path, "MyProject_01/" );
    ex_sdk_open_project ( path );

    // main-loop 
    // ex_lua_run_interpretor ( ex_lua_main_state() );
    ex_lua_dofile ( ex_lua_main_state(), "foobar.lua" );

    // deinits 
    ex_sdk_deinit ();

    return 0;
}

