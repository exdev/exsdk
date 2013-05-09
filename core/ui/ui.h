// ======================================================================================
// File         : ui.h
// Author       : Wu Jie 
// Last Change  : 04/01/2013 | 11:56:33 AM | Monday,April
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef UI_H_1364788594
#define UI_H_1364788594
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" { 
#endif
// ######################### 

typedef struct ex_ui_state_t {
    bool initialized;
    ex_memblock_t vb;
    ex_memblock_t ib;

    size_t primitive_count;
    ex_vec4f_t color;
    void *texture;
    ex_mat33f_t matrix;
} ex_ui_state_t;

typedef struct ex_ui_vertex_t {
    ex_vec2f_t pos;
    ex_vec2f_t uv0;
    ex_vec4f_t color;
} ex_ui_vertex_t;

///////////////////////////////////////////////////////////////////////////////
// state
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern ex_ui_state_t *ex_ui_state ();
extern void ex_ui_reset_state ();

extern int ex_ui_init ();
extern void ex_ui_deinit ();

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_ui_set_texture ( void *_texture );
extern void ex_ui_set_matrix ( ex_mat33f_t *_mat );
extern void ex_ui_set_color ( ex_vec4f_t *_color );

///////////////////////////////////////////////////////////////////////////////
// draw
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_ui_draw_texture ( int _dx, int _dy, int _dw, int _dh,
                                 int _sx, int _sy, int _sw, int _sh );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_ui_draw_border_texture ( int _dx, int _dy, int _dw, int _dh,
                                        int _l, int _r, int _t, int _b, 
                                        int _sx, int _sy, int _sw, int _sh );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_ui_draw_text ( const char *_text, 
                              ex_font_t *_font,
                              int _dx, int _dy, int _dw, int _dh );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_ui_draw_rect ( int _dx, int _dy, int _dw, int _dh, int _thickness );
extern void ex_ui_draw_filled_rect ( int _dx, int _dy, int _dw, int _dh );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_ui_flush ();

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 

// #################################################################################
#endif // END UI_H_1364788594
// #################################################################################
