// ======================================================================================
// File         : wrap_window.c
// Author       : Wu Jie 
// Last Change  : 05/07/2013 | 14:48:33 PM | Tuesday,May
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
extern void create_window ( int, int, int );
// ------------------------------------------------------------------ 

static int __lua_create_window ( lua_State *_l ) {
    int refID;

    ex_lua_check_nargs(_l,3);

    lua_pushvalue(_l,1);
    refID = luaL_ref(_l,LUA_REGISTRYINDEX);
    create_window ( refID, luaL_checkint(_l,2), luaL_checkint(_l,3) );

    //
    lua_pushinteger(_l,refID);
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
extern void destroy_window ( int );
// ------------------------------------------------------------------ 

static int __lua_destroy_window ( lua_State *_l ) {
    ex_lua_check_nargs(_l,1);

    destroy_window (luaL_checkint(_l,1));

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
extern void repaint_window ( int );
// ------------------------------------------------------------------ 

static int __lua_repaint_window ( lua_State *_l ) {
    ex_lua_check_nargs(_l,1);

    repaint_window (luaL_checkint(_l,1));

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
extern ALLEGRO_DISPLAY *get_display ( int );
// ------------------------------------------------------------------ 

static int __lua_get_window_width ( lua_State *_l ) {
    ALLEGRO_DISPLAY *display;

    ex_lua_check_nargs(_l,1);
    display = get_display( luaL_checkint(_l,1) );

    //
    lua_pushinteger( _l, al_get_display_width(display) );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_get_window_height ( lua_State *_l ) {
    ALLEGRO_DISPLAY *display;

    ex_lua_check_nargs(_l,1);
    display = get_display( luaL_checkint(_l,1) );

    //
    lua_pushinteger( _l, al_get_display_height(display) );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "create_window",     __lua_create_window },
    { "destroy_window",    __lua_destroy_window },
    { "repaint_window",    __lua_repaint_window },
    { "get_window_width",    __lua_get_window_width },
    { "get_window_height",   __lua_get_window_height },
    { NULL, NULL }
};

int __ex_lua_add_window ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );
    return 0;
}
