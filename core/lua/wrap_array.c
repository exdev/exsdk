// ======================================================================================
// File         : wrap_array.c
// Author       : Wu Jie 
// Last Change  : 02/16/2013 | 10:51:37 AM | Saturday,February
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

static int __lua_array_new ( lua_State *_l ) {
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_array_delete ( lua_State *_l ) {
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "array_new",          __lua_array_new },
    { "array_delete",       __lua_array_delete },
    // ex_array_set
    // ex_array_get
    // ex_array_add
    // ex_array_add_range
    // ex_array_insert
    // ex_array_insert_range
    // ex_array_ncpy
    // ex_array_remove_at
    // ex_array_remove_at_fast
    // ex_array_remove_range
    // ex_array_remove_all
    // ex_array_sort
    { NULL, NULL }
};

int __ex_lua_add_array ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );
    return 0;
}
