// ======================================================================================
// File         : wrap_core.c
// Author       : Wu Jie 
// Last Change  : 02/07/2013 | 15:00:11 PM | Thursday,February
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
// functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// NOTE: don't call ex_lua_dofile here, because ex_lua_dofile will push an error func to trace debug stack.
//       if lua script call ex_c.lua_dofile with this functon, it will recursively push the error func handle and lead to error. 
// ------------------------------------------------------------------ 

static int __lua_dofile ( lua_State *_l ) {
    const char *path;
    int status;
    ex_file_t *file;
    size_t buf_size;
    void *buffer;

    ex_lua_check_nargs(_l,1);
    path = luaL_checkstring(_l,1);

    // open the file
    file = ex_fsys_fopen_r(path);
    if ( file == NULL ) {
        ex_log ( "[lua] Can't find the file %s", path );
        return 1;
    }

    // get the file to the buffer we allocated.
    buf_size = ex_fsys_fsize (file);
    buffer = ex_malloc (buf_size);
    ex_fsys_fread (file, buffer, buf_size );
    ex_fsys_fclose(file);

    // parse the buffer by lua interpreter & call the script
    status = luaL_loadbuffer( _l, (const char *)buffer, buf_size, path ) || lua_pcall ( _l, 0, LUA_MULTRET, 0 );
    if ( status ) {
        // TODO??
        // ex_lua_alert(_l); // I need to Test this!!! write something wrong in a lua file and use ex_c.lua_dofile call him
        return -1;
    }
    ex_free(buffer);

    return lua_gettop(_l) - 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static const luaL_Reg lib[] = {
    { "lua_dump_stack",     ex_lua_dump_stack },
    { "lua_total_memory",   ex_lua_totoal_memory },
    { "lua_dofile",         __lua_dofile },
    { NULL, NULL }
};

int __ex_lua_add_core ( lua_State *_l ) {
    luaL_setfuncs( _l, lib, 0 );

    // ex_c.null = NULL
    lua_pushlightuserdata ( _l, NULL );
    lua_setfield( _l, -2, "null" );

    // ex_c.invalid_handle = -1
    lua_pushinteger ( _l, (size_t)-1 );
    lua_setfield( _l, -2, "invalid_handle" );

    return 0;
}
