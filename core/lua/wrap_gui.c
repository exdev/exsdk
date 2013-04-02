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

static int __lua_gui_set_texture ( lua_State *_l ) {
    ALLEGRO_BITMAP *bitmap;

    ex_lua_check_nargs(_l,1);

    // get bitmap ptr
    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    bitmap = lua_touserdata(_l,1);

    //
    ex_ui_set_texture(bitmap);

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_gui_set_matrix ( lua_State *_l ) {
    ex_mat33f_t mat;

    ex_lua_check_nargs(_l,9);

    ex_mat33f_set ( &mat, 
                    (float)luaL_checknumber(_l,1),
                    (float)luaL_checknumber(_l,2),
                    (float)luaL_checknumber(_l,3),
                    (float)luaL_checknumber(_l,4),
                    (float)luaL_checknumber(_l,5),
                    (float)luaL_checknumber(_l,6),
                    (float)luaL_checknumber(_l,7),
                    (float)luaL_checknumber(_l,8),
                    (float)luaL_checknumber(_l,9) );
    ex_ui_set_matrix( &mat );

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_gui_set_color ( lua_State *_l ) {
    ex_vec4f_t color;

    ex_lua_check_nargs(_l,4);

    ex_vec4f_set ( &color,
                   (float)luaL_checknumber(_l,1),
                   (float)luaL_checknumber(_l,2),
                   (float)luaL_checknumber(_l,3),
                   (float)luaL_checknumber(_l,4)
                 );
    ex_ui_set_color ( &color );

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_gui_draw_texture ( lua_State *_l ) {
    ex_lua_check_nargs(_l,8);

    ex_ui_draw_texture ( luaL_checkint(_l,1),
                         luaL_checkint(_l,2),
                         luaL_checkint(_l,3),
                         luaL_checkint(_l,4),
                         luaL_checkint(_l,5),
                         luaL_checkint(_l,6),
                         luaL_checkint(_l,7),
                         luaL_checkint(_l,8)
                       );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_gui_draw_border_texture ( lua_State *_l ) {
    ex_lua_check_nargs(_l,12);

    ex_ui_draw_border_texture ( luaL_checkint(_l,1 ),
                                luaL_checkint(_l,2 ),
                                luaL_checkint(_l,3 ),
                                luaL_checkint(_l,4 ),
                                luaL_checkint(_l,5 ),
                                luaL_checkint(_l,6 ),
                                luaL_checkint(_l,7 ),
                                luaL_checkint(_l,8 ),
                                luaL_checkint(_l,9 ),
                                luaL_checkint(_l,10),
                                luaL_checkint(_l,11),
                                luaL_checkint(_l,12)
                              );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_gui_flush ( lua_State *_l ) {
    ex_lua_check_nargs(_l,0);
    ex_ui_flush();
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "gui_set_texture",            __lua_gui_set_texture },
    { "gui_set_matrix",             __lua_gui_set_matrix },
    { "gui_set_color",              __lua_gui_set_color },
    { "gui_draw_texture",           __lua_gui_draw_texture },
    { "gui_draw_border_texture",    __lua_gui_draw_border_texture },
    { "gui_flush",                  __lua_gui_flush },
    { NULL, NULL }
};

int __ex_lua_add_gui ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );
    return 0;
}
