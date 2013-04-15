// ======================================================================================
// File         : font.h
// Author       : Wu Jie 
// Last Change  : 04/08/2013 | 16:25:18 PM | Monday,April
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef FONT_H_1365409519
#define FONT_H_1365409519
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// font
///////////////////////////////////////////////////////////////////////////////

typedef struct ex_glyph_t {
   void *page;
   int16 x;
   int16 y;
   int16 w;
   int16 h;
   int16 offset_x;
   int16 offset_y;
   int16 advance_x;
   int16 advance_y;
} ex_glyph_t;

typedef struct ex_font_t {
    void *face;
    int size;
    int outline_type; // ( 0 = None, 1 = Line, 2 = Inner, 3 = Outer )
    int outline_thickness;
    ex_hashmap_t *glyph_sets; // (size, outline_type, outline_thickness) -> ex_glyph_set_t 
} ex_font_t;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern int ex_font_init ();
extern void ex_font_deinit ();
extern bool ex_font_initialized ();

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern ex_font_t *ex_font_load ( const char *_filepath, int _size );
extern void ex_font_destroy ( ex_font_t *_font );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_font_set_size ( ex_font_t *_font, int _size );
extern int ex_font_get_kerning ( ex_font_t *_font, int _first, int _second );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern ex_glyph_t *ex_font_get_glyph ( ex_font_t *_font, int _ft_index );
extern void ex_font_cache_glyph ( ex_font_t *_font, ex_glyph_t *_glyph, int _ft_index );

// #################################################################################
#endif // END FONT_H_1365409519
// #################################################################################


