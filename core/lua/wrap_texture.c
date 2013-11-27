// ======================================================================================
// File         : wrap_texture.c
// Author       : Wu Jie 
// Last Change  : 02/19/2013 | 15:10:22 PM | Tuesday,February
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "SDL.h"
#include "SDL_image.h"

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
    SDL_Texture *sdl_texture;
    SDL_Surface *bitmap;

    ex_lua_check_nargs(_l,1);

    path = luaL_checkstring(_l,1);
    bitmap = IMG_Load(path);
    if ( bitmap == NULL ) {
        luaL_error ( _l, "Failed to load image: %s", path );
    }
    sdl_texture = SDL_CreateTextureFromSurface( ex_get_main_sdl_renderer(),
                                                bitmap );
    if ( sdl_texture == NULL ) {
        luaL_error ( _l, "Failed to create texture from: %s", path );
    }

    //
    lua_pushlightuserdata ( _l, sdl_texture );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_texture_new ( lua_State *_l ) {
    int w,h;
    SDL_Texture *sdl_texture;

    ex_lua_check_nargs(_l,2);

    w = luaL_checkint(_l,1);
    h = luaL_checkint(_l,2);

    sdl_texture = SDL_CreateTexture( ex_get_main_sdl_renderer(),
                                     SDL_PIXELFORMAT_ARGB8888,
                                     SDL_TEXTUREACCESS_STREAMING,
                                     w, h );
    if ( sdl_texture == NULL ) {
        luaL_error ( _l, "Failed to create texture" );
    }

    //
    lua_pushlightuserdata ( _l, sdl_texture );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_texture_destroy ( lua_State *_l ) {
    SDL_Texture *sdl_texture;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    sdl_texture = lua_touserdata(_l,1);

    //
    SDL_DestroyTexture(sdl_texture);
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_texture_get_width ( lua_State *_l ) {
    SDL_Texture *sdl_texture;
    int w;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    sdl_texture = lua_touserdata(_l,1);

    SDL_QueryTexture( sdl_texture, NULL, NULL, &w, NULL );
    lua_pushinteger(_l,w);

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_texture_get_height ( lua_State *_l ) {
    SDL_Texture *sdl_texture;
    int h;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    sdl_texture = lua_touserdata(_l,1);

    SDL_QueryTexture( sdl_texture, NULL, NULL, NULL, &h );
    lua_pushinteger(_l,h);

    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
static SDL_Texture *__locked_texture = NULL;
static void *__locked_pixels = NULL;
static int __locked_pitch = -1;
// ------------------------------------------------------------------ 

static int __lua_texture_lock_rect ( lua_State *_l ) {
    SDL_Rect rect;

    if ( __locked_texture != NULL ) {
        return luaL_error ( _l, "Can't operate different texture at the same time" );
    } 
    ex_lua_check_nargs(_l,5);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    __locked_texture = lua_touserdata(_l,1);

    rect.x = luaL_checkint(_l,2);
    rect.y = luaL_checkint(_l,3);
    rect.w = luaL_checkint(_l,4);
    rect.h = luaL_checkint(_l,5);
    SDL_LockTexture ( __locked_texture,
                      &rect,
                      &__locked_pixels,
                      &__locked_pitch );

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_texture_unlock ( lua_State *_l ) {
    SDL_Texture *sdl_texture;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    sdl_texture = lua_touserdata(_l,1);

    //
    if ( __locked_texture != sdl_texture ) {
        return luaL_error ( _l, "Can't operate different texture at the same time" );
    } 
    SDL_UnlockTexture ( __locked_texture );
    __locked_texture = NULL;

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_texture_set_pixel ( lua_State *_l ) {
    SDL_Texture *sdl_texture;
    ex_vec4f_t color;
    uint32 *dst_pixel;
    int x, y;

    ex_lua_check_nargs(_l,7);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    sdl_texture = lua_touserdata(_l,1);

    if ( __locked_texture != sdl_texture ) {
        return luaL_error ( _l, "Can't operate different texture at the same time" );
    } 

    x = luaL_checkint(_l,2);
    y = luaL_checkint(_l,3);

    // convert color
    ex_color4f_set( &color, 
                    (float)luaL_checknumber(_l,4),
                    (float)luaL_checknumber(_l,5),
                    (float)luaL_checknumber(_l,6),
                    (float)luaL_checknumber(_l,7) );

    dst_pixel = (uint32 *)( (uint8 *)__locked_pixels + y * __locked_pitch + 4 * x );
    *dst_pixel = ex_color4f_to_ARGB (&color);

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
