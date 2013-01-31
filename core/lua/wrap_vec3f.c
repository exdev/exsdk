// ======================================================================================
// File         : wrap_vec3f.c
// Author       : Wu Jie 
// Last Change  : 01/31/2013 | 13:36:50 PM | Thursday,January
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

static int vec3f_new ( lua_State *_l ) {
    void *p;

    ex_lua_check_nargs(_l,3);

    p = ex_malloc ( sizeof(ex_vec3f_t) );
    ex_vec3f_set ( (ex_vec3f_t *)p, 
                   (float)luaL_checknumber(_l,1), 
                   (float)luaL_checknumber(_l,2),
                   (float)luaL_checknumber(_l,3)
                   );

    lua_pushlightuserdata ( _l, p );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int vec3f_delete ( lua_State *_l ) {
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

static int vec3f_get_x ( lua_State *_l ) {
    void *p;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    p = lua_touserdata(_l,1);

    lua_pushnumber( _l, ((ex_vec3f_t *)p)->x );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int vec3f_get_y ( lua_State *_l ) {
    void *p;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    p = lua_touserdata(_l,1);

    lua_pushnumber( _l, ((ex_vec3f_t *)p)->y );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int vec3f_get_z ( lua_State *_l ) {
    void *p;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    p = lua_touserdata(_l,1);

    lua_pushnumber( _l, ((ex_vec3f_t *)p)->z );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "vec3f_new",      vec3f_new },
    { "vec3f_delete",   vec3f_delete },
    { "vec3f_get_x",    vec3f_get_x },
    { "vec3f_get_y",    vec3f_get_y },
    { "vec3f_get_z",    vec3f_get_z },
    { NULL, NULL }
};

int luaopen_vec3f ( lua_State *_l ) {
    luaL_newlib(_l, lib);
    return 1;
}
