// ======================================================================================
// File         : lua_global.cpp
// Author       : Wu Jie 
// Last Change  : 08/29/2010 | 17:11:50 PM | Sunday,August
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
// quick reference
///////////////////////////////////////////////////////////////////////////////

/**

-------------------------------------------
The index of the stack:
-------------------------------------------

 Top <--- current
        | el(n)     | idx: -1
        | el(n-1)   | idx: -2
        | el(n-2)   | idx: -3
        | ......... | ...
        | ......... | ...
        | ......... | ...
        | el(2)     | idx: 2
 Bottom | el(1)     | idx: 1

 #define lua_pop(L,n) lua_settop(L, -(n) - 1)
 so lua_pop(L,1) means lua_settop(L,-2) which will set current to -2 ( aka pop the -1 ) 

-------------------------------------------
Example:
-------------------------------------------

 int main (void) {
     lua_State *L = luaL_newstate();

                                 // bottome <----------------------------> top
                                 //  1   | 2  | 3    | 4       | 5    | 6   |
                                 // -----+----+------+---------+------+-----|
     lua_pushboolean(L, 1);      // true |    |      |         |      |     |                    
     lua_pushnumber(L, 10);      // true | 10 |      |         |      |     |      
     lua_pushnil(L);             // true | 10 | nil  |         |      |     |         
     lua_pushstring(L, "hello"); // true | 10 | nil  | 'hello' |      |     |            
     lua_pushvalue(L, -4);       // true | 10 | nil  | 'hello' | true |     |           
     lua_replace(L, 3);          // true | 10 | true | 'hello' |      |     |              
     lua_settop(L, 6);           // true | 10 | true | 'hello' | nil  | nil |           
     lua_remove(L, -3);          // true | 10 | true |  nil    | nil  |     |            
     lua_settop(L, -5);          // true |    |      |         |      |     |          
                                 // -----+----+------+---------+------+-----+
     lua_close(L); 

     return 0;
 }

-------------------------------------------
API examplaint:
-------------------------------------------

Here we list all functions and types from the C API in alphabetical order. 
Each function has an indicator like this:

 [-o, +p, x]

The first field, o, is how many elements the function pops from the stack. 

The second field, p, is how many elements the function pushes onto the stack. 
(Any function always pushes its results after popping its arguments.) 
A field in the form x|y means the function can push (or pop) x or y elements, 
depending on the situation; an interrogation mark '?' means that we cannot know 
how many elements the function pops/pushes by looking only at its arguments 
(e.g., they may depend on what is on the stack). 

The third field, x, tells whether the function may throw errors: 
'-' means the function never throws any error; 
'm' means the function may throw an error only due to not enough memory; 
'e' means the function may throw other kinds of errors; 
'v' means the function may throw an error on purpose

 */

///////////////////////////////////////////////////////////////////////////////
// internal defines
///////////////////////////////////////////////////////////////////////////////

#define BUF_SIZE 1024

static lua_State *__L = NULL;
static bool __initialized = false;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int __lua_index ( lua_State *_l, int _idx ) {
    if ( _idx > 0 ) {
        return _idx;
    }
    else if ( _idx > LUA_REGISTRYINDEX ) {
        return lua_gettop(_l) + _idx + 1;
    }
    else {
        return _idx;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// TODO { 
// extern int luaopen_ex ( lua_State * );
// extern int luaopen_angf ( lua_State * );
// extern int luaopen_vec2f ( lua_State * );
// extern int luaopen_mat33f ( lua_State * );
// extern int luaopen_color3f ( lua_State * );
// extern int luaopen_color4f ( lua_State * );
// } TODO end 

#if ( EX_PLATFORM != EX_IOS )
extern int luaopen_luagl ( lua_State * );
extern int luaopen_luaglu ( lua_State * );
#endif
// ------------------------------------------------------------------ 

int ex_lua_init () {

    // the lua-interpreter already initialized.
    if ( __initialized ) {
        return 1;
    }

    // the lua status already opened.
    ex_assert( __L == NULL );

    //
    __L = luaL_newstate();
    luaL_openlibs(__L); // open default libs

    // OPTME { 
    // clear the package.path and package.cpath
    ex_lua_dostring ( __L, "package.path = \"\"" );
    ex_lua_dostring ( __L, "package.cpath = \"\"" );

    // NOTE: we don't need any search path. 
    // in exsdk, require("module") is deprecated all script load as module.
    // clear the package.path and package.cpath
    ex_lua_dostring ( __L, "package.path = \"./?.lua\"" );
    ex_lua_dostring ( __L, "package.cpath = \"./?.so;./?.dll\"" );
    {
        char **mounts = ex_fsys_mounts();
        char **i;
        for ( i = mounts; *i != NULL; ++i  ) {
            ex_lua_add_path( __L, *i );
            ex_lua_add_cpath( __L, *i );
        }
        ex_fsys_free_list(mounts);
    }
    // } OPTME end 

    // init graphics wraps
#if ( EX_PLATFORM != EX_IOS )
    lua_settop ( __L, 0 ); // clear the stack
    luaopen_luagl (__L);
    luaopen_luaglu (__L);
#endif

    // TODO:
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_lua_deinit () {
    if ( __initialized ) {
        // before close modules, force a complete garbage collection in case of memory leak
        lua_gc(__L, LUA_GCCOLLECT, 0);

        // TODO:

        lua_close(__L);
        __L = NULL;
        __initialized = false;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_lua_initialized () { 
    return __initialized;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

lua_State *ex_lua_main_state () { return __L; }

///////////////////////////////////////////////////////////////////////////////
// lua interpreter op
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_lua_dofile ( lua_State *_l, const char *_filepath, const char *_modname ) {
// TODO { 
//     int status;
//     ex_file_t *file;
//     size_t buf_size;
//     void *buffer;

//     // open the file
//     file = ex_fopen_r(_filepath);
//     if ( file == NULL ) {
//         ex_error ( "can't find the file %s", _filepath );
//         return -1;
//     }

//     // get the file to the buffer we allocated.
//     buf_size = ex_fsize (file);
//     buffer = ex_malloc (buf_size);
//     ex_fread (file, buffer, buf_size );
//     ex_fclose(file);

//     // parse the buffer by lua interpreter
//     status = luaL_loadbuffer( _l, (const char *)buffer, buf_size, _filepath );
//     if ( status ) {
//         ex_lua_alert(_l);
//         goto PARSE_FAILED;
//     }

//     // call the script 
//     if ( _modname ) {
//         lua_pushstring(_l,_modname);
//         status = lua_pcall(_l, 1, LUA_MULTRET, 0);
//     }
//     else {
//         status = lua_pcall(_l, 0, LUA_MULTRET, 0);
//     }
//     if ( status ) {
//         ex_lua_alert(_l);
//         goto PARSE_FAILED;
//     }

// PARSE_FAILED:
//     ex_free(buffer);
//     return -1;
// } TODO end 

    return -1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_lua_dostring ( lua_State *_l, const char *_fmt, ... ) {
    int result = -1;
    int status;
    char buf[BUF_SIZE];
    char *buffer = NULL;

    EX_GET_VA_STRING_WITH_RESULT( buf, BUF_SIZE-1, _fmt, &result ); // NOTE: the buffer_count-1 will leave 1 character for null terminal
    buffer = buf;
    if ( result == -1 ) {
        char *dyn_buf = NULL;
        int buffer_count = BUF_SIZE * 2;

        // keep get va string until success 
        do {
            dyn_buf = (char *)ex_realloc_nomng( dyn_buf, buffer_count * sizeof(char) );
            EX_GET_VA_STRING_WITH_RESULT( dyn_buf, buffer_count-1, _fmt, &result ); // NOTE: the buffer_count-1 will leave 1 character for null terminal
            buffer_count *= 2;
        } while ( result == -1 );
        buffer = dyn_buf;
    }
    buffer[result] = '\0';

    // do lua script!
    status = luaL_dostring(_l, buffer);

    // if we use dynamic buffer, free it
    if ( buffer != buf )
        ex_free_nomng ( buffer );

    // check the result.
    if ( status ) {
        ex_lua_alert(_l);
        return -1;
    }
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
// lua debug op
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_lua_alert ( lua_State *_l ) {
    lua_getglobal(_l, "_ALERT");
    if ( lua_isfunction(_l, -1) ) {
        lua_insert(_l, -2);
        lua_call(_l, 1, 0);
    }
    else {  /* no _ALERT function; print it on stderr */
        // luaL_error( _l, "%s\n", lua_tostring(_l, -2) ); // don't do this in unprotected scene
        ex_log( "Lua Error: %s\n", lua_tostring(_l, -2) );
        lua_pop(_l, 2);  /* remove error message and _ALERT */
    }
}

// ------------------------------------------------------------------ 
// Desc:
// ------------------------------------------------------------------ 

void ex_lua_dump_stack ( lua_State *_l ) {
    int i;
    int top = lua_gettop(_l);
    ex_log("dump lua stack:");
    ex_log("+_________");
    ex_log("|-> TOP");
    for ( i = top; i >= 0; --i ) {
        int t = lua_type(_l, i);
        switch (t) {
        case LUA_TSTRING: 
            ex_log("| %d: '%s'", i, lua_tostring(_l, i));
            break;

        case LUA_TBOOLEAN: 
            ex_log( "| %d: %s", i, lua_toboolean(_l, i) ? "true" : "false");
            break;

        case LUA_TNUMBER: 
            ex_log("| %d: %g", i, lua_tonumber(_l, i));
            break;

            // other type ( userdata, function, table ... )
        default: 
            ex_log("| %d: %s", i, lua_typename(_l, t));
            break;
        }
    }
    ex_log("|__________");
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_lua_totoal_memory ( struct lua_State *_l ) {
    return lua_gc(_l, LUA_GCCOUNT, 0);
}
