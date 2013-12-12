// ======================================================================================
// File         : wrap_base.c
// Author       : Wu Jie 
// Last Change  : 02/18/2013 | 15:19:11 PM | Monday,February
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: string.ncmp ( _self, _compare, _index, _count ) 
// ------------------------------------------------------------------ 

static int __lua_string_ncmp ( lua_State *_l ) {
    const char *str1, *str2;
    size_t idx, cnt;

    ex_lua_check_nargs(_l,4);

    str1 = luaL_checkstring(_l,1);
    str2 = luaL_checkstring(_l,2);
    idx = luaL_checkint(_l,3);
    cnt = luaL_checkint(_l,4);

    if ( (idx + cnt) > strlen(str1) ) {
        lua_pushboolean( _l, false );
        return 1;
    }

    lua_pushboolean( _l, strncmp ( str1+idx, str2, cnt ) == 0 );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg string_lib[] = {
    { "ncmp",     __lua_string_ncmp },
    { NULL, NULL }
};

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_os_getcwd ( lua_State *_l ) {
    lua_pushstring( _l, ex_os_getcwd() );
    return 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg os_lib[] = {
    { "getcwd",     __lua_os_getcwd },
    { NULL, NULL }
};
#if ( EX_PLATFORM == EX_WIN32 )
    static const char *__platform_name = "windows";
#elif ( EX_PLATFORM == EX_LINUX )
    static const char *__platform_name = "linux";
#elif ( EX_PLATFORM == EX_MACOSX )
    static const char *__platform_name = "macosx";
#elif ( EX_PLATFORM == EX_XENON )
    static const char *__platform_name = "xbox360";
#elif ( EX_PLATFORM == EX_PS3 )
    static const char *__platform_name = "ps3";
#elif ( EX_PLATFORM == EX_IOS )
    static const char *__platform_name = "ios";
#elif ( EX_PLATFORM == EX_ANDROID )
    static const char *__platform_name = "android";
#endif

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

int __ex_lua_add_base ( lua_State *_l ) {
    // ======================================================== 
    // string
    // ======================================================== 

    lua_getglobal(_l,"string");
    luaL_setfuncs( _l, string_lib, 0 );
    lua_pop(_l,1); // pop string

    // ======================================================== 
    // os
    // ======================================================== 

    lua_getglobal(_l,"os");
    luaL_setfuncs( _l, os_lib, 0 );

    // os.platform = "..."
    lua_pushstring ( _l, __platform_name );
    lua_setfield( _l, -2, "platform" );
    lua_pop(_l,1); // pop os

    return 0;
}
