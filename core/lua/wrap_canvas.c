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
    ALLEGRO_COLOR tint;

    ex_lua_check_nargs(_l,7);

    // get bitmap ptr
    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    bitmap = lua_touserdata(_l,1);

    // convert tint color
    tint = al_map_rgba_f ( (float)luaL_checknumber(_l,2),
                           (float)luaL_checknumber(_l,3),
                           (float)luaL_checknumber(_l,4),
                           (float)luaL_checknumber(_l,5) );

    al_draw_tinted_scaled_rotated_bitmap ( bitmap, 

                                           // tint color
                                           tint,

                                           // center x,y
                                           // (float)luaL_checknumber(_l,6), 
                                           // (float)luaL_checknumber(_l,7),
                                           0.0f, 0.0f,

                                           // destination x,y
                                           (float)luaL_checknumber(_l,6), 
                                           (float)luaL_checknumber(_l,7),

                                           // scale x,y
                                           // (float)luaL_checknumber(_l,10), 
                                           // (float)luaL_checknumber(_l,11),
                                           1.0f, 1.0f,

                                           // angle (in radians)
                                           // (float)luaL_checknumber(_l,12), 
                                           0.0f,

                                           // flags
                                           0 );

	return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_canvas_draw_texture_region ( lua_State *_l ) {
    ALLEGRO_BITMAP *bitmap;
    ALLEGRO_COLOR tint;

    ex_lua_check_nargs(_l,11);

    // get bitmap ptr
    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    bitmap = lua_touserdata(_l,1);

    // convert tint color
    tint = al_map_rgba_f ( (float)luaL_checknumber(_l,2),
                           (float)luaL_checknumber(_l,3),
                           (float)luaL_checknumber(_l,4),
                           (float)luaL_checknumber(_l,5) );

    al_draw_tinted_scaled_rotated_bitmap_region( bitmap, 

                                                 // region x,y,w,h
                                                 (float)luaL_checknumber(_l,6), 
                                                 (float)luaL_checknumber(_l,7),
                                                 (float)luaL_checknumber(_l,8),
                                                 (float)luaL_checknumber(_l,9),

                                                 // tint color
                                                 tint,

                                                 // center x,y
                                                 // (float)luaL_checknumber(_l,10), 
                                                 // (float)luaL_checknumber(_l,11),
                                                 0.0f, 0.0f,

                                                 // destination x,y
                                                 (float)luaL_checknumber(_l,10), 
                                                 (float)luaL_checknumber(_l,11),

                                                 // scale x,y
                                                 // (float)luaL_checknumber(_l,14), 
                                                 // (float)luaL_checknumber(_l,15),
                                                 1.0f, 1.0f,

                                                 // angle (in radians)
                                                 // (float)luaL_checknumber(_l,16), 
                                                 0.0f,

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
