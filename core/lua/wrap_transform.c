// ======================================================================================
// File         : wrap_transform.c
// Author       : Wu Jie 
// Last Change  : 02/27/2013 | 16:16:06 PM | Wednesday,February
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

extern size_t __ex_al_transform_pool_request ( ALLEGRO_TRANSFORM ** );
extern void __ex_al_transform_pool_return ( size_t );
ALLEGRO_TRANSFORM *__ex_al_transform_pool_get ( size_t );

///////////////////////////////////////////////////////////////////////////////
// functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_transform_identity ( lua_State *_l ) {
    size_t handle;
    ALLEGRO_TRANSFORM *t;

    ex_lua_check_nargs(_l,0);

    handle = __ex_al_transform_pool_request ( &t );
    al_identity_transform (t);

    lua_pushinteger ( _l, handle );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_transform_dead ( lua_State *_l ) {
    size_t handle;

    ex_lua_check_nargs(_l,1);

    handle = luaL_checkinteger( _l, 1 );
    if ( handle != -1 )
        __ex_al_transform_pool_return(handle);

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_transform_current ( lua_State *_l ) {
    size_t handle;
    ALLEGRO_TRANSFORM *t;

    ex_lua_check_nargs(_l,0);

    handle = __ex_al_transform_pool_request ( &t );
    al_copy_transform(t, al_get_current_transform());

    lua_pushinteger ( _l, handle );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_transform_apply ( lua_State *_l ) {
    size_t handle;
    ALLEGRO_TRANSFORM *t;

    ex_lua_check_nargs(_l,1);

    handle = luaL_checkinteger( _l, 1 );
    t = __ex_al_transform_pool_get(handle);

    al_use_transform(t);

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_transform_translate ( lua_State *_l ) {
    size_t handle;
    ALLEGRO_TRANSFORM *t;

    ex_lua_check_nargs(_l,3);

    handle = luaL_checkinteger( _l, 1 );
    t = __ex_al_transform_pool_get(handle);

    al_translate_transform ( t, 
                             (float)luaL_checknumber(_l,2),
                             (float)luaL_checknumber(_l,3) );

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_transform_scale ( lua_State *_l ) {
    size_t handle;
    ALLEGRO_TRANSFORM *t;

    ex_lua_check_nargs(_l,3);

    handle = luaL_checkinteger( _l, 1 );
    t = __ex_al_transform_pool_get(handle);

    al_scale_transform ( t, 
                         (float)luaL_checknumber(_l,2),
                         (float)luaL_checknumber(_l,3) );

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_transform_rotate ( lua_State *_l ) {
    size_t handle;
    ALLEGRO_TRANSFORM *t;

    ex_lua_check_nargs(_l,2);

    handle = luaL_checkinteger( _l, 1 );
    t = __ex_al_transform_pool_get(handle);

    al_rotate_transform ( t, 
                         (float)luaL_checknumber(_l,2) );

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_transform_shear ( lua_State *_l ) {
    size_t handle;
    ALLEGRO_TRANSFORM *t;

    ex_lua_check_nargs(_l,3);

    handle = luaL_checkinteger( _l, 1 );
    t = __ex_al_transform_pool_get(handle);

    t->m[1][0] = (float)luaL_checknumber(_l,2); // shear x
    t->m[0][1] = (float)luaL_checknumber(_l,3); // shear y

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_transform_compose ( lua_State *_l ) {
    size_t handle;
    ALLEGRO_TRANSFORM *t1, *t2;

    ex_lua_check_nargs(_l,2);

    handle = luaL_checkinteger( _l, 1 );
    t1 = __ex_al_transform_pool_get(handle);

    handle = luaL_checkinteger( _l, 2 );
    t2 = __ex_al_transform_pool_get(handle);

    al_compose_transform ( t1, t2 ); 

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// al_use_transform
// al_build_transform
// al_invert_transform
// al_check_inverse
// al_transform_coordinates
// al_compose_transform
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "transform_identity",       __lua_transform_identity },
    { "transform_dead",           __lua_transform_dead },
    { "transform_current",        __lua_transform_current },
    { "transform_apply",          __lua_transform_apply },
    { "transform_translate",      __lua_transform_translate },
    { "transform_rotate",         __lua_transform_rotate },
    { "transform_scale",          __lua_transform_scale },
    { "transform_shear",          __lua_transform_shear },
    { "transform_compose",        __lua_transform_compose },
    { NULL, NULL }
};

int __ex_lua_add_transform ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );
    return 0;
}
