// ======================================================================================
// File         : wrap_vec2f.c
// Author       : Wu Jie 
// Last Change  : 01/28/2013 | 18:12:12 PM | Monday,January
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

static int vec2f_new ( lua_State *_l ) {
    void *p;

    ex_lua_check_nargs(_l,2);

    p = ex_malloc ( sizeof(ex_vec2f_t) );
    ex_vec2f_set ( (ex_vec2f_t *)p, (float)luaL_checknumber(_l,1), (float)luaL_checknumber(_l,2) );

    lua_pushlightuserdata ( _l, p );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int vec2f_delete ( lua_State *_l ) {
    void *p;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    p = lua_touserdata(_l,1);

    ex_free(p);
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int vec2f_get_x ( lua_State *_l ) {
    void *p;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    p = lua_touserdata(_l,1);

    lua_pushnumber( _l, ((ex_vec2f_t *)p)->x );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int vec2f_get_y ( lua_State *_l ) {
    void *p;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    p = lua_touserdata(_l,1);

    lua_pushnumber( _l, ((ex_vec2f_t *)p)->y );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "vec2f_new",      vec2f_new },
    { "vec2f_delete",   vec2f_delete },
    { "vec2f_get_x",    vec2f_get_x },
    { "vec2f_get_y",    vec2f_get_y },
    { NULL, NULL }
};

void __ex_lua_add_vec2f ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );
}
