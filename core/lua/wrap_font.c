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
// http://www.w3schools.com/cssref/pr_text_white-space.asp
// http://baike.baidu.com/view/40801.htm
// http://www.ipmtea.net/javascript/201009/23_294.html
// static bool IsChineseCharacter(char ch) {
//     return  '\u2E80' <= ch && 
//         (
//          ('\u4E00' <= ch && ch <= '\u9FBF') ||
//          ('\u2E80' <= ch && ch <= '\u2EFF') ||
//          ('\u2F00' <= ch && ch <= '\u2FDF') ||
//          //('\u3000' <= ch && ch <= '\u303F') || CJK 符号和标点 
//          ('\u31C0' <= ch && ch <= '\u31EF') ||
//          ('\u3200' <= ch && ch <= '\u32FF') ||
//          ('\u3300' <= ch && ch <= '\u33FF') ||
//          ('\u3400' <= ch && ch <= '\u4DBF') ||
//          ('\u4DC0' <= ch && ch <= '\u4DFF') ||
//          ('\u4E00' <= ch && ch <= '\u9FBF') ||
//          ('\uF900' <= ch && ch <= '\uFAFF') 
//         )
// // }
// ------------------------------------------------------------------ 

static int __lua_font_wrap_text ( lua_State *_l ) {
    ex_font_t *font;
    const char *text, *whitespace;
    int maxWidth;

    const char *str, *laststr, *nextstr, *pword;
    char *newtext, *newtext_p, *last_newtext;
    int ch, next_ch, len, newlen;
    uint ft_index, prev_ft_index;
    int cur_x, last_x, word_x, advance;
    ex_glyph_t *glyph;
    bool linebreak, beginningOfLine, trimWhitespace; 
    bool wrapword, collapseSpace, collapseLinebreak;

    // get lua arguments
    ex_lua_check_nargs(_l,5);
    text = luaL_checkstring(_l,1);
    luaL_checktype( _l, 2, LUA_TLIGHTUSERDATA );
    font = lua_touserdata(_l,2);
    whitespace = luaL_checkstring(_l,3);
    maxWidth = luaL_checkint(_l,4);
    trimWhitespace = beginningOfLine = (luaL_checkint(_l,5) == 1);

    //
    len = strlen(text);
    str = laststr = nextstr = pword = text;
    newtext_p = newtext = last_newtext = ex_malloc( len * sizeof(char) );
    prev_ft_index = -1;

    // get wrapMode
    wrapword = false;
    collapseSpace = collapseLinebreak = false;
    if ( !strncmp( whitespace, "pre-wrap", 8 ) ) {
        wrapword = true;
        collapseSpace = false;
        collapseLinebreak = false;
    }
    else if ( !strncmp( whitespace, "pre-line", 8 ) ) {
        wrapword = true;
        collapseSpace = true;
        collapseLinebreak = false;
    }
    else if ( !strncmp( whitespace, "normal", 6 ) ) {
        wrapword = true;
        collapseSpace = true;
        collapseLinebreak = true;
    }
    else if ( !strncmp( whitespace, "nowrap", 6 ) ) {
        wrapword = false;
        collapseSpace = true;
        collapseLinebreak = true;
    }
    else if ( !strncmp( whitespace, "pre", 3 ) ) {
        wrapword = false;
        collapseSpace = false;
        collapseLinebreak = false;
    }

    // process text
    cur_x = word_x = 0;
    linebreak = false;
    while ( *str ) {
        nextstr += utf8proc_iterate ((const uint8_t *)str, -1, &ch);

        // if this is line-break
        if ( ch == '\n' || ch == '\r' ) {
            if ( collapseLinebreak ) {
                ch = ' '; // turn it to space
            }
            else {
                linebreak = true;
            }
        }

        // if this is space 
        if ( ch == ' ' || ch == '\t' || ch == '\f' ) {
            if ( collapseSpace ) {
                const char * nextnextstr = nextstr;
                while ( *nextstr ) {
                    nextstr = nextnextstr;
                    nextnextstr += utf8proc_iterate ((const uint8_t *)nextstr, -1, &next_ch);

                    // if next_ch is white-space, then collapse this char
                    if ( next_ch == ' ' || next_ch == '\t' || next_ch == '\f' ) {
                        str = nextstr;
                        continue;
                    }

                    // if next_ch is line-break and collapseLinebreak is true, then collapse this char
                    if ( next_ch == '\n' || next_ch == '\r' ) {
                        if ( collapseLinebreak ) {
                            str = nextstr;
                            continue;
                        }
                    }

                    //
                    break;
                }

                // skip first-time collapse
                if ( trimWhitespace ) {
                    trimWhitespace = false;
                    str = nextstr;
                    continue;
                }

                // yes, must turn it to space to make sure only one space
                ch = ' ';
            }
        }

        //
        trimWhitespace = false;

        // process word-break, word-wrap
        if ( wrapword ) {
            pword = str;
            word_x = cur_x;

            next_ch = ch;
            const char * nextnextstr = nextstr;
            while (1) {
                bool canbreak = false;

                // if this character can break
                if ( next_ch == ' ' || next_ch == '\t' || next_ch == '\f' || next_ch == '\n' || next_ch == '\r' ) {
                    pword = nextstr;
                    word_x = cur_x;

                    beginningOfLine = false;
                    canbreak = true;
                }

                // advanced character
                advance = 0;
                ft_index = ex_font_get_index ( font, next_ch );
                glyph = ex_font_get_glyph ( font, ft_index );
                advance += ex_font_get_kerning( font, prev_ft_index, ft_index );
                advance += glyph->advance_x;
                cur_x += advance;
                prev_ft_index = ft_index;

                //
                if ( canbreak ) {
                    if ( cur_x > maxWidth ) {
                        if ( !beginningOfLine ) {
                            linebreak = true;

                            nextstr = pword;
                            cur_x = word_x;
                        }
                    }
                    break;
                }

                //
                nextstr = nextnextstr;
                nextnextstr += utf8proc_iterate ((const uint8_t *)nextstr, -1, &next_ch);

                //
                if ( *nextnextstr == NULL )
                    break;
            }
        }
        else {
            // advanced character
            advance = 0;
            ft_index = ex_font_get_index ( font, ch );
            glyph = ex_font_get_glyph ( font, ft_index );
            advance += ex_font_get_kerning( font, prev_ft_index, ft_index );
            advance += glyph->advance_x;
            cur_x += advance;
            prev_ft_index = ft_index;
        } 

        // DELME { 
        // TODO: word step, like above, we should step word here. 
        // process last word
        // if ( ch == ' ' || ch == '\t' || ch == '\f' || ch == '\n' || ch == '\r' ) {
        //     beginningOfLine = false;

        //     // ERROR TODO!!! { 
        //     // NOTE: this flag will control to skip current white-space and add it to text2 when word-wrap already happens, 
        //     // if ( needwrap ) {
        //     //     word_x = last_x;
        //     //     pword = laststr;
        //     //     last_newtext = newtext_p;
        //     // }
        //     // else {
        //     //     word_x = cur_x;
        //     //     pword = str;
        //     //     last_newtext = newtext_p + (str-laststr);
        //     // }
        //     // } TODO end 
        //     word_x = last_x;
        //     pword = nextstr;
        //     last_newtext = newtext_p;
        // }
        // } DELME end 

        // copy character to newtext_p
        strncpy( newtext_p, str, nextstr - str );
        newtext_p += (nextstr - str);
        str = nextstr;

        if ( linebreak ) {
            break;
        }
    }

    // text1
    newlen = newtext_p-newtext;
    if ( newlen > 0 ) {
        lua_pushlstring(_l, newtext, newlen);
    }
    else {
        lua_pushnil(_l);
    }

    // text2
    if ( linebreak && *str ) {
        lua_pushstring(_l, str );
    }
    else {
        lua_pushnil(_l);
    }
    lua_pushinteger(_l,cur_x); // width
    lua_pushboolean(_l,linebreak); // line-break

    //
    ex_free(newtext);

    return 4; // text1(can be nil), text2(can be nil), width of text1, linebreak
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
