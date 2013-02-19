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

static int __lua_dofile ( lua_State *_l ) {
    const char *path;

    ex_lua_check_nargs(_l,1);

    path = luaL_checkstring(_l,1);
    ex_lua_dofile( _l, path );

    return lua_gettop(_l) - 1;
}

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

static int __lua_fsys_writedir ( lua_State *_l ) {
    lua_pushstring( _l, ex_fsys_write_dir() );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_fsys_exists ( lua_State *_l ) {
    const char *path;

    ex_lua_check_nargs(_l,1);

    path = luaL_checkstring(_l,1);
    lua_pushboolean( _l, ex_fsys_exists(path) );

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "lua_dump_stack",     ex_lua_dump_stack },
    { "lua_total_memory",   ex_lua_totoal_memory },
    { "lua_dofile",         __lua_dofile },
    { "fsys_app_dir",       __lua_fsys_app_dir },
    { "fsys_user_dir",      __lua_fsys_user_dir },
    { "fsys_writedir",      __lua_fsys_writedir },
    { "fsys_exists",        __lua_fsys_exists },
    { NULL, NULL }
};

int __ex_lua_add_core ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );

    // ex_c.null = NULL
    lua_pushlightuserdata ( _l, NULL );
    lua_setfield( _l, -2, "null" );

    return 0;
}
