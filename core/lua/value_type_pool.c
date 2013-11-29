// ======================================================================================
// File         : value_type_pool.c
// Author       : Wu Jie 
// Last Change  : 02/26/2013 | 13:37:16 PM | Tuesday,February
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "allegro5/allegro.h"
#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

static ex_mempool_t __vec2f_pool; 
static ex_mempool_t __vec3f_pool; 
static ex_mempool_t __vec4f_pool; 
static ex_mempool_t __mat44f_pool; 

#define MEMPOOL_INIT( _pool, _type, _size ) \
    ex_mempool_init ( &_pool \
                      , sizeof(_type) \
                      , _size \
                      , ex_func_alloc \
                      , ex_func_realloc \
                      , ex_func_dealloc \
                    )

///////////////////////////////////////////////////////////////////////////////
// functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void __ex_value_type_pool_init () {
    MEMPOOL_INIT ( __vec2f_pool, ex_vec2f_t, 256 );
    MEMPOOL_INIT ( __vec3f_pool, ex_vec3f_t, 256 );
    MEMPOOL_INIT ( __vec4f_pool, ex_vec4f_t, 256 );
    MEMPOOL_INIT ( __mat44f_pool, ex_mat44f_t, 256 );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void __ex_value_type_pool_deinit () {
    ex_mempool_deinit ( &__vec2f_pool );
    ex_mempool_deinit ( &__vec3f_pool );
    ex_mempool_deinit ( &__vec4f_pool );
    ex_mempool_deinit ( &__mat44f_pool );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

size_t __ex_vec2f_pool_request ( ex_vec2f_t **_ptr ) {
    return ex_mempool_request( &__vec2f_pool, (void **)_ptr );
}
void __ex_vec2f_pool_return ( size_t _handle ) {
    ex_mempool_return( &__vec2f_pool, _handle );
}
ex_vec2f_t *__ex_vec2f_pool_get ( size_t _handle ) {
    return ex_mempool_get( &__vec2f_pool, _handle );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

size_t __ex_vec3f_pool_request ( ex_vec3f_t **_ptr ) {
    return ex_mempool_request( &__vec3f_pool, (void **)_ptr );
}
void __ex_vec3f_pool_return ( size_t _handle ) {
    ex_mempool_return( &__vec3f_pool, _handle );
}
ex_vec3f_t *__ex_vec3f_pool_get ( size_t _handle ) {
    return ex_mempool_get( &__vec3f_pool, _handle );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

size_t __ex_vec4f_pool_request ( ex_vec4f_t **_ptr ) {
    return ex_mempool_request( &__vec4f_pool, (void **)_ptr );
}
void __ex_vec4f_pool_return ( size_t _handle ) {
    ex_mempool_return( &__vec4f_pool, _handle );
}
ex_vec4f_t *__ex_vec4f_pool_get ( size_t _handle ) {
    return ex_mempool_get( &__vec4f_pool, _handle );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

size_t __ex_mat44f_pool_request ( ex_mat44f_t **_ptr ) {
    return ex_mempool_request( &__mat44f_pool, (void **)_ptr );
}
void __ex_mat44f_pool_return ( size_t _handle ) {
    ex_mempool_return( &__mat44f_pool, _handle );
}
ex_mat44f_t *__ex_mat44f_pool_get ( size_t _handle ) {
    return ex_mempool_get( &__mat44f_pool, _handle );
}

