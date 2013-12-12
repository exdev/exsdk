// ======================================================================================
// File         : wrap_window.c
// Author       : Wu Jie 
// Last Change  : 05/07/2013 | 14:48:33 PM | Tuesday,May
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "SDL.h"

#include "wiz.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

///////////////////////////////////////////////////////////////////////////////
// functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_create_window ( lua_State *_l ) {
    int refID;

    ex_lua_check_nargs(_l,3);

    lua_pushvalue(_l,1);
    refID = luaL_ref(_l,LUA_REGISTRYINDEX);
    wiz_create_window ( _l, refID, luaL_checkint(_l,2), luaL_checkint(_l,3) );

    //
    lua_pushinteger(_l,refID);
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_destroy_window ( lua_State *_l ) {
    ex_lua_check_nargs(_l,1);

    wiz_destroy_window ( _l, luaL_checkint(_l,1) );

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_repaint_window ( lua_State *_l ) {
    ex_lua_check_nargs(_l,1);

    wiz_repaint_window (luaL_checkint(_l,1));

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_get_window_width ( lua_State *_l ) {
    int w, h;

    ex_lua_check_nargs(_l,1);
    wiz_get_window_size( luaL_checkint(_l,1), &w, &h );

    //
    lua_pushinteger( _l, w );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_get_window_height ( lua_State *_l ) {
    int w, h;

    ex_lua_check_nargs(_l,1);
    wiz_get_window_size( luaL_checkint(_l,1), &w, &h );

    //
    lua_pushinteger( _l, h );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
extern void set_window_background ( int, int, int, int );
// ------------------------------------------------------------------ 

static int __lua_set_window_background ( lua_State *_l ) {
    ex_lua_check_nargs(_l,4);
    wiz_set_window_background( luaL_checkint(_l,1),
                               luaL_checkint(_l,2),
                               luaL_checkint(_l,3),
                               luaL_checkint(_l,4) );

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "create_window",          __lua_create_window },
    { "destroy_window",         __lua_destroy_window },
    { "repaint_window",         __lua_repaint_window },
    { "get_window_width",       __lua_get_window_width },
    { "get_window_height",      __lua_get_window_height },
    { "set_window_background",  __lua_set_window_background },
    { NULL, NULL }
};

int __wiz_lua_add_window ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );
    return 0;
}
