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

static const luaL_Reg lib[] = {
    { "lua_dump_stack",     ex_lua_dump_stack },
    { "lua_total_memory",   ex_lua_totoal_memory },
    { "lua_dofile",         __lua_dofile },
    { NULL, NULL }
};

int __ex_lua_add_core ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );

    // ex_c.null = NULL
    lua_pushlightuserdata ( _l, NULL );
    lua_setfield( _l, -2, "null" );

    // ex_c.invalid_handle = -1
    lua_pushinteger ( _l, (size_t)-1 );
    lua_setfield( _l, -2, "invalid_handle" );

    return 0;
}
