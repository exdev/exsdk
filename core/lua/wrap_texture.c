// ======================================================================================
// File         : wrap_texture.c
// Author       : Wu Jie 
// Last Change  : 02/19/2013 | 15:10:22 PM | Tuesday,February
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

static int __lua_texture_load ( lua_State *_l ) {
    const char *path;
    ALLEGRO_BITMAP *bitmap;

    ex_lua_check_nargs(_l,1);

    al_set_new_bitmap_flags ( ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR );

    path = luaL_checkstring(_l,1);
    bitmap = al_load_bitmap(path);
    if ( bitmap == NULL ) {
        luaL_error ( _l, "Failed to load texture: %s", path );
    }

    //
    lua_pushlightuserdata ( _l, bitmap );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_texture_new ( lua_State *_l ) {
    int w,h;
    ALLEGRO_BITMAP *bitmap;

    ex_lua_check_nargs(_l,2);

    w = luaL_checkint(_l,1);
    h = luaL_checkint(_l,2);

    al_set_new_bitmap_flags ( ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR );
    bitmap = al_create_bitmap(w,h);
    if ( bitmap == NULL ) {
        luaL_error ( _l, "Failed to create texture" );
    }

    //
    lua_pushlightuserdata ( _l, bitmap );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_texture_destroy ( lua_State *_l ) {
    ALLEGRO_BITMAP *bitmap;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    bitmap = lua_touserdata(_l,1);

    //
    al_destroy_bitmap(bitmap);
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_texture_get_width ( lua_State *_l ) {
    ALLEGRO_BITMAP *bitmap;
    int r;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    bitmap = lua_touserdata(_l,1);

    r = al_get_bitmap_width(bitmap);
    lua_pushinteger(_l,r);

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_texture_get_height ( lua_State *_l ) {
    ALLEGRO_BITMAP *bitmap;
    int r;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    bitmap = lua_touserdata(_l,1);

    r = al_get_bitmap_height(bitmap);
    lua_pushinteger(_l,r);

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_texture_lock_rect ( lua_State *_l ) {
    ALLEGRO_BITMAP *bitmap;

    ex_lua_check_nargs(_l,5);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    bitmap = lua_touserdata(_l,1);

    al_lock_bitmap_region ( bitmap,
                            luaL_checkint(_l,2),
                            luaL_checkint(_l,3),
                            luaL_checkint(_l,4),
                            luaL_checkint(_l,5),
                            ALLEGRO_PIXEL_FORMAT_ANY,
                            ALLEGRO_LOCK_WRITEONLY );

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_texture_unlock ( lua_State *_l ) {
    ALLEGRO_BITMAP *bitmap;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    bitmap = lua_touserdata(_l,1);

    al_unlock_bitmap ( bitmap );

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_texture_set_pixel ( lua_State *_l ) {
    ALLEGRO_BITMAP *bitmap;
    ALLEGRO_COLOR color;

    ex_lua_check_nargs(_l,7);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    bitmap = lua_touserdata(_l,1);

    // convert color
    color = al_map_rgba_f ( (float)luaL_checknumber(_l,4),
                            (float)luaL_checknumber(_l,5),
                            (float)luaL_checknumber(_l,6),
                            (float)luaL_checknumber(_l,7) );

    al_put_pixel ( luaL_checkint(_l,2),
                   luaL_checkint(_l,3),
                   color );

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "texture_load",       __lua_texture_load },
    { "texture_new",        __lua_texture_new },
    { "texture_destroy",    __lua_texture_destroy },
    { "texture_get_width",  __lua_texture_get_width },
    { "texture_get_height", __lua_texture_get_height },
    { "texture_lock_rect",  __lua_texture_lock_rect },
    { "texture_unlock",     __lua_texture_unlock },
    { "texture_set_pixel",  __lua_texture_set_pixel },
    { NULL, NULL }
};

int __ex_lua_add_texture ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );
    return 0;
}
