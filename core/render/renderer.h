// ======================================================================================
// File         : renderer.h
// Author       : Wu Jie 
// Last Change  : 03/12/2013 | 16:20:46 PM | Tuesday,March
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef RENDERER_H_1363076445
#define RENDERER_H_1363076445
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" { 
#endif
// ######################### 

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

// vertex attribute type
enum {
    VAT_POSITION = 0,
    VAT_COLOR,
    VAT_TEXCOORD,
    VAT_MAX
};

// uniform constants
enum {
    UNIFORM_MATRIX_P,
    UNIFORM_MATRIX_MV,
    UNIFORM_MATRIX_MVP,

    UNIFORM_FLOAT_TIME,

    UNIFORM_MAX
};

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

typedef struct ex_renderer_t {
    bool initialized;

    // ui data
    ex_memblock_t    ui_node_block; 
    uint             ui_vb_id;
    ex_memblock_t    ui_vb;
    uint             ui_ib_id;
    ex_memblock_t    ui_ib;
    uint             ui_vao_id;
} ex_renderer_t;

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern int ex_renderer_init ( ex_renderer_t *_renderer );
extern void ex_renderer_deinit ( ex_renderer_t *_renderer );
static inline bool ex_renderer_initialized ( ex_renderer_t *_renderer ) {
    return _renderer->initialized;
}

extern void ex_set_current_renderer ( ex_renderer_t *_renderer );
extern ex_renderer_t *ex_current_renderer ();

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_renderer_draw_nodes ( ex_renderer_t *_renderer );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_renderer_draw_texture ( ex_renderer_t *_renderer,
                                       void *_texture,
                                       ex_recti_t _pos,
                                       ex_recti_t _border,
                                       ex_recti_t _rect,
                                       ex_vec4f_t _color ); 

///////////////////////////////////////////////////////////////////////////////
// interface
///////////////////////////////////////////////////////////////////////////////

#include "shader.h"

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 


// #################################################################################
#endif // END RENDERER_H_1363076445
// #################################################################################

