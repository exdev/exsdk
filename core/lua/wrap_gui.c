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
    ex_renderer_t *renderer;
    ALLEGRO_BITMAP *bitmap;
    ex_recti_t pos, border, rect;
    ex_vec4f_t color;

    ex_lua_check_nargs(_l,17);

    // get bitmap ptr
    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    bitmap = lua_touserdata(_l,1);

    pos.x = (float)luaL_checknumber(_l,2);
    pos.y = (float)luaL_checknumber(_l,3);
    pos.w = (float)luaL_checknumber(_l,4);
    pos.h = (float)luaL_checknumber(_l,5);

    border.l = (float)luaL_checknumber(_l,6);
    border.r = (float)luaL_checknumber(_l,7);
    border.t = (float)luaL_checknumber(_l,8);
    border.b = (float)luaL_checknumber(_l,9);

    rect.x = (float)luaL_checknumber(_l,10);
    rect.y = (float)luaL_checknumber(_l,11);
    rect.w = (float)luaL_checknumber(_l,12);
    rect.h = (float)luaL_checknumber(_l,13);

    color.r = (float)luaL_checknumber(_l,14);
    color.g = (float)luaL_checknumber(_l,15);
    color.b = (float)luaL_checknumber(_l,16);
    color.a = (float)luaL_checknumber(_l,17);

    // 
    renderer = ex_current_renderer();
    ex_ui_draw_texture ( renderer,
                         bitmap,
                         pos,
                         border,
                         rect,
                         color );

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "gui_draw_texture",   __lua_gui_draw_texture },
    { NULL, NULL }
};

int __ex_lua_add_gui ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );
    return 0;
}
