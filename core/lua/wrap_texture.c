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

static const luaL_Reg lib[] = {
    { "texture_load",       __lua_texture_load },
    { "texture_new",        __lua_texture_new },
    { "texture_destroy",    __lua_texture_destroy },
    { NULL, NULL }
};

int __ex_lua_add_texture ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );
    return 0;
}
