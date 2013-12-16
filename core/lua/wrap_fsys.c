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

static int __lua_fsys_os_dir ( lua_State *_l ) {
    char path[MAX_PATH]; 

    ex_lua_check_nargs(_l,1);

    strncpy( path, ex_fsys_os_dir(luaL_checkstring(_l,1)), MAX_PATH );
    ex_unix_path(path);
    lua_pushstring( _l, path );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_fsys_mount ( lua_State *_l ) {
    const char *path;
    const char *mountPoint;

    ex_lua_check_nargs(_l,2);
    path = luaL_checkstring(_l,1);
    mountPoint = luaL_checkstring(_l,2);

    ex_str_simplify_path (path);

    // always use append here
    if ( ex_fsys_mount ( path, mountPoint, true ) != 0 ) {
        return luaL_error ( _l, "[fsys] Failed to mount %s to %s", path, mountPoint );
    }
    ex_log( "[fsys] Mount %s to %s", path, mountPoint );

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_fsys_unmount ( lua_State *_l ) {
    ex_lua_check_nargs(_l,1);
    ex_fsys_unmount (luaL_checkstring(_l,1));
    
    return 0;
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

static const luaL_Reg lib[] = {
    // fsys basic
    { "fsys_writedir",      __lua_fsys_writedir },
    { "fsys_os_dir",        __lua_fsys_os_dir },

    // mount
    { "fsys_mount",         __lua_fsys_mount },
    { "fsys_unmount",       __lua_fsys_unmount },

    // file process
    { "fsys_exists",        __lua_fsys_exists },
    { "fsys_files_in",      __lua_fsys_files_in },

    { NULL, NULL }
};

int __ex_lua_add_fsys ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );

    return 0;
}
