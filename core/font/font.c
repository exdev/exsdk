// ======================================================================================
// File         : font.c
// Author       : Wu Jie 
// Last Change  : 04/08/2013 | 16:25:21 PM | Monday,April
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "allegro5/allegro.h"

#include "exsdk.h"

// freetype
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

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
    ex_hashmap_t *glyphs; // char_code -> ex_glyph_t
    ex_array_t *pages; // bitmap page
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

static void __init_glyph ( ex_font_t *_font, __glyph_set_t *_glyph_set, ex_glyph_t *_glyph, int _ft_index ) {
    FT_Int32 flags;
    FT_Error error;
    FT_Face face;
    FT_Bitmap ft_bitmap;

    int ft_bitmap_width = 0;
    int ft_bitmap_rows = 0;
    int ft_bitmap_pitch = 0;
    int ft_glyph_top = 0;
    int ft_glyph_left = 0;

    if ( _glyph->page != NULL || _glyph->x < 0 )
        return;

    face = _font->face;

    flags |= FT_LOAD_FORCE_AUTOHINT;
    if( _font->outline_type > 0 )
        flags |= FT_LOAD_NO_BITMAP;
    else
        flags |= FT_LOAD_RENDER;

    //
    error = FT_Load_Glyph( face, _ft_index, flags );
    if ( error ) {
        ex_log ( "[FreeType] Error Code: 0x%02x, Message: %s",
                 FT_Errors[error].code, 
                 FT_Errors[error].message );
        return;
    }

    //
    if ( _font->outline_type == 0 ) {
        ft_bitmap       = face->glyph->bitmap;
        ft_bitmap_width = face->glyph->bitmap.width;
        ft_bitmap_rows  = face->glyph->bitmap.rows;
        ft_bitmap_pitch = face->glyph->bitmap.pitch;
        ft_glyph_top    = face->glyph->bitmap_top;
        ft_glyph_left   = face->glyph->bitmap_left;
    }
    else {
        FT_Stroker stroker;
        FT_Glyph ft_glyph;
        FT_BitmapGlyph ft_bitmap_glyph;

        error = FT_Stroker_New( __ft_lib, &stroker );
        if ( error ) {
            ex_log ( "[FreeType] Error Code: 0x%02x, Message: %s",
                     FT_Errors[error].code, 
                     FT_Errors[error].message );
            return;
        }

        FT_Stroker_Set( stroker,
                        _font->outline_thickness * __HRES,
                        FT_STROKER_LINECAP_ROUND,
                        FT_STROKER_LINEJOIN_ROUND,
                        0 );
        error = FT_Get_Glyph ( face->glyph, &ft_glyph);
        if ( error ) {
            ex_log ( "[FreeType] Error Code: 0x%02x, Message: %s",
                     FT_Errors[error].code, 
                     FT_Errors[error].message );
            return;
        }

        //
        if( _font->outline_type == 1 )
            error = FT_Glyph_Stroke( &ft_glyph, stroker, 1 );
        else if ( _font->outline_type == 2 )
            error = FT_Glyph_StrokeBorder( &ft_glyph, stroker, 0, 1 );
        else if ( _font->outline_type == 3 )
            error = FT_Glyph_StrokeBorder( &ft_glyph, stroker, 1, 1 );
        if ( error ) {
            ex_log ( "[FreeType] Error Code: 0x%02x, Message: %s",
                     FT_Errors[error].code, 
                     FT_Errors[error].message );
            return;
        }

        //
        error = FT_Glyph_To_Bitmap( &ft_glyph, FT_RENDER_MODE_NORMAL, 0, 1);
        if ( error ) {
            ex_log ( "[FreeType] Error Code: 0x%02x, Message: %s",
                     FT_Errors[error].code, 
                     FT_Errors[error].message );
            return;
        }

        ft_bitmap_glyph = (FT_BitmapGlyph)ft_glyph;
        ft_bitmap       = ft_bitmap_glyph->bitmap;
        ft_bitmap_width = ft_bitmap.width;
        ft_bitmap_rows  = ft_bitmap.rows;
        ft_bitmap_pitch = ft_bitmap.pitch;
        ft_glyph_top    = ft_bitmap_glyph->top;
        ft_glyph_left   = ft_bitmap_glyph->left;
        FT_Stroker_Done(stroker);
    }

    // TODO:
    // __atlas_alloc_region ( _font, )
}

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
    font->glyph_sets = ex_hashmap_alloc ( sizeof(__glyph_key_t),
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
    // free glyph sets
    ex_hashmap_each ( _font->glyph_sets, __glyph_set_t, set )

        // free glyphs
        ex_hashmap_free( set.glyphs );

        // free pages
        ex_array_each ( set.pages,  ALLEGRO_BITMAP *, page )
            al_destroy_bitmap(page);
        ex_array_each_end
        ex_array_free( set.pages );

    ex_hashmap_each_end
    ex_hashmap_free(_font->glyph_sets);

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

ex_glyph_t *ex_font_get_glyph ( ex_font_t *_font, int _ft_index ) {
    __glyph_key_t key;
    __glyph_set_t *set;
    ex_glyph_t *glyph;

    key.size = _font->size;
    key.outline_type = _font->outline_type;
    key.outline_thickness = _font->outline_thickness;

    // get glyph-set
    set = ex_hashmap_get( _font->glyph_sets, &key, NULL ); 
    if ( set == NULL ) {
        size_t idx = -1;
        __glyph_set_t new_set;

        new_set.glyphs = ex_hashmap_alloc ( sizeof(int),
                                            sizeof(ex_glyph_t),
                                            128,
                                            ex_hashkey_int,
                                            ex_keycmp_int
                                          );
        new_set.pages = ex_array_alloc ( sizeof(ALLEGRO_BITMAP *), 8 );

        ex_hashmap_add ( _font->glyph_sets, &key, &new_set, &idx );

        ex_assert ( idx != -1 );
        set = ex_hashmap_get_by_idx ( _font->glyph_sets, idx );
    }

    // get glyph
    glyph = ex_hashmap_get( set->glyphs, &_ft_index, NULL ); 
    if ( glyph == NULL ) {
        size_t idx = -1;
        ex_glyph_t new_glyph;

        new_glyph.page = NULL;
        new_glyph.x = -1;
        new_glyph.y = -1;
        new_glyph.w = -1;
        new_glyph.h = -1;
        new_glyph.offset_x = -1;
        new_glyph.offset_y = -1;
        new_glyph.advance = -1;

        ex_hashmap_add ( set->glyphs, &_ft_index, &new_glyph, &idx );

        ex_assert ( idx != -1 );
        glyph = ex_hashmap_get_by_idx ( set->glyphs, idx );

        // init and cache the glyph data
        __init_glyph ( _font, set, glyph, _ft_index );
    }

    return glyph;
}
