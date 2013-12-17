// ======================================================================================
// File         : xmlparser.c
// Author       : Wu Jie 
// Last Change  : 12/16/2013 | 11:32:49 AM | Monday,December
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

#include "wiz.h"

#include <expat.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

#define BUF_SIZE 1024

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

typedef struct __user_data_t {
    lua_State *l;
    int refID_on_add_text;
    int refID_on_start_element;
    int refID_on_end_element;
    int refID_on_finish;
} __user_data_t;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void __process_character_data ( void *_userData, const char *_text, int _len ) {
    bool isWhiteSpace = true;
    const char *p = _text; 
    __user_data_t *userData = (__user_data_t *)_userData;
    lua_State *l = userData->l;

    // check if is white-space
    while ( (p - _text) < _len ) {
        if ( isspace(*p) == false ) {
            isWhiteSpace = false;
            break;
        }
        ++p;
    }

    // invoke wiz.parser.onAddText(_text)
    lua_rawgeti( l, LUA_REGISTRYINDEX, userData->refID_on_add_text );
    lua_pushlstring( l, _text, _len );
    lua_pushboolean( l, isWhiteSpace );
    if ( lua_pcall( l, 2, 0, 0 ) ) {
        ex_lua_alert(l);
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void XMLCALL __start_element ( void *_userData, const char *_name, const char **_attrs ) {
    __user_data_t *userData = (__user_data_t *)_userData;

    // for ( i = 0; i < *depthPtr; i++ )
    //     printf("\t");

    printf( "%s: ", _name );
    while ( *_attrs ) {
        printf( "%s ", *_attrs );

        ++_attrs; 
    } 
    printf("\n");
    // *depthPtr += 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void XMLCALL __end_element ( void *_userData, const char *_name ) {
    __user_data_t *userData = (__user_data_t *)_userData;

    // *depthPtr -= 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int __wiz_load_xml ( lua_State *_l, const char *_filepath ) {
    XML_Parser parser;
    ex_file_t *file;
    char buffer[BUF_SIZE];
    int done;
    size_t len;
    __user_data_t userData;

    //
    file = ex_os_fopen( _filepath, "rb" );
    if ( file == NULL ) {
        ex_log ( "[wiz] Can't find the file %s", _filepath );
        return 1;
    }

    // init userData
    userData.l = _l;
    lua_getglobal( _l, "wiz" );
    lua_getfield( _l, -1, "parser" );

    lua_getfield( _l, -1, "onAddText" );
    userData.refID_on_add_text = luaL_ref( _l, LUA_REGISTRYINDEX );

    lua_getfield( _l, -1, "onStartElement" );
    userData.refID_on_start_element = luaL_ref( _l, LUA_REGISTRYINDEX );

    lua_getfield( _l, -1, "onEndElement" );
    userData.refID_on_end_element = luaL_ref( _l, LUA_REGISTRYINDEX );

    lua_getfield( _l, -1, "onFinish" );
    userData.refID_on_finish = luaL_ref( _l, LUA_REGISTRYINDEX );

        // create xml parser 
        parser = XML_ParserCreate(NULL);
        XML_SetUserData(parser, &userData);
        XML_SetElementHandler ( parser, __start_element, __end_element );
        XML_SetCharacterDataHandler ( parser, __process_character_data );

        // begin parse strimming xml 
        do {
            len = ex_os_fread (file, buffer, BUF_SIZE);
            done = len < sizeof(buffer);
            if ( XML_Parse(parser, buffer, len, done) == XML_STATUS_ERROR ) {
                ex_log( "[wiz] %s at line %d", 
                        XML_ErrorString(XML_GetErrorCode(parser)),
                        XML_GetCurrentLineNumber(parser) );
                return 1;
            }
        } while (!done);

        XML_ParserFree(parser);
        ex_os_fclose(file);

        // invoke wiz.parser.onFinish()
        lua_rawgeti( _l, LUA_REGISTRYINDEX, userData.refID_on_finish );
        if ( lua_pcall( _l, 0, 0, 0 ) ) {
            ex_lua_alert(_l);
        }

    // deinit userData
    luaL_unref( _l, LUA_REGISTRYINDEX, userData.refID_on_add_text );
    luaL_unref( _l, LUA_REGISTRYINDEX, userData.refID_on_start_element );
    luaL_unref( _l, LUA_REGISTRYINDEX, userData.refID_on_end_element );
    luaL_unref( _l, LUA_REGISTRYINDEX, userData.refID_on_finish );
    lua_pop(_l,2); // pop wiz.parser

    return 0;
}

