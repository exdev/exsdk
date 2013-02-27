// ======================================================================================
// File         : wrap_vec4f.c
// Author       : Wu Jie 
// Last Change  : 02/27/2013 | 15:12:37 PM | Wednesday,February
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

extern size_t __ex_vec4f_pool_request ( ex_vec4f_t ** );
extern void __ex_vec4f_pool_return ( size_t );
ex_vec4f_t *__ex_vec4f_pool_get ( size_t );

///////////////////////////////////////////////////////////////////////////////
// functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_new ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *v;

    ex_lua_check_nargs(_l,4);

    handle = __ex_vec4f_pool_request ( &v );
    ex_vec4f_set ( v, 
                   (float)luaL_checknumber(_l,1), 
                   (float)luaL_checknumber(_l,2),
                   (float)luaL_checknumber(_l,3),
                   (float)luaL_checknumber(_l,4)
                   );

    lua_pushinteger ( _l, handle );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_delete ( lua_State *_l ) {
    size_t handle;

    ex_lua_check_nargs(_l,1);

    handle = luaL_checkinteger( _l, 1 );
    if ( handle != -1 )
        __ex_vec4f_pool_return(handle);

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_get_x ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *v;

    ex_lua_check_nargs(_l,1);

    handle = luaL_checkinteger( _l, 1 );
    v = __ex_vec4f_pool_get(handle);

    lua_pushnumber( _l, v->x );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_get_y ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *v;

    ex_lua_check_nargs(_l,1);

    handle = luaL_checkinteger( _l, 1 );
    v = __ex_vec4f_pool_get(handle);

    lua_pushnumber( _l, v->y );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_get_z ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *v;

    ex_lua_check_nargs(_l,1);

    handle = luaL_checkinteger( _l, 1 );
    v = __ex_vec4f_pool_get(handle);

    lua_pushnumber( _l, v->z );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_get_w ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *v;

    ex_lua_check_nargs(_l,1);

    handle = luaL_checkinteger( _l, 1 );
    v = __ex_vec4f_pool_get(handle);

    lua_pushnumber( _l, v->w );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_set_x ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *v;

    ex_lua_check_nargs(_l,2);

    handle = luaL_checkinteger( _l, 1 );
    v = __ex_vec4f_pool_get(handle);

    v->x = (float)luaL_checknumber(_l,2);
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_set_y ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *v;

    ex_lua_check_nargs(_l,2);

    handle = luaL_checkinteger( _l, 1 );
    v = __ex_vec4f_pool_get(handle);

    v->y = (float)luaL_checknumber(_l,2);
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_set_z ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *v;

    ex_lua_check_nargs(_l,2);

    handle = luaL_checkinteger( _l, 1 );
    v = __ex_vec4f_pool_get(handle);

    v->z = (float)luaL_checknumber(_l,2);
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_set_w ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *v;

    ex_lua_check_nargs(_l,2);

    handle = luaL_checkinteger( _l, 1 );
    v = __ex_vec4f_pool_get(handle);

    v->w = (float)luaL_checknumber(_l,2);
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_add ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *r, *v1, *v2;

    ex_lua_check_nargs(_l,3);

    handle = luaL_checkinteger( _l, 1 );
    r = __ex_vec4f_pool_get(handle);

    handle = luaL_checkinteger( _l, 2 );
    v1 = __ex_vec4f_pool_get(handle);

    handle = luaL_checkinteger( _l, 3 );
    v2 = __ex_vec4f_pool_get(handle);

    ex_vec4f_add ( r, v1, v2 );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_sub ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *r, *v1, *v2;

    ex_lua_check_nargs(_l,3);

    handle = luaL_checkinteger( _l, 1 );
    r = __ex_vec4f_pool_get(handle);

    handle = luaL_checkinteger( _l, 2 );
    v1 = __ex_vec4f_pool_get(handle);

    handle = luaL_checkinteger( _l, 3 );
    v2 = __ex_vec4f_pool_get(handle);

    ex_vec4f_sub ( r, v1, v2 );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_mul ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *r, *v1, *v2;

    ex_lua_check_nargs(_l,3);

    handle = luaL_checkinteger( _l, 1 );
    r = __ex_vec4f_pool_get(handle);

    handle = luaL_checkinteger( _l, 2 );
    v1 = __ex_vec4f_pool_get(handle);

    handle = luaL_checkinteger( _l, 3 );
    v2 = __ex_vec4f_pool_get(handle);

    ex_vec4f_mul ( r, v1, v2 );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_mul_scalar ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *r, *v1;
    float s;

    ex_lua_check_nargs(_l,3);

    handle = luaL_checkinteger( _l, 1 );
    r = __ex_vec4f_pool_get(handle);

    handle = luaL_checkinteger( _l, 2 );
    v1 = __ex_vec4f_pool_get(handle);

    s = (float)luaL_checknumber(_l,3);

    ex_vec4f_mul_scalar ( r, v1, s );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_div ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *r, *v1, *v2;

    ex_lua_check_nargs(_l,3);

    handle = luaL_checkinteger( _l, 1 );
    r = __ex_vec4f_pool_get(handle);

    handle = luaL_checkinteger( _l, 2 );
    v1 = __ex_vec4f_pool_get(handle);

    handle = luaL_checkinteger( _l, 3 );
    v2 = __ex_vec4f_pool_get(handle);

    ex_vec4f_div ( r, v1, v2 );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_div_scalar ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *r, *v1;
    float s;

    ex_lua_check_nargs(_l,3);

    handle = luaL_checkinteger( _l, 1 );
    r = __ex_vec4f_pool_get(handle);

    handle = luaL_checkinteger( _l, 2 );
    v1 = __ex_vec4f_pool_get(handle);

    s = (float)luaL_checknumber(_l,3);

    ex_vec4f_div_scalar ( r, v1, s );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_scalar_div_vec4f ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *r, *v1;
    float s;

    ex_lua_check_nargs(_l,3);

    handle = luaL_checkinteger( _l, 1 );
    r = __ex_vec4f_pool_get(handle);

    s = (float)luaL_checknumber(_l,2);

    handle = luaL_checkinteger( _l, 3 );
    v1 = __ex_vec4f_pool_get(handle);

    ex_scalar_div_vec4f ( r, s, v1 );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_neg ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *r, *v1;

    ex_lua_check_nargs(_l,2);

    handle = luaL_checkinteger( _l, 1 );
    r = __ex_vec4f_pool_get(handle);

    handle = luaL_checkinteger( _l, 2 );
    v1 = __ex_vec4f_pool_get(handle);

    ex_vec4f_get_neg ( r, v1 );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_eq ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *v1, *v2;
    bool r;

    ex_lua_check_nargs(_l,2);

    handle = luaL_checkinteger( _l, 1 );
    v1 = __ex_vec4f_pool_get(handle);

    handle = luaL_checkinteger( _l, 2 );
    v2 = __ex_vec4f_pool_get(handle);

    r = ex_vec4f_is_equal ( v1, v2 );
    lua_pushboolean(_l,r);

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_normalize ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *v1;

    ex_lua_check_nargs(_l,1);

    handle = luaL_checkinteger( _l, 1 );
    v1 = __ex_vec4f_pool_get(handle);

    ex_vec4f_normalize(v1);

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_get_normalize ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *v1, *v2;

    ex_lua_check_nargs(_l,2);

    handle = luaL_checkinteger( _l, 1 );
    v1 = __ex_vec4f_pool_get(handle);

    handle = luaL_checkinteger( _l, 2 );
    v2 = __ex_vec4f_pool_get(handle);

    ex_vec4f_get_normalize(v1,v2);
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_len ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *v1;

    ex_lua_check_nargs(_l,1);

    handle = luaL_checkinteger( _l, 1 );
    v1 = __ex_vec4f_pool_get(handle);

    lua_pushnumber( _l, ex_vec4f_len(v1) );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_lenSQR ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *v1;

    ex_lua_check_nargs(_l,1);

    handle = luaL_checkinteger( _l, 1 );
    v1 = __ex_vec4f_pool_get(handle);

    lua_pushnumber( _l, ex_vec4f_lenSQR(v1) );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_vec4f_lerp ( lua_State *_l ) {
    size_t handle;
    ex_vec4f_t *r, *v1, *v2;
    float t, x, y, z, w;

    ex_lua_check_nargs(_l,4);

    handle = luaL_checkinteger( _l, 1 );
    r = __ex_vec4f_pool_get(handle);

    handle = luaL_checkinteger( _l, 2 );
    v1 = __ex_vec4f_pool_get(handle);

    handle = luaL_checkinteger( _l, 3 );
    v2 = __ex_vec4f_pool_get(handle);

    t = (float)luaL_checknumber(_l,4);

    // lerp
    x = ex_lerpf ( v1->x, v2->x, t );
    y = ex_lerpf ( v1->y, v2->y, t );
    z = ex_lerpf ( v1->z, v2->z, t );
    w = ex_lerpf ( v1->w, v2->w, t );

    ex_vec4f_set ( (ex_vec4f_t *)r, x, y, z, w );
    lua_pushlightuserdata ( _l, r );

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "vec4f_new",              __lua_vec4f_new },
    { "vec4f_delete",           __lua_vec4f_delete },
    { "vec4f_get_x",            __lua_vec4f_get_x },
    { "vec4f_get_y",            __lua_vec4f_get_y },
    { "vec4f_get_z",            __lua_vec4f_get_z },
    { "vec4f_get_w",            __lua_vec4f_get_w },
    { "vec4f_set_x",            __lua_vec4f_set_x },
    { "vec4f_set_y",            __lua_vec4f_set_y },
    { "vec4f_set_z",            __lua_vec4f_set_z },
    { "vec4f_set_w",            __lua_vec4f_set_w },
    { "vec4f_add",              __lua_vec4f_add },
    { "vec4f_sub",              __lua_vec4f_sub },
    { "vec4f_mul",              __lua_vec4f_mul },
    { "vec4f_mul_scalar",       __lua_vec4f_mul_scalar },
    { "vec4f_div",              __lua_vec4f_div },
    { "vec4f_div_scalar",       __lua_vec4f_div_scalar },
    { "scalar_div_vec4f",       __lua_scalar_div_vec4f },
    { "vec4f_neg",              __lua_vec4f_neg },
    { "vec4f_eq",               __lua_vec4f_eq },
    { "vec4f_normalize",        __lua_vec4f_normalize },
    { "vec4f_get_normalize",    __lua_vec4f_get_normalize },
    { "vec4f_len",              __lua_vec4f_len },
    { "vec4f_lenSQR",           __lua_vec4f_lenSQR },
    { "vec4f_lerp",             __lua_vec4f_lerp },
    { NULL, NULL }
};

int __ex_lua_add_vec4f ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );
    return 0;
}
