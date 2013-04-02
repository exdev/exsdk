// ======================================================================================
// File         : ui.c
// Author       : Wu Jie 
// Last Change  : 04/01/2013 | 13:32:57 PM | Monday,April
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

#define MEMBLOCK_INIT( _block, _type, _size ) \
    ex_memblock_init ( &_block \
                      , sizeof(_type) \
                      , _size \
                      , ex_func_alloc \
                      , ex_func_realloc \
                      , ex_func_dealloc \
                    )

static ex_ui_state_t __ui_state;

///////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ex_ui_state_t *ex_ui_state () {
    return &__ui_state;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_ui_reset_state () {
    ex_memblock_clear ( &__ui_state.vb );
    ex_memblock_clear ( &__ui_state.ib );

    ex_vec4f_set ( &__ui_state.color, 1.0f, 1.0f, 1.0f, 1.0f );
    __ui_state.texture = NULL;
    ex_mat33f_identity ( &__ui_state.matrix );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_ui_init () {
    ex_assert ( __ui_state.initialized == false );

    if ( __ui_state.initialized )
        return -1;

    // ======================================================== 
    // init ui 
    // ======================================================== 

    // init current ui state
    ex_ui_reset_state ();

    // create ui node pool
    MEMBLOCK_INIT ( __ui_state.vb, ex_ui_vertex_t, 4096 );
    MEMBLOCK_INIT ( __ui_state.ib, uint16, 4096 );

    __ui_state.initialized = true;
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_ui_deinit () {
    ex_assert ( __ui_state.initialized );

    if ( __ui_state.initialized == false )
        return;

    // destroy ui node pool
    ex_memblock_deinit ( &__ui_state.vb );
    ex_memblock_deinit ( &__ui_state.ib );

    __ui_state.initialized = false;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_ui_set_texture ( void *_texture ) {
    __ui_state.texture = _texture;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_ui_set_matrix ( ex_mat33f_t *_mat ) {
    ex_mat33f_set( &__ui_state.matrix,
                   _mat->m00, _mat->m01, _mat->m02, 
                   _mat->m10, _mat->m11, _mat->m12, 
                   _mat->m20, _mat->m21, _mat->m22 );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_ui_set_color ( ex_vec4f_t *_color ) {
    ex_vec4f_set ( &__ui_state.color, _color->r, _color->g, _color->b, _color->a ); 
}
