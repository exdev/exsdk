// ======================================================================================
// File         : memblock.c
// Author       : Wu Jie 
// Last Change  : 03/14/2013 | 10:41:30 AM | Thursday,March
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

ex_memblock_t *ex_memblock_alloc ( size_t _element_bytes, size_t _count ) {
    ex_memblock_t *pool = ex_malloc ( sizeof(ex_memblock_t) );
    ex_memblock_init( pool, _element_bytes, _count,
                     ex_func_alloc,
                     ex_func_realloc,
                     ex_func_dealloc
                   );
    return pool;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_memblock_free ( ex_memblock_t *_block ) {
    ex_assert( _block != NULL );

    ex_memblock_deinit(_block);
    ex_free(_block);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_memblock_init ( ex_memblock_t *_block, 
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
    _block->alloc = _alloc;
    _block->realloc = _realloc;
    _block->dealloc = _dealloc;

    _block->count = 0;
    _block->capacity = _count;
    _block->element_bytes = _element_bytes;

    // init data
    _block->data = _block->alloc( data_size );
    ex_memzero ( _block->data, data_size );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_memblock_deinit ( ex_memblock_t *_block ) {
    ex_assert( _block != NULL );

    _block->dealloc(_block->data);
    _block->data = NULL;

    _block->element_bytes = 0;
    _block->count = 0;
    _block->capacity = 0;

    _block->alloc = NULL;
    _block->realloc = NULL;
    _block->dealloc = NULL;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_memblock_reserve ( ex_memblock_t *_block, size_t _count ) {
    int i = _count - 1;

    // we don't process resizing if the new size is small than the _capacity
    if ( _count <= _block->capacity )
        return;

    //
    _block->data = _block->realloc( _block->data, _block->element_bytes * _count );
    _block->capacity = _count;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void *ex_memblock_request ( ex_memblock_t *_block, int _count ) {
    size_t idx = -1;

    ex_assert ( _count != 0 );

    //
    while ( _block->count + _count > _block->capacity ) {
        _block->capacity *= 2;
        _block->data = _block->realloc ( _block->data, _block->element_bytes * _block->capacity );
    }

    idx = _block->count;
    _block->count += _count;
    return (char *)(_block->data) + idx * _block->element_bytes;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void *ex_memblock_get ( const ex_memblock_t *_block, size_t _idx ) {
    ex_assert( _idx >= 0 && _idx < _block->capacity );

    return (char *)(_block->data) + _idx * _block->element_bytes;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_memblock_clear ( ex_memblock_t *_block ) {
    int data_size = _block->element_bytes * _block->capacity;
    int index_size = sizeof(size_t) * _block->capacity;

    _block->count = 0;

    // init data
    ex_memzero ( _block->data, data_size );
}
