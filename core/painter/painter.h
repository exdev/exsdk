// ======================================================================================
// File         : painter.h
// Author       : Wu Jie 
// Last Change  : 11/29/2013 | 16:42:49 PM | Friday,November
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef PAINTER_H_1385714570
#define PAINTER_H_1385714570
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" { 
#endif
// ######################### 

typedef struct ex_painter_state_t {
    bool initialized;
    ex_memblock_t vb;
    ex_memblock_t ib;

    size_t primitive_count;
    ex_vec4f_t color;
    void *texture;
    ex_mat33f_t matrix;
} ex_painter_state_t;

typedef struct ex_painter_vertex_t {
    ex_vec2f_t pos;
    ex_vec2f_t uv0;
    ex_vec4f_t color;
} ex_painter_vertex_t;

///////////////////////////////////////////////////////////////////////////////
// state
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern int ex_painter_init ();
extern void ex_painter_deinit ();

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern ex_painter_state_t *ex_painter_state ();
extern void ex_painter_reset_state ();

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_painter_set_texture ( void *_texture );
extern void ex_painter_set_matrix ( ex_mat33f_t *_mat );
extern void ex_painter_set_color ( ex_vec4f_t *_color );
extern void ex_painter_flush ();

///////////////////////////////////////////////////////////////////////////////
// draw
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_painter_draw_texture ( int _dx, int _dy, int _dw, int _dh,
                                      int _sx, int _sy, int _sw, int _sh );
extern void ex_painter_draw_sliced_texture ( int _dx, int _dy, int _dw, int _dh,
                                             int _t, int _r, int _b, int _l, 
                                             int _sx, int _sy, int _sw, int _sh );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_painter_draw_text ( const char *_text, ex_font_t *_font, int _dx, int _dy );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_painter_draw_rect ( int _dx, int _dy, int _dw, int _dh, int _thickness );
extern void ex_painter_draw_rect_4 ( int _dx, int _dy, int _dw, int _dh, 
                                     int _t, int _r, int _b, int _l );
extern void ex_painter_draw_filled_rect ( int _dx, int _dy, int _dw, int _dh );

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 

// #################################################################################
#endif // END PAINTER_H_1385714570
// #################################################################################
