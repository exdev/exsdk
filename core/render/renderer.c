// ======================================================================================
// File         : renderer.c
// Author       : Wu Jie 
// Last Change  : 03/12/2013 | 16:21:54 PM | Tuesday,March
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
// static
///////////////////////////////////////////////////////////////////////////////

static bool __initialized = false;
static ex_mempool_t __ui_node_pool; 
static ex_ui_state_t __cur_ui_state;

#define MEMPOOL_INIT( _pool, _type, _size ) \
    ex_mempool_init ( &_pool \
                      , sizeof(_type) \
                      , _size \
                      , ex_func_alloc \
                      , ex_func_realloc \
                      , ex_func_dealloc \
                    )

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void __reset_ui_state () {
    __cur_ui_state.node = NULL;
    __cur_ui_state.matrix = EX_MAT44F_IDENTITY;
}

///////////////////////////////////////////////////////////////////////////////
// renderer op
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_renderer_init () {
    ex_assert ( __initialized == false );

    if ( __initialized )
        return -1;

    // init current ui state
    __reset_ui_state ();

    // create ui node pool
    MEMPOOL_INIT ( __ui_node_pool, ex_ui_node_t, 512 );

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_renderer_deinit () {
    ex_assert ( __initialized );

    if ( __initialized == false )
        return;

    // destroy ui node pool
    ex_mempool_deinit ( &__ui_node_pool );

    __initialized = false;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_renderer_initialized () { 
    return __initialized;
}

///////////////////////////////////////////////////////////////////////////////
// node op
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ex_ui_node_t *ex_request_ui_node () {
    ex_ui_node_t *node;
    ex_mempool_request( &__ui_node_pool, &node );
    return node;
}

///////////////////////////////////////////////////////////////////////////////
// ui op
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_ui_draw_texture ( ex_recti_t _pos,
                          ex_recti_t _border,
                          ex_rectf_t _uv0,
                          ex_vec4f_t _color ) 
{
    ex_ui_node_t *node;

    node = ex_request_ui_node();
    node->parent = __cur_ui_state.node;
    node->transform = __cur_ui_state.matrix; 
    node->pos = _pos;
    node->border = _border;
    node->uv0 = _uv0;
    node->color = _color;
}
