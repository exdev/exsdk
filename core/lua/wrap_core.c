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
    int status;

    ex_lua_check_nargs(_l,1);
    path = luaL_checkstring(_l,1);

    // NOTE: don't call ex_lua_dofile here, because ex_lua_dofile will push 
    //       an error func to trace debug stack. if lua script call ex_c.lua_dofile 
    //       with this functon, it will recursively push the error func handle and lead to error. 
    status = ex_lua_dofile_2( _l, path, 0 );
    if ( status ) {
        return status;
    }

    //
    return lua_gettop(_l) - 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_init_modules ( lua_State *_l ) {
    const char *path;
    int status;

    ex_lua_check_nargs(_l,1);
    path = luaL_checkstring(_l,1);
    status = ex_lua_init_modules (_l, path);
    if ( status ) {
        return status;
    }

    //
    return lua_gettop(_l) - 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_load_module ( lua_State *_l ) {
    return -1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "dump_stack",     ex_lua_dump_stack },
    { "total_memory",   ex_lua_totoal_memory },
    { "dofile",         __lua_dofile },
    { "init_modules",   __lua_init_modules },
    { "load_module",    __lua_load_module },
    { NULL, NULL }
};

int __ex_lua_add_core ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );

    // ex_c.cwd = ""
    lua_pushstring ( _l, "" );
    lua_setfield( _l, -2, "cwd" );

    // ex_c.null = NULL
    lua_pushlightuserdata ( _l, NULL );
    lua_setfield( _l, -2, "null" );

    // ex_c.invalid_handle = -1
    lua_pushinteger ( _l, (size_t)-1 );
    lua_setfield( _l, -2, "invalid_handle" );

    return 0;
}
