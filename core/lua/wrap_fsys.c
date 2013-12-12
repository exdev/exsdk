// ======================================================================================
// File         : wrap_fsys.c
// Author       : Wu Jie 
// Last Change  : 02/20/2013 | 10:25:36 AM | Wednesday,February
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
// fsys basic
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_fsys_app_dir ( lua_State *_l ) {
    char path[MAX_PATH]; 

    strncpy( path, ex_fsys_app_dir(), MAX_PATH );
    ex_unix_path(path);
    lua_pushstring( _l, path );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_fsys_user_dir ( lua_State *_l ) {
    char path[MAX_PATH]; 

    strncpy( path, ex_fsys_user_dir(), MAX_PATH );
    ex_unix_path(path);
    lua_pushstring( _l, path );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_fsys_writedir ( lua_State *_l ) {
    char path[MAX_PATH]; 

    strncpy( path, ex_fsys_write_dir(), MAX_PATH );
    ex_unix_path(path);
    lua_pushstring( _l, path );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_fsys_realdir ( lua_State *_l ) {
    char path[MAX_PATH]; 

    ex_lua_check_nargs(_l,1);

    strncpy( path, ex_fsys_realdir(luaL_checkstring(_l,1)), MAX_PATH );
    ex_unix_path(path);
    lua_pushstring( _l, path );
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

static int __lua_fsys_files_in ( lua_State *_l ) {
    const char *path;
    char **file_list, **i;
    int count = 1;

    ex_lua_check_nargs(_l,1);

    path = luaL_checkstring(_l,1);

    // get file list
    lua_newtable(_l);
    file_list = ex_fsys_files_in(path);
    for ( i = file_list; *i != NULL; ++i ) {
        lua_pushnumber( _l, count );
        lua_pushstring( _l, *i );
        lua_settable(_l,-3);
        ++count;
    }
    ex_fsys_free_list(file_list);

    return 1;
}

///////////////////////////////////////////////////////////////////////////////
// fsys lua script
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_fsys_dofile ( lua_State *_l ) {
    const char *path;
    int status;

    ex_lua_check_nargs(_l,1);
    path = luaL_checkstring(_l,1);

    // NOTE: don't call ex_lua_dofile here, because ex_lua_dofile will push 
    //       an error func to trace debug stack. if lua script call ex_c.lua_dofile 
    //       with this functon, it will recursively push the error func handle and lead to error. 
    status = ex_lua_fsys_dofile_2( _l, path, 0 );
    if ( status ) {
        return status;
    }

    //
    return lua_gettop(_l) - 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_fsys_init_modules ( lua_State *_l ) {
    const char *path;
    int status;

    ex_lua_check_nargs(_l,1);
    path = luaL_checkstring(_l,1);
    status = ex_lua_fsys_init_modules (_l, path);
    if ( status ) {
        return status;
    }

    //
    return lua_gettop(_l) - 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_fsys_load_module ( lua_State *_l ) {
    return -1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    // fsys basic
    { "fsys_app_dir",       __lua_fsys_app_dir },
    { "fsys_user_dir",      __lua_fsys_user_dir },
    { "fsys_writedir",      __lua_fsys_writedir },
    { "fsys_realdir",       __lua_fsys_realdir },
    { "fsys_exists",        __lua_fsys_exists },
    { "fsys_files_in",      __lua_fsys_files_in },

    // fsys lua file process
    { "fsys_dofile",         __lua_fsys_dofile },
    { "fsys_init_modules",   __lua_fsys_init_modules },
    { "fsys_load_module",    __lua_fsys_load_module },

    { NULL, NULL }
};

int __ex_lua_add_fsys ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );

    return 0;
}
