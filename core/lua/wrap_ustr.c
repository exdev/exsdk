// ======================================================================================
// File         : wrap_ustr.c
// Author       : Wu Jie 
// Last Change  : 02/22/2013 | 16:30:23 PM | Friday,February
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "allegro5/allegro.h"
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

static int __lua_ustr_new ( lua_State *_l ) {
    const char *arg;
    ALLEGRO_USTR *r;

    ex_lua_check_nargs(_l,1);

    arg = luaL_checkstring(_l,1);
    r = al_ustr_new(arg);

    lua_pushlightuserdata ( _l, r );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_ustr_delete ( lua_State *_l ) {
    void *p;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    p = lua_touserdata(_l,1);

    al_ustr_free((ALLEGRO_USTR *)p);
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_ustr_get ( lua_State *_l ) {
    void *p;
    int pos;
    int r;

    ex_lua_check_nargs(_l,2);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    p = lua_touserdata(_l,1);

    pos = luaL_checkint(_l,2);

    r = al_ustr_get ( (const ALLEGRO_USTR *)p, pos );
    lua_pushinteger(_l,r);

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_ustr_length ( lua_State *_l ) {
    void *p;
    int r;

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    p = lua_touserdata(_l,1);

    r = al_ustr_length ( (const ALLEGRO_USTR *)p );
    lua_pushinteger(_l,r);

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "ustr_new",              __lua_ustr_new },
    { "ustr_delete",           __lua_ustr_delete },
    { "ustr_get",              __lua_ustr_get },
    { "ustr_length",           __lua_ustr_length },
    { NULL, NULL }
};

int __ex_lua_add_ustr ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );
    return 0;
}
