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

static int __lua_canvas_clear ( lua_State *_l ) {
    ex_lua_check_nargs(_l,3);

    al_clear_to_color( al_map_rgb_f( (float)luaL_checknumber(_l,1),
                                     (float)luaL_checknumber(_l,2),
                                     (float)luaL_checknumber(_l,3)
                                   ) );

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_canvas_flush ( lua_State *_l ) {
    al_flip_display();
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_canvas_hold_bitmap_drawing ( lua_State *_l ) {
    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TBOOLEAN );
    al_hold_bitmap_drawing( lua_toboolean(_l,1) );

    return 0;
} 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_canvas_draw_texture ( lua_State *_l ) {
    ALLEGRO_BITMAP *bitmap;

    ex_lua_check_nargs(_l,3);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    bitmap = lua_touserdata(_l,1);

    al_draw_bitmap( bitmap, 

                    // x, y
                    (float)luaL_checknumber(_l,2), 
                    (float)luaL_checknumber(_l,3),

                    // flags
                    0 );

	return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_canvas_draw_texture_region ( lua_State *_l ) {
    ALLEGRO_BITMAP *bitmap;

    ex_lua_check_nargs(_l,7);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    bitmap = lua_touserdata(_l,1);

    al_draw_bitmap_region( bitmap, 

                           // sx,sy,sw,sh
                           (float)luaL_checknumber(_l,4), 
                           (float)luaL_checknumber(_l,5),
                           (float)luaL_checknumber(_l,6),
                           (float)luaL_checknumber(_l,7),

                           // x, y
                           (float)luaL_checknumber(_l,2), 
                           (float)luaL_checknumber(_l,3),

                           // flags
                           0 );

	return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "canvas_clear",                __lua_canvas_clear },
    { "canvas_flush",                __lua_canvas_flush },
    { "canvas_hold_bitmap_drawing",  __lua_canvas_hold_bitmap_drawing },
    { "canvas_draw_texture",         __lua_canvas_draw_texture },
    { "canvas_draw_texture_region",  __lua_canvas_draw_texture_region },
    { NULL, NULL }
};

int __ex_lua_add_canvas ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );
    return 0;
}
