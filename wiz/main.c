// ======================================================================================
// File         : main.c
// Author       : Wu Jie 
// Last Change  : 05/07/2013 | 14:48:30 PM | Tuesday,May
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

#include "SDL.h"
#include "SDL_main.h"

#include "wiz.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

///////////////////////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void __process_option ( const char *_arg ) {
    // TODO:
    // char key[512];
    // const char* value;

    // /* If a value is specified, split the option into a key/value pair */
    // char* ptr = strchr(arg, '=');
    // if (ptr) {
    //     int len = ptr - arg;
    //     if (len > 511) len = 511;
    //     strncpy(key, arg, len);
    //     key[len] = '\0';
    //     value = ptr + 1;
    // }
    // else {
    //     strcpy(key, arg);
    //     value = "";
    // }

    // /* Make keys lowercase to avoid case issues */
    // for ( ptr = key; *ptr; ++ptr ) { *ptr = (char)tolower(*ptr); }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void __process_arguments ( int _argc, char **_argv ) {
    int i = 1;

    while ( i < _argc ) {
		// process options start with '--'
		if ( _argv[i][0] == '-' && _argv[i][1] == '-' ) {
			__process_option (_argv[i] + 2);
		}
        ++i;
	}
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int main ( int _argc, char **_argv ) {
    lua_State *l;

    __process_arguments ( _argc, _argv );

    // show help
    if ( _argc == 1 ) {
        printf( "Type 'wiz --help' for help\n" );
        return 1;
    }

    // ======================================================== 
    // system init phase ( SDL, ex_sdk, ex_lua )
    // ======================================================== 

    // init SDL
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    // SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    // NOTE: it will also init mouse, keyboard, touch and events
    if ( SDL_VideoInit(0) < 0 ) {
        ex_log ( "[SDL] Error: Could not initialize SDL video driver: %s", SDL_GetError() );
        return 1;
    }
    SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1);
    // SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    // init exsdk ( including ex_c lua module ) 
    if ( ex_sdk_init() != 0 ) {
        ex_log ( "Could not init exsdk!" );
        return 1;
    }

    // initialize ex_c module
    ex_log ( "[wiz] Initializing lua..." );
    l = ex_lua_init ();

    // ======================================================== 
    // wiz phase ( init, loop, deinit )
    // ======================================================== 

    wiz_run ( l, _argc, _argv );

    // ======================================================== 
    // system deinit phase
    // ======================================================== 

    ex_log ( "[lua] Closing lua..." );
    ex_lua_deinit (l);

    // deinit exsdk 
    ex_sdk_deinit ();

    // deinit SDL
    SDL_VideoQuit();

    return 0;
}

