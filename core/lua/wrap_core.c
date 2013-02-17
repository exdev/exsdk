// ======================================================================================
// File         : wrap_core.c
// Author       : Wu Jie 
// Last Change  : 02/07/2013 | 15:00:11 PM | Thursday,February
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

///////////////////////////////////////////////////////////////////////////////
// functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_fsys_app_dir ( lua_State *_l ) {
    lua_pushstring( _l, ex_fsys_app_dir() );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_fsys_user_dir ( lua_State *_l ) {
    lua_pushstring( _l, ex_fsys_user_dir() );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_fsys_realpath ( lua_State *_l ) {
    const char *path;

    ex_lua_check_nargs(_l,1);

    path = luaL_checkstring(_l,1);
    lua_pushstring( _l, ex_fsys_realpath(path) );

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "lua_dump_stack",     ex_lua_dump_stack },
    { "lua_total_memory",   ex_lua_totoal_memory },
    { "fsys_app_dir",       __lua_fsys_app_dir },
    { "fsys_user_dir",      __lua_fsys_user_dir },
    { "fsys_realpath",      __lua_fsys_realpath },
    { NULL, NULL }
};

int __ex_lua_add_core ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );

    // ex_c.null = NULL
    lua_pushlightuserdata ( _l, NULL );
    lua_setfield( _l, -2, "null" );

    // ex_c.platform = "..."
#if ( EX_PLATFORM == EX_WIN32 )
    lua_pushstring ( _l, "windows" );
#elif ( EX_PLATFORM == EX_LINUX )
    lua_pushstring ( _l, "linux" );
#elif ( EX_PLATFORM == EX_MACOSX )
    lua_pushstring ( _l, "macosx" );
#elif ( EX_PLATFORM == EX_XENON )
    lua_pushstring ( _l, "xb360" );
#elif ( EX_PLATFORM == EX_PS3 )
    lua_pushstring ( _l, "ps3" );
#elif ( EX_PLATFORM == EX_IOS )
    lua_pushstring ( _l, "ios" );
#elif ( EX_PLATFORM == EX_ANDROID )
    lua_pushstring ( _l, "android" );
#endif
    lua_setfield( _l, -2, "platform" );

    return 0;
}
