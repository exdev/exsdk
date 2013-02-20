// ======================================================================================
// File         : wrap_renderer.c
// Author       : Wu Jie 
// Last Change  : 02/20/2013 | 13:06:57 PM | Wednesday,February
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

static int __lua_draw_texture ( lua_State *_l ) {
    ALLEGRO_BITMAP *bitmap;

    ex_lua_check_nargs(_l,3);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    bitmap = lua_touserdata(_l,1);

    al_draw_bitmap( bitmap, 
                    (float)luaL_checknumber(_l,2), 
                    (float)luaL_checknumber(_l,3),
                    0 );

	return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "draw_texture",       __lua_draw_texture },
    { NULL, NULL }
};

int __ex_lua_add_renderer ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );
    return 0;
}
