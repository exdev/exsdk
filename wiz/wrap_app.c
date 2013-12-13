// ======================================================================================
// File         : wrap_app.c
// Author       : Wu Jie 
// Last Change  : 05/07/2013 | 17:29:47 PM | Tuesday,May
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "wiz.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

///////////////////////////////////////////////////////////////////////////////
// functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_open_app ( lua_State *_l ) {
    const char *path;

    ex_lua_check_nargs(_l,1);

    path = luaL_checkstring(_l,1);

    ex_assert ( path != NULL );

    // if the media_path exists, use it. if not, try to search it in the app/ directory
    if ( ex_os_exists (path) == false ) {
        return luaL_error ( _l, "[wiz] Error: Can't load project at %s", path );
    }

    ex_log ( "[wiz] Open project: %s", path  );

    // mount the dir to __wiz__/
    if ( ex_fsys_mount( path, "__wiz__", true ) != 0 )
        return luaL_error ( _l, "[wiz] Error: Can't mount dir %s", path );

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_close_app ( lua_State *_l ) {
    // TODO: unmount app dir
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_test ( lua_State *_l ) {
    ex_log ( "The up value is = %s", lua_getupvalue(_l,1,1) );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "open_app",  __lua_open_app },
    { "close_app", __lua_close_app },
    { "test",      __lua_test },
    { NULL, NULL }
};

int __wiz_lua_add_app ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );
    return 0;
}
