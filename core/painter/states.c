// ======================================================================================
// File         : states.c
// Author       : Wu Jie 
// Last Change  : 11/29/2013 | 16:43:18 PM | Friday,November
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

static ex_painter_state_t __painter_state;

///////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_painter_init () {
    ex_assert ( __painter_state.initialized == false );

    if ( __painter_state.initialized ) {
        ex_set_error ( "[painter] Error: Already initialized." );
        return -1;
    }

    // ======================================================== 
    // init ui 
    // ======================================================== 

    // init current ui state
    ex_painter_reset_state ();

    // create ui node pool
    MEMBLOCK_INIT ( __painter_state.vb, ex_painter_vertex_t, 4096 );
    MEMBLOCK_INIT ( __painter_state.ib, uint16, 4096 );

    __painter_state.initialized = true;
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_painter_deinit () {
    ex_assert ( __painter_state.initialized );

    if ( __painter_state.initialized == false )
        return;

    // destroy ui node pool
    ex_memblock_deinit ( &__painter_state.vb );
    ex_memblock_deinit ( &__painter_state.ib );

    __painter_state.initialized = false;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ex_painter_state_t *ex_painter_state () {
    return &__painter_state;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_painter_reset_state () {
    ex_memblock_clear ( &__painter_state.vb );
    ex_memblock_clear ( &__painter_state.ib );

    ex_vec4f_set ( &__painter_state.color, 1.0f, 1.0f, 1.0f, 1.0f );
    __painter_state.texture = NULL;
    ex_mat33f_identity ( &__painter_state.matrix );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_painter_set_texture ( void *_texture ) {
    if ( __painter_state.texture != _texture ) {
        ex_painter_flush();
        __painter_state.texture = _texture;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_painter_set_matrix ( ex_mat33f_t *_mat ) {
    ex_mat33f_set( &__painter_state.matrix,
                   _mat->m00, _mat->m01, _mat->m02, 
                   _mat->m10, _mat->m11, _mat->m12, 
                   _mat->m20, _mat->m21, _mat->m22 );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_painter_set_color ( ex_vec4f_t *_color ) {
    ex_color4f_set ( &__painter_state.color, _color->r, _color->g, _color->b, _color->a ); 
}
