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

#define SHORT_PATH_LEN 30

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
extern int __ex_lua_add_base ( lua_State * );
extern int __ex_lua_add_core ( lua_State * );
extern int __ex_lua_add_fsys ( lua_State * );
extern int __ex_lua_add_array ( lua_State * );
extern int __ex_lua_add_utf8 ( lua_State * );
extern int __ex_lua_add_vec2f ( lua_State * );
extern int __ex_lua_add_vec3f ( lua_State * );
extern int __ex_lua_add_vec4f ( lua_State * );
extern int __ex_lua_add_transform ( lua_State * );
extern int __ex_lua_add_texture ( lua_State * );
extern int __ex_lua_add_font ( lua_State * );
extern int __ex_lua_add_painter ( lua_State * );

static const lua_CFunction loadedlibs[] = {
    __ex_lua_add_base,
    __ex_lua_add_core,
    __ex_lua_add_fsys,
    __ex_lua_add_array,
    __ex_lua_add_utf8,
    __ex_lua_add_vec2f,
    __ex_lua_add_vec3f,
    __ex_lua_add_vec4f,
    __ex_lua_add_transform,
    __ex_lua_add_texture,
    __ex_lua_add_font,
    __ex_lua_add_painter,
    NULL
};
// ------------------------------------------------------------------ 

static void __ex_lua_openlibs ( lua_State *_l ) {
    const lua_CFunction *pfunc;

    // create ex_c table
    lua_newtable(_l);

        // call open functions from 'loadedlibs' and set results to global table
        for ( pfunc = loadedlibs; *pfunc; ++pfunc ) {
            (*pfunc) (_l); // add functions to the table
        }

        ex_lua_add_c_module ( _l, "ex_c" );

    lua_pop(_l, 1);  /* remove module table */
}

// ------------------------------------------------------------------ 
// Desc: 
extern int luaopen_lpeg ( lua_State * );
extern int luaopen_yajl ( lua_State * );
// ------------------------------------------------------------------ 

static void __ex_lua_openlibs_ext ( lua_State *_l ) {
    luaopen_lpeg (_l); // new lpeg table
    ex_lua_add_c_module ( _l, "lpeg" );
    lua_pop(_l, 1);  /* remove module table */

    luaopen_yajl (_l); // new yajl-json table
    ex_lua_add_c_module ( _l, "json" );
    lua_pop(_l, 1);  /* remove module table */
}

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
#if ( EX_PLATFORM != EX_IOS )
extern int luaopen_luagl ( lua_State * );
extern int luaopen_luaglu ( lua_State * );
#endif
extern void __ex_value_type_pool_init ();
// ------------------------------------------------------------------ 

lua_State *ex_lua_init () {
    lua_State *l = NULL;

    // the lua-interpreter already initialized.
    // the lua status already opened.
    ex_assert ( __initialized == false );

    if ( __initialized )
        return NULL;

    //
    l = luaL_newstate();
    __ex_value_type_pool_init ();

    //
    ex_log ( "[lua] Version %0.f", *lua_version(l) );

    // open default lua libs
    ex_log ( "[lua] Loading default modules..." );
    luaL_openlibs(l);
    lua_settop ( l, 0 ); // clear the stack

    // open ex_c libs
    ex_log ( "[lua] Loading ex_c modules..." );
    __ex_lua_openlibs (l);
    lua_settop ( l, 0 ); // clear the stack

    // open lpeg
    ex_log ( "[lua] Loading lpeg modules..." );
    __ex_lua_openlibs_ext (l);
    lua_settop ( l, 0 ); // clear the stack

    // open luagl
#if ( EX_PLATFORM != EX_IOS )
    ex_log ( "[lua] Loading gl modules..." );
    luaopen_luagl (l);
    lua_settop ( l, 0 ); // clear the stack

    luaopen_luaglu (l);
    lua_settop ( l, 0 ); // clear the stack
#endif

    // clear the package.path and package.cpath
    ex_lua_clear_path(l);
    ex_lua_clear_cpath(l);

    // DELME { 
    // ex_lua_add_path( l, "./" );
    // ex_lua_add_cpath( l, "./" );
    // {
    //     char **mounts = ex_fsys_mounts();
    //     char **i;
    //     for ( i = mounts; *i != NULL; ++i  ) {
    //         ex_lua_add_path( l, *i );
    //         ex_lua_add_cpath( l, *i );
    //     }
    //     ex_fsys_free_list(mounts);
    // }
    // } DELME end 

    __initialized = true;
    return l;
}

// ------------------------------------------------------------------ 
// Desc: 
extern void __ex_value_type_pool_deinit ();
// ------------------------------------------------------------------ 

void ex_lua_deinit ( lua_State *_l ) {
    ex_assert ( __initialized );

    if ( __initialized == false )
        return;

    // before close modules, force a complete garbage collection in case of memory leak
    lua_gc(_l, LUA_GCCOLLECT, 0);
    lua_close(_l);

    // 
    __ex_value_type_pool_deinit ();

    _l = NULL;
    __initialized = false;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_lua_initialized () { 
    return __initialized;
}

///////////////////////////////////////////////////////////////////////////////
// lua op
///////////////////////////////////////////////////////////////////////////////

static inline int __lua_set_path ( struct lua_State *_l, const char * _fieldName, const char *_path ) {
    lua_getglobal( _l, "package" );
    lua_pushstring( _l, _path );

    lua_setfield( _l, -2, _fieldName ); // package.${_fieldName} = "\"\"", _fieldName = "path" or "cpath"

    lua_pop( _l, 1 ); // get rid of package table from top of stack
    return 0;
}
static inline int __lua_add_path ( struct lua_State *_l, const char * _fieldName, const char *_path ) {
    ex_str_t *string;

    lua_getglobal( _l, "package" );
    lua_getfield( _l, -1, _fieldName );

    string = ex_str_alloc(lua_tostring( _l, -1 )); // grab path string from top of stack
    ex_str_catf( string, ";%s", _path );

    lua_pop( _l, 1 ); // get rid of the string on the stack we just pushed on line 5
    lua_pushstring( _l, ex_cstr(string) ); // push the new one
    lua_setfield( _l, -2, _fieldName ); // set the field "path" in table at -2 with value at top of stack
    lua_pop( _l, 1 ); // get rid of package table from top of stack

    ex_str_free(string);

    return 0;
}
// TODO: add ex_str_new() functions for easy create strop { 
// static inline int __lua_add_path ( struct lua_State *_l, const char * _fieldName, const char *_path ) {
//     char *new_path;
//     const char *original_path;
//     size_t original_path_len;
//     size_t path_len;

//     lua_getglobal( _l, "package" );
//     lua_getfield( _l, -1, _fieldName );

//     original_path = lua_tostring( _l, -1 ); // grab path string from top of stack
//     original_path_len = strlen(original_path);
//     path_len = strlen(_path);

//     new_path = ex_malloc( original_path_len + path_len + 1 + 1 );
//     strncat( new_path, ";", 1 );
//     strncat( new_path, _path, path_len );
//     new_path[original_path_len + path_len + 1 + 1] = '\0';

//     lua_pop( _l, 1 ); // get rid of the string on the stack we just pushed on line 5
//     lua_pushstring( _l, new_path ); // push the new one
//     lua_setfield( _l, -2, _fieldName ); // set the field "path" in table at -2 with value at top of stack
//     lua_pop( _l, 1 ); // get rid of package table from top of stack

//     ex_free(new_path);

//     return 0;
// }
// } TODO end 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_lua_clear_path ( struct lua_State *_l ) {
    return __lua_set_path ( _l, "path", "\"\"" );
}
int ex_lua_set_path ( struct lua_State *_l, const char *_path ) {
    ex_str_t *string;
    
    string = ex_str_allocf( "\"%s?.lua\"", ex_unix_path(_path) );

    // "package.path = "\"${_path}?.lua\""
    __lua_set_path ( _l, "path", ex_cstr(string) );

    ex_str_free (string);
    return 0;
}
int ex_lua_add_path ( struct lua_State *_l, const char *_path ) {
    ex_str_t *string;
    
    string = ex_str_allocf( ";\"%s?.lua\"", ex_unix_path(_path) );

    // "package.path = package.path .. \";${_path}?.lua\""
    __lua_add_path ( _l, "path", ex_cstr(string) );

    ex_str_free (string);
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_lua_clear_cpath ( struct lua_State *_l ) {
    return __lua_set_path ( _l, "cpath", "\"\"" );
}
int ex_lua_set_cpath ( struct lua_State *_l, const char *_path ) {
    ex_str_t *string;
    const char *dir_cstr;
    
    dir_cstr = ex_unix_path(_path);
    string = ex_str_allocf ( "\"%s?.so;%s?.dll\"", dir_cstr, dir_cstr );

    // "package.cpath = "\"${_path}?.so;${_path}?.dll\""
    __lua_set_path ( _l, "cpath", ex_cstr(string) );

    ex_str_free (string);
    return 0;
}
int ex_lua_add_cpath ( struct lua_State *_l, const char *_path ) {
    ex_str_t *string;
    const char *dir_cstr;
    
    dir_cstr = ex_unix_path(_path);
    string = ex_str_allocf ( ";\"%s?.so;%s?.dll\"", dir_cstr, dir_cstr );

    // "package.cpath = package.cpath .. \";${_path}?.so;${_path}?.dll\"", 
    __lua_add_path ( _l, "cpath", _path );

    ex_str_free (string);
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_lua_add_c_module ( lua_State *_l, const char *_modname ) {
    luaL_getsubtable(_l, LUA_REGISTRYINDEX, "_LOADED");
    lua_pushvalue(_l, -2);  /* make copy of module (call result) */
    lua_setfield(_l, -2, _modname);  /* _LOADED[modname] = module */
    lua_pop(_l, 1);  /* remove _LOADED table */

    lua_pushvalue(_l, -1);  /* copy of 'mod' */
    lua_setglobal(_l, _modname);  /* _G[modname] = module */
}

///////////////////////////////////////////////////////////////////////////////
// lua interpreter op
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_lua_pcall ( lua_State *_l, int _nargs, int _nresults, int _errfunc ) {
    int status;

    status = lua_pcall ( _l, _nargs, _nresults, _errfunc );
    if ( status ) {
        ex_lua_alert(_l);
        return -1;
    }

    return 0;
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

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_lua_run_interpretor ( lua_State *_l ) {
    char buff[256];
    int error;

    while ( fgets(buff, sizeof(buff), stdin) != NULL ) {
        error = luaL_loadbuffer ( _l, buff, strlen(buff), "line" ) || lua_pcall(_l, 0, 0, 0);
        if ( error ) {
            fprintf(stderr, "%s", lua_tostring(_l, -1));
            lua_pop(_l, 1); /* pop error message from the stack */
        }
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_lua_dofile ( struct lua_State *_l, const char *_filepath ) {
    int status;
    int idx = -1;

    lua_pushcfunction( _l, ex_lua_trace_back );     /* push traceback function */
    idx = lua_gettop(_l);                           /* function index */
    status = ex_lua_dofile_2( _l, _filepath, idx );
    lua_remove(_l, idx);                            /* remove traceback function */

    return status;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_lua_dofile_2 ( lua_State *_l, const char *_filepath, int _idx ) {
    int status;
    ex_file_t *file;
    size_t buf_size;
    void *buffer;

    size_t pathLen = -1;
    char shortPath[SHORT_PATH_LEN];

    // open the file
    file = ex_os_fopen (_filepath, "rb");
    if ( file == NULL ) {
        ex_log ( "[lua] Can't find the file %s", _filepath );
        return 1;
    }

    // get the file to the buffer we allocated.
    buf_size = ex_os_fsize(file);
    buffer = ex_malloc (buf_size);
    ex_os_fread (file, buffer, buf_size);
    ex_os_fclose(file);

    // get short path
    pathLen = strlen(_filepath);
    if ( pathLen > SHORT_PATH_LEN ) {
        strncpy( shortPath + 3, _filepath + pathLen - (SHORT_PATH_LEN-4), SHORT_PATH_LEN-4 );
        strncpy( shortPath, "...", 3 );
        shortPath[SHORT_PATH_LEN-1] = '\0';
    }

    // parse the buffer by lua interpreter & call the script
    status = luaL_loadbuffer( _l, (const char *)buffer, buf_size, shortPath ) || lua_pcall ( _l, 0, LUA_MULTRET, _idx );
    ex_free(buffer);
    if ( status ) {
        ex_lua_alert(_l);
    }

    //
    return status;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_lua_fsys_dofile ( lua_State *_l, const char *_fsys_filepath ) {
    int status;
    int idx = -1;

    lua_pushcfunction( _l, ex_lua_trace_back );     /* push traceback function */
    idx = lua_gettop(_l);                           /* function index */
    status = ex_lua_fsys_dofile_2( _l, _fsys_filepath, idx );
    lua_remove(_l, idx);                            /* remove traceback function */

    return status;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_lua_fsys_dofile_2 ( lua_State *_l, const char *_fsys_filepath, int _idx ) {
    int status;
    ex_file_t *file;
    size_t buf_size;
    void *buffer;

    size_t pathLen = -1;
    char shortPath[SHORT_PATH_LEN];

    // open the file
    file = ex_fsys_fopen_r(_fsys_filepath);
    if ( file == NULL ) {
        ex_log ( "[lua] Can't find the file %s", _fsys_filepath );
        return 1;
    }

    // get the file to the buffer we allocated.
    buf_size = ex_fsys_fsize (file);
    buffer = ex_malloc (buf_size);
    ex_fsys_fread (file, buffer, buf_size );
    ex_fsys_fclose(file);

    // get short path
    pathLen = strlen(_fsys_filepath);
    if ( pathLen > SHORT_PATH_LEN ) {
        strncpy( shortPath + 3, _fsys_filepath + pathLen - (SHORT_PATH_LEN-4), SHORT_PATH_LEN-4 );
        strncpy( shortPath, "...", 3 );
        shortPath[SHORT_PATH_LEN-1] = '\0';
    }

    // parse the buffer by lua interpreter & call the script
    status = luaL_loadbuffer( _l, (const char *)buffer, buf_size, shortPath ) || lua_pcall ( _l, 0, LUA_MULTRET, _idx );
    ex_free(buffer);
    if ( status ) {
        ex_lua_alert(_l);
    }

    //
    return status;
}

///////////////////////////////////////////////////////////////////////////////
// lua debug op
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_lua_trace_back ( lua_State *_l ) {
    lua_getglobal ( _l, "debug" );
    lua_getfield ( _l, -1, "traceback" );
    lua_pushvalue ( _l, 1 );
    lua_pushinteger ( _l, 2 );
    lua_call ( _l, 2, 1 );
    return 1;
}

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
        ex_log( "Lua Error: %s", lua_tostring(_l, -2) );
        lua_pop(_l, 2);  /* remove error message and _ALERT */
    }
}

// ------------------------------------------------------------------ 
// Desc:
// ------------------------------------------------------------------ 

int ex_lua_dump_stack ( lua_State *_l ) {
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

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_lua_totoal_memory ( struct lua_State *_l ) {
    return lua_gc(_l, LUA_GCCOUNT, 0);
}
