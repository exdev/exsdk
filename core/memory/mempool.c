// ======================================================================================
// File         : mempool.c
// Author       : Wu Jie 
// Last Change  : 02/27/2013 | 09:56:13 AM | Wednesday,February
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ex_mempool_t *ex_mempool_alloc ( size_t _element_bytes, size_t _count ) {
    ex_mempool_t *pool = ex_malloc ( sizeof(ex_mempool_t) );
    ex_mempool_init( pool, _element_bytes, _count,
                     ex_func_alloc,
                     ex_func_realloc,
                     ex_func_dealloc
                   );
    return pool;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_mempool_free ( ex_mempool_t *_pool ) {
    ex_assert( _pool != NULL );

    ex_mempool_deinit(_pool);
    ex_free(_pool);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_mempool_init ( ex_mempool_t *_pool, 
                       size_t _element_bytes, 
                       size_t _count,
                       void *(*_alloc) ( size_t ),
                       void *(*_realloc) ( void *, size_t ),
                       void  (*_dealloc) ( void * )
                     )
{
    int data_size = _element_bytes * _count;
    int index_size = sizeof(size_t) * _count;
    size_t i = 1;

    // init members
    _pool->alloc = _alloc;
    _pool->realloc = _realloc;
    _pool->dealloc = _dealloc;

    _pool->block_count = 0;
    _pool->capacity = _count;
    _pool->element_bytes = _element_bytes;
    _pool->free_count = 0;

    // init data
    _pool->data = _pool->alloc( data_size );
    ex_memzero ( _pool->data, data_size );

    // init free indices
    _pool->free_indices = _pool->alloc( index_size );
    ex_memzero ( _pool->free_indices, index_size );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_mempool_deinit ( ex_mempool_t *_pool ) {
    ex_assert( _pool != NULL );

    _pool->dealloc(_pool->data);
    _pool->data = NULL;

    _pool->dealloc(_pool->free_indices);
    _pool->free_indices = NULL;

    _pool->element_bytes = 0;
    _pool->block_count = 0;
    _pool->capacity = 0;
    _pool->free_count = 0;

    _pool->alloc = NULL;
    _pool->realloc = NULL;
    _pool->dealloc = NULL;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_mempool_reserve ( ex_mempool_t *_pool, size_t _count ) {
    int i = _count - 1;

    // we don't process resizing if the new size is small than the _capacity
    if ( _count <= _pool->capacity )
        return;

    //
    _pool->data = _pool->realloc( _pool->data, _pool->element_bytes * _count );
    _pool->free_indices = _pool->realloc( _pool->free_indices,  sizeof(size_t) * _count  );
    _pool->capacity = _count;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

size_t ex_mempool_request ( ex_mempool_t *_pool, void **_address ) {
    size_t idx = -1;

    // if we have free node, use it
    if ( _pool->free_count > 0 ) {
        --_pool->free_count;
        idx = _pool->free_indices[_pool->free_count];

        if ( _address != NULL )
            *_address = (char *)(_pool->data) + idx * _pool->element_bytes;
        return idx;
    }

    //
    if ( _pool->block_count >= _pool->capacity ) {
        _pool->capacity *= 2;
        _pool->data = _pool->realloc ( _pool->data, _pool->element_bytes * _pool->capacity );
        _pool->free_indices = _pool->realloc ( _pool->free_indices,  sizeof(size_t) * _pool->capacity  );
    }

    idx = _pool->block_count;
    if ( _address != NULL )
        *_address = (char *)(_pool->data) + idx * _pool->element_bytes;
    ++_pool->block_count;

    return idx;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_mempool_return ( ex_mempool_t *_pool, size_t _idx ) {
    ex_assert( _idx >= 0 && _idx < _pool->capacity );

    _pool->free_indices[_pool->free_count] = _idx;
    ++_pool->free_count;

    ex_memzero ( (char *)(_pool->data) + _idx * _pool->element_bytes, _pool->element_bytes );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void *ex_mempool_get ( const ex_mempool_t *_pool, size_t _idx ) {
    ex_assert( _idx >= 0 && _idx < _pool->capacity );

    return (char *)(_pool->data) + _idx * _pool->element_bytes;
}
