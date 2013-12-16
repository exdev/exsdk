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

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int __wiz_load_xml ( lua_State *_l, const char *_filepath ) {
    ex_file_t *file;
    size_t buf_size;
    void *buffer;

    file = ex_os_fopen( _filepath, "rb" );
    if ( file == NULL ) {
        ex_log ( "[wiz] Can't find the file %s", _filepath );
        return 1;
    }

    // get the file to the buffer we allocated.
    buf_size = ex_os_fsize(file);
    buffer = ex_malloc (buf_size);
    ex_os_fread (file, buffer, buf_size);
    ex_os_fclose(file);


    ex_free(buffer);

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 


