// ======================================================================================
// File         : font.c
// Author       : Wu Jie 
// Last Change  : 04/08/2013 | 16:25:21 PM | Monday,April
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

// freetype
#include <ft2build.h>
#include FT_FREETYPE_H

///////////////////////////////////////////////////////////////////////////////
// statics
///////////////////////////////////////////////////////////////////////////////

static bool __initialized = false;
static FT_Library __ft_lib;
static size_t __HRES = 64;

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_font_init () {
    FT_Error error;

    ex_assert ( __initialized == false );

    if ( __initialized )
        return -1;

    ex_log ( "[FreeType] Initializing library..." );
    error = FT_Init_FreeType( &__ft_lib );
    if ( error ) {
        ex_log ( "[FreeType] Error Code: 0x%02x, Message: %s",
                 FT_Errors[error].code, 
                 FT_Errors[error].message );
        return -1;
    }

    __initialized = true;
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_font_deinit () {
    ex_assert ( __initialized );

    if ( __initialized == false )
        return;

    FT_Done_FreeType(__ft_lib);

    __initialized = false;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_font_initialized () { 
    return __initialized; 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ex_font_t *ex_font_load ( const char *_filepath, int _size ) {
    ex_font_t *font;

    FT_Face face;
    FT_Error error;

    ex_file_t *file;
    size_t buf_size;
    void *buffer;

    // open the file
    file = ex_fsys_fopen_r(_filepath);
    if ( file == NULL ) {
        ex_log ( "[FreeType] Can't find the file %s", _filepath );
        return NULL;
    }

    // get the file to the buffer we allocated.
    buf_size = ex_fsys_fsize (file);
    buffer = ex_malloc (buf_size);
    ex_fsys_fread (file, buffer, buf_size );
    ex_fsys_fclose(file);

    //
    error = FT_New_Memory_Face( __ft_lib,
                                buffer,    /* first byte in memory */
                                buf_size,  /* size in bytes        */
                                0,         /* face_index           */
                                &face );
    if ( error ) {
        ex_log ( "[FreeType] Error Code: 0x%02x, Message: %s",
                 FT_Errors[error].code, 
                 FT_Errors[error].message );
        return NULL;
    }

    //
    error = FT_Set_Char_Size( face, _size*64, 0, 72 * __HRES, 72 );
    if ( error ) {
        ex_log ( "[FreeType] Error Code: 0x%02x, Message: %s",
                 FT_Errors[error].code, 
                 FT_Errors[error].message );
        FT_Done_Face( face );
        return NULL;
    }

    //
    ex_free(buffer);

    //
    font = (ex_font_t *)ex_malloc ( sizeof(ex_font_t) );
    font->size = _size;
    font->face = face;

    return font;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_font_destroy ( ex_font_t *_font ) {
    FT_Done_Face( _font->face );
    ex_free(_font);
}
