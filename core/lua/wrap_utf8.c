// ======================================================================================
// File         : wrap_utf8.c
// Author       : Wu Jie 
// Last Change  : 11/26/2013 | 16:19:08 PM | Tuesday,November
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "utf8proc.h"

///////////////////////////////////////////////////////////////////////////////
// functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_utf8_list ( lua_State *_l ) {
    const char *str;
    int id;
    int index;

    ex_lua_check_nargs(_l,1);

    str = luaL_checkstring ( _l, 1 );
    lua_newtable(_l);

    index = 0;
    while ( *str ) {
        str += utf8proc_iterate ((const uint8_t *)str, -1, &id);

        lua_pushinteger(_l,index+1);
        lua_pushinteger(_l,id);
        lua_settable(_l,-3);
        ++index;
    }

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "utf8_list",          __lua_utf8_list },
    { NULL, NULL }
};

int __ex_lua_add_utf8 ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );
    return 0;
}
