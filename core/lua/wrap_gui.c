// ======================================================================================
// File         : wrap_gui.c
// Author       : Wu Jie 
// Last Change  : 03/08/2013 | 15:19:36 PM | Friday,March
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
// ------------------------------------------------------------------ 

static int __lua_gui_draw_texture ( lua_State *_l ) {
    ALLEGRO_DISPLAY *display;

    // TODO:

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { NULL, NULL }
};

int __ex_lua_add_gui ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );
    return 0;
}