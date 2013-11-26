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

static size_t cached_strlen = -1;
static const char *cached_str = NULL;
static size_t iterator = 0;

///////////////////////////////////////////////////////////////////////////////
// functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void __check_cache ( const char *_str ) {
    if ( cached_str != _str ) {
        cached_str = _str;
        cached_strlen = strlen(cached_str);
        iterator = 0;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_utf8_iterate ( lua_State *_l ) {
    const char *str;
    int r;

    ex_lua_check_nargs(_l,1);

    str = luaL_checkstring ( _l, 1 );
    __check_cache (str);

    iterator += utf8proc_iterate( cached_str+iterator, cached_strlen-iterator, &r );
    lua_pushinteger(_l,r);
    lua_pushboolean(_l,iterator >= cached_strlen);

    return 2;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_utf8_length ( lua_State *_l ) {
    const char *str;
    int r, dummy;
    size_t pos;

    ex_lua_check_nargs(_l,1);

    str = luaL_checkstring ( _l, 1 );
    __check_cache (str);

    pos = 0;
    while ( pos < cached_strlen ) {
        pos += utf8proc_iterate (str+pos, cached_strlen-pos, &dummy);
        ++r;
    }

    lua_pushinteger(_l,r);

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "utf8_iterate",          __lua_utf8_iterate },
    { "utf8_length",           __lua_utf8_length },
    { NULL, NULL }
};

int __ex_lua_add_utf8 ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );
    return 0;
}
