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

typedef struct ex_renderer_t {
    bool initialized = false;

    // ui data
    ex_ui_state_t   ui_state;
    ex_memblock_t    ui_node_block; 
    ex_memblock_t    ui_vertex_buffer;
    ex_memblock_t    ui_index_buffer;
} ex_renderer_t;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern int ex_renderer_init ( ex_renderer_t *_renderer );
extern void ex_renderer_deinit ( ex_renderer_t *_renderer );
static inline bool ex_renderer_initialized ( ex_renderer_t *_renderer ) {
    return _renderer->initialized;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_renderer_draw_nodes ( ex_renderer_t *_renderer );

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 


// #################################################################################
#endif // END RENDERER_H_1363076445
// #################################################################################

