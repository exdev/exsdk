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
    float outline_thickness;
} __glyph_key_t;

typedef struct __glyph_set_t {
    ex_hashmap_t *glyphs; // char_code -> ex_glyph_t
    ex_array_t *pages; // bitmap page
    int cur_x;
    int cur_y;
    int max_height;
} __glyph_set_t;

#define FT_CHECK_ERROR_RETURN(error,ret) \
    if ( error ) { \
        ex_log ( "[FreeType] Error Code: 0x%02x, Message: %s", \
                 FT_Errors[error].code,  \
                 FT_Errors[error].message ); \
        ex_assert (0); \
        return ret; \
    }

#define FT_CHECK_ERROR_RETURN_VOID(error) \
    if ( error ) { \
        ex_log ( "[FreeType] Error Code: 0x%02x, Message: %s", \
                 FT_Errors[error].code,  \
                 FT_Errors[error].message ); \
        ex_assert (0); \
    }

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static uint32 __hashkey ( const void *_key ) {
    __glyph_key_t *key = (__glyph_key_t *)_key;
    return key->size << 16 | key->outline_type << 8 | (int)(key->outline_thickness * 10.0f);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __keycmp ( const void *_key1, const void *_key2 ) {
    __glyph_key_t *key1 = (__glyph_key_t *)_key1;
    __glyph_key_t *key2 = (__glyph_key_t *)_key2;

    if ( key1->size != key2->size ) {
        return key1->size - key2->size; 
    }
    if ( key1->outline_type != key2->outline_type ) {
        return key1->outline_type - key2->outline_type; 
    }
    if ( key1->outline_thickness != key2->outline_thickness ) {
        return ex_signf(key1->outline_thickness - key2->outline_thickness); 
    }
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static ALLEGRO_BITMAP *__new_texture () {
    ALLEGRO_BITMAP *bitmap;
    ALLEGRO_STATE state;

    al_store_state(&state, ALLEGRO_STATE_NEW_BITMAP_PARAMETERS);
        al_set_new_bitmap_format ( ALLEGRO_PIXEL_FORMAT_ABGR_8888 );
        al_set_new_bitmap_flags ( ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR );
        bitmap = al_create_bitmap( 256, 256 );
    al_restore_state(&state);

    al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
        al_hold_bitmap_drawing(false);
        al_set_target_bitmap(bitmap);
        al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));
    al_restore_state(&state);

    // DISABLE { 
    // ALLEGRO_LOCKED_REGION *locked;
    // int x, y, p;
    // unsigned char *rgba;
    // bitmap = al_create_bitmap( 256, 256 );
    // locked = al_lock_bitmap ( bitmap, ALLEGRO_PIXEL_FORMAT_ABGR_8888, ALLEGRO_LOCK_WRITEONLY );
    // rgba = locked->data;
    // p = locked->pitch;
    // for ( y = 0; y < 256; ++y ) {
    //     for ( x = 0; x < 256; ++x ) {
    //         rgba[y * p + x * 4 + 0] = 0;
    //         rgba[y * p + x * 4 + 1] = 0;
    //         rgba[y * p + x * 4 + 2] = 0;
    //         rgba[y * p + x * 4 + 3] = 0;
    //     }
    // }
    // al_unlock_bitmap(bitmap);
    // } DISABLE end 

    return bitmap;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static ALLEGRO_LOCKED_REGION *__atlas_alloc_region ( ex_font_t *_font, __glyph_set_t *_glyph_set, ex_glyph_t *_glyph, int _w, int _h, int _padding ) {
    ALLEGRO_BITMAP *page;
    ALLEGRO_LOCKED_REGION *region;

    //
    if ( _glyph_set->pages->count == 0 ) {
        page = __new_texture();
        ex_array_add ( _glyph_set->pages, &page );

        _glyph_set->cur_x = _padding;
        _glyph_set->cur_y = _padding;
        _glyph_set->max_height = 0;
    }
    else {
        page = *(ALLEGRO_BITMAP **)ex_array_get ( _glyph_set->pages, _glyph_set->pages->count-1 );
    }

    //
    ex_assert ( _w + _padding < al_get_bitmap_width(page) && _h + _padding < al_get_bitmap_height(page) );

    //
    if ( _glyph_set->cur_x + _w + _padding > al_get_bitmap_width(page) ) {
        _glyph_set->cur_y += (_glyph_set->max_height + _padding);
        _glyph_set->cur_x = _padding;
        _glyph_set->max_height = 0;
    }

    //
    if ( _glyph_set->cur_y + _h + _padding > al_get_bitmap_height(page) ) {
        page = __new_texture();
        ex_array_add ( _glyph_set->pages, &page );

        _glyph_set->cur_x = _padding;
        _glyph_set->cur_y = _padding;
        _glyph_set->max_height = 0;
    }

    //
    _glyph->x = _glyph_set->cur_x;
    _glyph->y = _glyph_set->cur_y;
    _glyph->w = _w;
    _glyph->h = _h;

    _glyph_set->cur_x += (_w + _padding);
    if ( _h + _padding > _glyph_set->max_height ) {
        _glyph_set->max_height = _h;
    }

    //
    region = al_lock_bitmap_region( page,
                                    _glyph->x, _glyph->y,
                                    _glyph->w, _glyph->h,
                                    ALLEGRO_PIXEL_FORMAT_ABGR_8888, 
                                    ALLEGRO_LOCK_WRITEONLY );

    return region;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void __copy_glyph_color ( FT_Bitmap _ft_bitmap, ALLEGRO_LOCKED_REGION *_region ) {
    int x, y;

    for ( y = 0; y < _ft_bitmap.rows; ++y ) {
        const uint8 *ptr = _ft_bitmap.buffer + _ft_bitmap.pitch * y;
        uint8 *dptr = (uint8 *)_region->data + _region->pitch * y;

        for ( x = 0; x < _ft_bitmap.width; ++x ) {
            unsigned char c = *ptr;
            *dptr++ = 255;
            *dptr++ = 255;
            *dptr++ = 255;
            *dptr++ = c;
            ptr++;
        }
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void __init_glyph ( ex_font_t *_font, __glyph_set_t *_glyph_set, ex_glyph_t *_glyph, uint _ft_index ) {
    FT_Int32 flags;
    FT_Error error;
    FT_Face face;
    FT_Glyph ft_glyph;
    FT_Bitmap ft_bitmap;
    ALLEGRO_BITMAP *cur_page = NULL;
    ALLEGRO_LOCKED_REGION *region = NULL;

    int ft_bitmap_width = 0;
    int ft_bitmap_rows = 0;
    int ft_bitmap_pitch = 0;
    int ft_glyph_top = 0;
    int ft_glyph_left = 0;

    if ( _glyph->page != NULL )
        return;

    face = _font->face;

    flags = 0;
    flags |= FT_LOAD_FORCE_AUTOHINT;
    if( _font->outline_type > 0 )
        flags |= FT_LOAD_NO_BITMAP;
    else
        flags |= FT_LOAD_RENDER;

    //
    error = FT_Load_Glyph( face, _ft_index, flags );
    FT_CHECK_ERROR_RETURN_VOID (error);

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
        FT_BitmapGlyph ft_bitmap_glyph;

        error = FT_Stroker_New( __ft_lib, &stroker );
        FT_CHECK_ERROR_RETURN_VOID (error);

        FT_Stroker_Set( stroker,
                        (int)(_font->outline_thickness * 64.0f),
                        FT_STROKER_LINECAP_ROUND,
                        FT_STROKER_LINEJOIN_ROUND,
                        0 );
        error = FT_Get_Glyph ( face->glyph, &ft_glyph);
        FT_CHECK_ERROR_RETURN_VOID (error);

        //
        if( _font->outline_type == 1 )
            error = FT_Glyph_Stroke( &ft_glyph, stroker, 1 );
        else if ( _font->outline_type == 2 )
            error = FT_Glyph_StrokeBorder( &ft_glyph, stroker, 0, 1 );
        else if ( _font->outline_type == 3 )
            error = FT_Glyph_StrokeBorder( &ft_glyph, stroker, 1, 1 );
        FT_CHECK_ERROR_RETURN_VOID (error);

        //
        error = FT_Glyph_To_Bitmap( &ft_glyph, FT_RENDER_MODE_NORMAL, 0, 1);
        FT_CHECK_ERROR_RETURN_VOID (error);

        ft_bitmap_glyph = (FT_BitmapGlyph)ft_glyph;
        ft_bitmap       = ft_bitmap_glyph->bitmap;
        ft_bitmap_width = ft_bitmap.width;
        ft_bitmap_rows  = ft_bitmap.rows;
        ft_bitmap_pitch = ft_bitmap.pitch;
        ft_glyph_top    = ft_bitmap_glyph->top;
        ft_glyph_left   = ft_bitmap_glyph->left;
        FT_Stroker_Done(stroker);
    }

    // 
    region = __atlas_alloc_region ( _font, _glyph_set, _glyph, ft_bitmap_width, ft_bitmap_rows, 1 );
    cur_page = *(ALLEGRO_BITMAP **)ex_array_get ( _glyph_set->pages, _glyph_set->pages->count-1 );

    __copy_glyph_color ( ft_bitmap, region );
    al_unlock_bitmap(cur_page);

    //
    _glyph->page = cur_page;
    _glyph->offset_x = ft_glyph_left;
    _glyph->offset_y = (face->size->metrics.ascender >> 6) - ft_glyph_top;

    // Discard hinting to get advance
    FT_Load_Glyph( face, _ft_index, FT_LOAD_RENDER | FT_LOAD_NO_HINTING);

    _glyph->advance_x = face->glyph->advance.x >> 6;
    _glyph->advance_y = face->glyph->advance.y >> 6;

    if ( _font->outline_type > 0 )
        FT_Done_Glyph( ft_glyph );
}

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_font_init () {
    FT_Error error;
    int major,minor,patch;

    ex_assert ( __initialized == false );

    if ( __initialized )
        return -1;

    error = FT_Init_FreeType( &__ft_lib );
    FT_CHECK_ERROR_RETURN (error,-1);

    FT_Library_Version( __ft_lib, &major, &minor, &patch );
    ex_log ( "[FreeType] Version %d.%d.%d", major, minor, patch );

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
    char *name;

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
    FT_CHECK_ERROR_RETURN (error,NULL);

    //
    error = FT_Set_Pixel_Sizes ( face, 0, _size );
    FT_CHECK_ERROR_RETURN (error,NULL);

    //
    font = (ex_font_t *)ex_malloc ( sizeof(ex_font_t) );
    font->face_buffer = buffer;
    name = strrchr ( _filepath, '/' );
    strncpy ( font->facename, name == NULL ? _filepath : name+1, MAX_PATH );

    font->face = face;
    font->size = _size;
    font->outline_type = 0;
    font->outline_thickness = 1.0f;
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
    ex_free(_font->face_buffer);
    ex_free(_font);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_font_set_size ( ex_font_t *_font, int _size ) {
    FT_Error error;

    if ( _font->size == _size )
        return;

    error = FT_Set_Pixel_Sizes ( _font->face, 0, _size );
    FT_CHECK_ERROR_RETURN_VOID(error);

    _font->size = _size;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_font_get_kerning ( ex_font_t *_font, uint _first, uint _second ) {
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

ex_glyph_t *ex_font_get_glyph ( ex_font_t *_font, uint _ft_index ) {
    __glyph_key_t key;
    __glyph_set_t *set;
    ex_glyph_t *glyph;

    key.size = _font->size;
    key.outline_type = _font->outline_type;
    key.outline_thickness = _font->outline_thickness;

    // get glyph-set
    set = ex_hashmap_get( _font->glyph_sets, &key ); 
    if ( set == NULL ) {
        size_t idx = -1;
        __glyph_set_t new_set;

        new_set.glyphs = ex_hashmap_alloc ( sizeof(uint),
                                            sizeof(ex_glyph_t),
                                            1024,
                                            ex_hashkey_uint64,
                                            ex_keycmp_uint64
                                          );
        new_set.pages = ex_array_alloc ( sizeof(ALLEGRO_BITMAP *), 8 );
        new_set.cur_x = 0;
        new_set.cur_y = 0;
        new_set.max_height = -1;

        idx = ex_hashmap_add_unique ( _font->glyph_sets, &key, &new_set );
        set = ex_hashmap_get_by_idx ( _font->glyph_sets, idx );
    }

    // get glyph
    glyph = ex_hashmap_get( set->glyphs, &_ft_index ); 
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
        new_glyph.advance_x = -1;
        new_glyph.advance_y = -1;

        idx = ex_hashmap_add_unique ( set->glyphs, &_ft_index, &new_glyph );
        glyph = ex_hashmap_get_by_idx ( set->glyphs, idx );

        // init and cache the glyph data
        __init_glyph ( _font, set, glyph, _ft_index );
    }

    return glyph;
}
