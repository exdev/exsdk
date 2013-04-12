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

#undef __FTERRORS_H__
#define FT_ERRORDEF( e, v, s )  { e, s },
#define FT_ERROR_START_LIST     {
#define FT_ERROR_END_LIST       { 0, 0 } };
const struct {
    int          code;
    const char  *message;
} FT_Errors[] =
#include FT_ERRORS_H

typedef struct __glyph_key_t {
    int size;
    int outline_type;
    int outline_thickness;
} __glyph_key_t;

typedef struct __glyph_set_t {
    ex_hashmap_t glyphs; // char_code -> ex_glyph_t
    ex_array_t pages; // bitmap page
} __glyph_set_t;

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static uint32 __hashkey ( const void *_key ) {
    __glyph_key_t *key = (__glyph_key_t *)_key;
    return key->size << 16 | key->outline_type << 8 | key->outline_thickness;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __keycmp ( const void *_key1, const void *_key2 ) {
    __glyph_key_t *key1 = (__glyph_key_t *)_key1;
    __glyph_key_t *key2 = (__glyph_key_t *)_key2;

    return (key1->size == key2->size) 
        && (key1->outline_type == key2->outline_type)
        && (key1->outline_thickness == key2->outline_thickness);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// __cache_glyph ( data, ft_index );

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
    font->face = face;
    font->size = _size;
    font->outline_type = 0;
    font->outline_thickness = 1;
    ex_hashmap_init ( &font->glyph_sets,
                      sizeof(__glyph_key_t),
                      sizeof(__glyph_set_t),
                      8,
                      __hashkey,
                      __keycmp );

    return font;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_font_destroy ( ex_font_t *_font ) {
    FT_Done_Face( _font->face );
    ex_free(_font);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_font_set_size ( ex_font_t *_font, int _size ) {
    FT_Error error;

    if ( _font->size == _size )
        return;

    error = FT_Set_Char_Size( _font->face, _size*64, 0, 72 * __HRES, 72 );
    if ( error ) {
        ex_log ( "[FreeType] Error Code: 0x%02x, Message: %s",
                 FT_Errors[error].code, 
                 FT_Errors[error].message );
        return;
    }

    _font->size = _size;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_font_get_kerning ( ex_font_t *_font, int _first, int _second ) {
   if ( _first != -1 ) {
      FT_Vector delta;
      FT_Get_Kerning( _font->face, _first, _second, FT_KERNING_DEFAULT, &delta );
      return delta.x >> 6;
   }

   return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ex_glyph_t *ex_get_glyph ( ex_font_t *_font, int _ft_index ) {
    return NULL;
}