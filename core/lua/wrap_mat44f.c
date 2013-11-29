// ======================================================================================
// File         : wrap_mat44f.c
// Author       : Wu Jie 
// Last Change  : 11/29/2013 | 14:37:08 PM | Friday,November
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

extern size_t __ex_mat44f_pool_request ( ex_mat44f_t ** );
extern void __ex_mat44f_pool_return ( size_t );
ex_mat44f_t *__ex_mat44f_pool_get ( size_t );

///////////////////////////////////////////////////////////////////////////////
// functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_mat44f_new ( lua_State *_l ) {
    size_t handle;
    ex_mat44f_t *m;

    ex_lua_check_nargs(_l,0);

    handle = __ex_mat44f_pool_request ( &m );
    ex_mat44f_identity(m);

    lua_pushinteger ( _l, handle );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_mat44f_delete ( lua_State *_l ) {
    size_t handle;

    ex_lua_check_nargs(_l,1);

    handle = luaL_checkinteger( _l, 1 );
    if ( handle != -1 )
        __ex_mat44f_pool_return(handle);

    return 0;
}

// TODO { 
// // ------------------------------------------------------------------ 
// // Desc: 
// // ------------------------------------------------------------------ 

// static int __lua_mat44f_translate ( lua_State *_l ) {
//     size_t handle;
//     ex_mat44f_t *m;

//     ex_lua_check_nargs(_l,3);

//     handle = luaL_checkinteger( _l, 1 );
//     m = __ex_mat44f_pool_get(handle);

//     al_translate_transform ( m, 
//                              (float)luaL_checknumber(_l,2),
//                              (float)luaL_checknumber(_l,3) );

//     return 0;
// }
// } TODO end 

// TODO { 
// // ------------------------------------------------------------------ 
// // Desc: 
// // ------------------------------------------------------------------ 

// static int __lua_mat44f_scale ( lua_State *_l ) {
//     size_t handle;
//     ex_mat44f_t *m;

//     ex_lua_check_nargs(_l,3);

//     handle = luaL_checkinteger( _l, 1 );
//     m = __ex_mat44f_pool_get(handle);

//     al_scale_transform ( m, 
//                          (float)luaL_checknumber(_l,2),
//                          (float)luaL_checknumber(_l,3) );

//     return 0;
// }
// } TODO end 

// TODO { 
// // ------------------------------------------------------------------ 
// // Desc: 
// // ------------------------------------------------------------------ 

// static int __lua_mat44f_rotate ( lua_State *_l ) {
//     size_t handle;
//     ex_mat44f_t *m;

//     ex_lua_check_nargs(_l,2);

//     handle = luaL_checkinteger( _l, 1 );
//     m = __ex_mat44f_pool_get(handle);

//     al_rotate_transform ( m, 
//                          (float)luaL_checknumber(_l,2) );

//     return 0;
// }
// } TODO end 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_mat44f_shear ( lua_State *_l ) {
    size_t handle;
    ex_mat44f_t *m;

    ex_lua_check_nargs(_l,3);

    handle = luaL_checkinteger( _l, 1 );
    m = __ex_mat44f_pool_get(handle);

    ex_mat44f_m_set( m, 1, 0, (float)luaL_checknumber(_l,2) ); // shear x
    ex_mat44f_m_set( m, 0, 1, (float)luaL_checknumber(_l,3) ); // shear y

    return 0;
}

// TODO { 
// // ------------------------------------------------------------------ 
// // Desc: 
// // ------------------------------------------------------------------ 

// static int __lua_mat44f_compose ( lua_State *_l ) {
//     size_t handle;
//     ex_mat44f_t *t1, *t2;

//     ex_lua_check_nargs(_l,2);

//     handle = luaL_checkinteger( _l, 1 );
//     t1 = __ex_mat44f_pool_get(handle);

//     handle = luaL_checkinteger( _l, 2 );
//     t2 = __ex_mat44f_pool_get(handle);

//     al_compose_transform ( t1, t2 ); 

//     return 0;
// }
// } TODO end 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "mat44f_new",           __lua_mat44f_new },
    { "mat44f_delete",         __lua_mat44f_delete },
    // { "mat44f_translate",      __lua_mat44f_translate },
    // { "mat44f_rotate",         __lua_mat44f_rotate },
    // { "mat44f_scale",          __lua_mat44f_scale },
    { "mat44f_shear",          __lua_mat44f_shear },
    // { "mat44f_compose",        __lua_mat44f_compose },
    { NULL, NULL }
};

int __ex_lua_add_transform ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );
    return 0;
}
