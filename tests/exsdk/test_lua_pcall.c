// ======================================================================================
// File         : test_lua_pcall.c
// Author       : Wu Jie 
// Last Change  : 06/09/2013 | 11:06:58 AM | Sunday,June
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

const char *buff = "\
function test_1 () no_func() end\n\
function test_2 ( x, y )\n\
    print(x)\n\
    print(y)\n\
    test_1()\n\
end\n\
my_table = { t = test_2 }\n\
";

static int __traceback ( lua_State *_l ) {
    lua_getglobal ( _l, "debug" );
    lua_getfield ( _l, -1, "traceback" );
    lua_pushvalue ( _l, 1 );
    lua_pushinteger ( _l, 2 );
    lua_call ( _l, 2, 1 );
    return 1;
}

int main (void) {
    int idx = -1;
    int error;
    lua_State *L = luaL_newstate(); /* opens Lua */
    luaL_openlibs(L); /* opens the standard libraries */
    
    lua_pushboolean(L, false);
    
    //
    idx = lua_gettop(L);
    lua_pushcfunction ( L, ex_lua_trace_back );
    error = luaL_loadbuffer ( L, buff, strlen(buff), "my_test" ) || lua_pcall( L, 0, 0, idx+1 );
    if (error) {
        fprintf(stderr, "%s", lua_tostring(L, -1));
        lua_pop(L, 1); /* pop error message from the stack */
    }
    lua_pop(L,1);
    

    //
    lua_pushcfunction ( L, ex_lua_trace_back );
    lua_getglobal( L, "my_table" );
    lua_getfield( L, -1, "t" );
    lua_pushstring( L, "Hello World" );
    lua_pushstring( L, "This is Johnny" );

    // lua_pushcfunction ( L, __traceback );
    // lua_insert ( L, -3-2 ); // -2 - nargs

    error = lua_pcall(L, 2, 0, idx+1);
    if (error) {
        fprintf(stderr, "%s", lua_tostring(L, -1));
        lua_pop(L, 1); /* pop error message from the stack */
    }

    lua_close(L);
    return 0;
}
