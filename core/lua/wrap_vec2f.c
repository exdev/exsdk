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
    int nargs = lua_gettop(_l);

    if ( nargs != 2 ) {
        luaL_error ( _l, "Invalid number of arguments, should be 2" );
        lua_pushnil (_l);
        return 1;
    }

    p = ex_malloc ( sizeof(ex_vec2f_t) );
    ex_vec2f_set ( (ex_vec2f_t *)p, (float)luaL_checknumber(_l,1), (float)luaL_checknumber(_l,2) );

    lua_pushlightuserdata ( _l, p );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int vec2f_delete ( lua_State *_l ) {
    // TODO:
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "vec2f_new",      vec2f_new },
    { "vec2f_delete",   vec2f_delete },
    { NULL, NULL }
};

int luaopen_vec2f ( lua_State *_l ) {
    luaL_newlib(_l, lib);
    return 1;
}
