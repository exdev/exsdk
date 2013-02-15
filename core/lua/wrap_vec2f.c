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

static int vec2f_set_x ( lua_State *_l ) {
    void *p;

    ex_lua_check_nargs(_l,2);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    p = lua_touserdata(_l,1);

    ((ex_vec2f_t *)p)->x = (float)luaL_checknumber(_l,2);
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int vec2f_set_y ( lua_State *_l ) {
    void *p;

    ex_lua_check_nargs(_l,2);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    p = lua_touserdata(_l,1);

    ((ex_vec2f_t *)p)->y = (float)luaL_checknumber(_l,2);
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int vec2f_add ( lua_State *_l ) {
    void *r, *v1, *v2;

    ex_lua_check_nargs(_l,3);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    r = lua_touserdata(_l,1);

    luaL_checktype( _l, 2, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,2);

    luaL_checktype( _l, 3, LUA_TLIGHTUSERDATA );
    v2 = lua_touserdata(_l,3);

    ex_vec2f_add ( r, v1, v2 );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int vec2f_sub ( lua_State *_l ) {
    void *r, *v1, *v2;

    ex_lua_check_nargs(_l,3);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    r = lua_touserdata(_l,1);

    luaL_checktype( _l, 2, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,2);

    luaL_checktype( _l, 3, LUA_TLIGHTUSERDATA );
    v2 = lua_touserdata(_l,3);

    ex_vec2f_sub ( r, v1, v2 );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int vec2f_mul ( lua_State *_l ) {
    void *r, *v1, *v2;

    ex_lua_check_nargs(_l,3);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    r = lua_touserdata(_l,1);

    luaL_checktype( _l, 2, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,2);

    luaL_checktype( _l, 3, LUA_TLIGHTUSERDATA );
    v2 = lua_touserdata(_l,3);

    ex_vec2f_mul ( r, v1, v2 );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int vec2f_mul_scalar ( lua_State *_l ) {
    void *r, *v1;
    float s;

    ex_lua_check_nargs(_l,3);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    r = lua_touserdata(_l,1);

    luaL_checktype( _l, 2, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,2);

    s = (float)luaL_checknumber(_l,3);

    ex_vec2f_mul_scalar ( r, v1, s );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int vec2f_div ( lua_State *_l ) {
    void *r, *v1, *v2;

    ex_lua_check_nargs(_l,3);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    r = lua_touserdata(_l,1);

    luaL_checktype( _l, 2, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,2);

    luaL_checktype( _l, 3, LUA_TLIGHTUSERDATA );
    v2 = lua_touserdata(_l,3);

    ex_vec2f_div ( r, v1, v2 );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int vec2f_div_scalar ( lua_State *_l ) {
    void *r, *v1;
    float s;

    ex_lua_check_nargs(_l,3);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    r = lua_touserdata(_l,1);

    luaL_checktype( _l, 2, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,2);

    s = (float)luaL_checknumber(_l,3);

    ex_vec2f_div_scalar ( r, v1, s );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int scalar_div_vec2f ( lua_State *_l ) {
    void *r, *v1;
    float s;

    ex_lua_check_nargs(_l,3);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    r = lua_touserdata(_l,1);

    s = (float)luaL_checknumber(_l,2);

    luaL_checktype( _l, 3, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,3);

    ex_scalar_div_vec2f ( r, s, v1 );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int vec2f_neg ( lua_State *_l ) {
    void *r, *v1;

    ex_lua_check_nargs(_l,2);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    r = lua_touserdata(_l,1);

    luaL_checktype( _l, 2, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,2);

    ex_vec2f_get_neg ( r, v1 );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int vec2f_eq ( lua_State *_l ) {
    void *v1, *v2;
    bool r;

    ex_lua_check_nargs(_l,2);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,1);

    luaL_checktype( _l, 2, LUA_TLIGHTUSERDATA );
    v2 = lua_touserdata(_l,2);

    r = ex_vec2f_is_equal ( v1, v2 );
    lua_pushboolean(_l,r);

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int vec2f_normalize ( lua_State *_l ) {
    void *v1;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,1);

    ex_vec2f_normalize(v1);

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int vec2f_get_normalize ( lua_State *_l ) {
    void *v1, *v2;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,1);

    ex_vec2f_get_normalize(v1,v2);

    lua_pushlightuserdata(_l,v2);
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int vec2f_len ( lua_State *_l ) {
    void *v1;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,1);

    lua_pushnumber( _l, ex_vec2f_len(v1) );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int vec2f_lenSQR ( lua_State *_l ) {
    void *v1;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    v1 = lua_touserdata(_l,1);

    lua_pushnumber( _l, ex_vec2f_lenSQR(v1) );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "vec2f_new",              vec2f_new },
    { "vec2f_delete",           vec2f_delete },
    { "vec2f_get_x",            vec2f_get_x },
    { "vec2f_get_y",            vec2f_get_y },
    { "vec2f_set_x",            vec2f_set_x },
    { "vec2f_set_y",            vec2f_set_y },
    { "vec2f_add",              vec2f_add },
    { "vec2f_sub",              vec2f_sub },
    { "vec2f_mul",              vec2f_mul },
    { "vec2f_mul_scalar",       vec2f_mul_scalar },
    { "vec2f_div",              vec2f_div },
    { "vec2f_div_scalar",       vec2f_div_scalar },
    { "scalar_div_vec2f",       scalar_div_vec2f },
    { "vec2f_neg",              vec2f_neg },
    { "vec2f_eq",               vec2f_eq },
    { "vec2f_normalize",        vec2f_normalize },
    { "vec2f_get_normalize",    vec2f_get_normalize },
    { "vec2f_len",              vec2f_len },
    { "vec2f_lenSQR",           vec2f_lenSQR },
    { NULL, NULL }
};

int __ex_lua_add_vec2f ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );
    return 0;
}
