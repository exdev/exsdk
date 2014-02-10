// ======================================================================================
// File         : wrap_font.c
// Author       : Wu Jie 
// Last Change  : 04/09/2013 | 14:00:40 PM | Tuesday,April
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "utf8proc.h"

///////////////////////////////////////////////////////////////////////////////
// functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_font_load ( lua_State *_l ) {
    const char *path;
    ex_font_t *font;

    ex_lua_check_nargs(_l,2);

    path = luaL_checkstring(_l,1);
    font = ex_font_load ( path, luaL_checkint(_l,2) );
    if ( font == NULL ) {
        luaL_error ( _l, "Failed to load font: %s", path );
    }

    //
    lua_pushlightuserdata ( _l, font );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_font_destroy ( lua_State *_l ) {
    ex_font_t *font;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    font = lua_touserdata(_l,1);

    //
    if ( font != NULL )
        ex_font_destroy(font);

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_font_get_height ( lua_State *_l ) {
    ex_font_t *font;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    font = lua_touserdata(_l,1);

    //
    lua_pushinteger( _l, ex_font_get_height (font) );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_font_set_size ( lua_State *_l ) {
    ex_font_t *font;

    ex_lua_check_nargs(_l,2);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    font = lua_touserdata(_l,1);

    //
    ex_font_set_size( font, luaL_checkint(_l,2) );
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_font_get_size ( lua_State *_l ) {
    ex_font_t *font;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    font = lua_touserdata(_l,1);

    //
    lua_pushinteger( _l, font->size );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_font_set_outline_type ( lua_State *_l ) {
    ex_font_t *font;

    ex_lua_check_nargs(_l,2);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    font = lua_touserdata(_l,1);

    //
    font->outline_type = luaL_checkint(_l,2);
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_font_get_outline_type ( lua_State *_l ) {
    ex_font_t *font;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    font = lua_touserdata(_l,1);

    //
    lua_pushinteger( _l, font->outline_type );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_font_set_outline_thickness ( lua_State *_l ) {
    ex_font_t *font;

    ex_lua_check_nargs(_l,2);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    font = lua_touserdata(_l,1);

    //
    font->outline_thickness = (float)luaL_checknumber(_l,2);
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_font_get_outline_thickness ( lua_State *_l ) {
    ex_font_t *font;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    font = lua_touserdata(_l,1);

    //
    lua_pushnumber( _l, font->outline_thickness );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_font_get_family_name ( lua_State *_l ) {
    ex_font_t *font;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    font = lua_touserdata(_l,1);

    //
    lua_pushstring( _l, ex_font_get_family_name (font) );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_font_get_style_name ( lua_State *_l ) {
    ex_font_t *font;

    ex_lua_check_nargs(_l,1);

    luaL_checktype( _l, 1, LUA_TLIGHTUSERDATA );
    font = lua_touserdata(_l,1);

    //
    lua_pushstring( _l, ex_font_get_style_name (font) );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_font_wrap_text ( lua_State *_l ) {
    ex_font_t *font;
    const char *text, *whitespace;
    int maxWidth;

    const char *str;
    int ch;
    uint ft_index, prev_ft_index;
    int cur_x = 0;
    ex_glyph_t *glyph;
    int advance = 0;

    //
    ex_lua_check_nargs(_l,4);

    text = luaL_checkstring(_l,1);
    luaL_checktype( _l, 2, LUA_TLIGHTUSERDATA );
    font = lua_touserdata(_l,2);
    whitespace = luaL_checkstring(_l,3);
    maxWidth = luaL_checkint(_l,4);

    //
    str = text;
    prev_ft_index = -1;
    while ( *str ) {
        str += utf8proc_iterate ((const uint8_t *)str, -1, &ch);
        advance = 0;
        ft_index = ex_font_get_index ( font, ch );

        // TODO { 
        // // if this is \n(10) or \r(13), it will turn to ' ' space
        // if ( ch == 10 || ch == 13 ) {
        //     ft_index = ex_font_get_index ( font, ' ' );
        // }
        // } TODO end 

        glyph = ex_font_get_glyph ( font, ft_index );
        advance += ex_font_get_kerning( font, prev_ft_index, ft_index );
        advance += glyph->advance_x;

        cur_x += advance;
        prev_ft_index = ft_index;
    }

    //
    lua_pushstring(_l, text);
    lua_pushnil(_l);
    lua_pushinteger(_l,cur_x);
    return 3; // text1, text2(can be nil), width
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "font_load",                      __lua_font_load },
    { "font_destroy",                   __lua_font_destroy },
    { "font_get_height",                __lua_font_get_height },
    { "font_set_size",                  __lua_font_set_size },
    { "font_get_size",                  __lua_font_get_size },
    { "font_set_outline_type",          __lua_font_set_outline_type },
    { "font_get_outline_type",          __lua_font_get_outline_type },
    { "font_set_outline_thickness",     __lua_font_set_outline_thickness },
    { "font_get_outline_thickness",     __lua_font_get_outline_thickness },
    { "font_get_family_name",           __lua_font_get_family_name },
    { "font_get_style_name",            __lua_font_get_style_name },
    { "font_wrap_text",                 __lua_font_wrap_text },
    { NULL, NULL }
};

int __ex_lua_add_font ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );
    return 0;
}
