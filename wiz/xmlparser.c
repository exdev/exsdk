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

static XML_Parser parser = NULL;

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void __process_character_data ( void *_userData, const char *_text, int _len ) {
    if ( _len > 0 ) {
        // lua_pushlstring( _text, _len );
        char *t = ex_malloc( _len+1 );

        strncpy( t, _text, _len );
        t[_len] = '\0';
        printf( "(%s)", t );

        ex_free(t);
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void XMLCALL __start_element ( void *_userData, const char *_name, const char **_attrs ) {
    int i;
    int *depthPtr = (int *)_userData;

    // for ( i = 0; i < *depthPtr; i++ )
    //     printf("\t");

    printf( "%s: ", _name );
    while ( *_attrs ) {
        printf( "%s ", *_attrs );

        ++_attrs; 
    } 
    printf("\n");
    *depthPtr += 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void XMLCALL __end_element(void *_userData, const char *_name) {
    int *depthPtr = (int *)_userData;
    *depthPtr -= 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int __wiz_load_xml ( lua_State *_l, const char *_filepath ) {
    const size_t BUF_SIZE = 1024;

    ex_file_t *file;
    char buffer[BUF_SIZE];
    int done;
    size_t len;

    int depth = 0;

    file = ex_os_fopen( _filepath, "rb" );
    if ( file == NULL ) {
        ex_log ( "[wiz] Can't find the file %s", _filepath );
        return 1;
    }

    // create xml parser 
    parser = XML_ParserCreate(NULL);
    XML_SetUserData(parser, &depth);
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
    return 0;
}

