// ======================================================================================
// File         : pool.c
// Author       : Wu Jie 
// Last Change  : 06/26/2010 | 14:15:26 PM | Saturday,June
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
// static defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static ex_pool_node_t *__request_free_node( ex_pool_t *_pool ) 
{
    ex_pool_node_t *node = NULL;

    if ( _pool->free_nodes == NULL ) {
        ex_pool_reserve( _pool, _pool->capacity * 2 );
    }

    node = _pool->free_nodes;
    _pool->free_nodes->next = NULL;
    _pool->free_nodes = _pool->free_nodes->prev;

    return node;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void __push_to_used ( ex_pool_t *_pool, ex_pool_node_t *_node )
{
    if ( _pool->used_nodes_end ) { // if we have used nodes
        _pool->used_nodes_end->next = _node;
        _node->prev = _pool->used_nodes_end;
        _node->next = NULL;
        _pool->used_nodes_end = _node;
    }
    else { // if it is the first one of the used nodes
        _pool->used_nodes_begin = _pool->used_nodes_end = _node;
        _pool->used_nodes_end->next = NULL;
        _pool->used_nodes_end->prev = NULL;
    }
    ex_bitarray_set( _pool->used_bits, _node - _pool->nodes, 1 );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void __push_to_used_reverse ( ex_pool_t *_pool, ex_pool_node_t *_node )
{
    if ( _pool->used_nodes_begin ) { // if we have used nodes
        _pool->used_nodes_begin->prev = _node;
        _node->next = _pool->used_nodes_begin;
        _node->prev = NULL;
        _pool->used_nodes_begin = _node;
    }
    else { // if it is the first one of the used nodes
        _pool->used_nodes_begin = _pool->used_nodes_end = _node;
        _pool->used_nodes_end->next = NULL;
        _pool->used_nodes_end->prev = NULL;
    }
    ex_bitarray_set( _pool->used_bits, _node - _pool->nodes, 1 );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void __push_to_free ( ex_pool_t *_pool, ex_pool_node_t *_node )
{
    if ( _pool->free_nodes ) { // if we have used nodes
        _pool->free_nodes->next = _node;
        _node->prev = _pool->free_nodes;
        _node->next = NULL;
        _pool->free_nodes = _node;
    }
    else { // if it is the first one of the used nodes
        _pool->free_nodes = _node;
        _pool->free_nodes->next = NULL;
        _pool->free_nodes->prev = NULL;
    }
    ex_bitarray_set( _pool->used_bits, _node - _pool->nodes, 0 );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void *__remove_at ( ex_pool_t *_pool, int _idx ) {
    ex_pool_node_t *node = NULL;

    // get current node.
    node = _pool->nodes + _idx;

    // re-locate the used_nodes begin and end
    if ( node == _pool->used_nodes_begin ) {
        _pool->used_nodes_begin = node->next;
    } 
    if ( node == _pool->used_nodes_end ) {
        _pool->used_nodes_end = node->prev;
    } 

    // unlink the node from used node.
    if ( node->prev )
        node->prev->next = node->next;
    if ( node->next )
        node->next->prev = node->prev;

    // return it to free_nodes
    __push_to_free( _pool, node );
    --_pool->count;

    return (char *)(_pool->data) + _idx * _pool->element_bytes;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void __pool_init ( ex_pool_t *_pool, 
                          size_t _element_bytes, 
                          size_t _count,
                          void *(*_alloc) ( size_t ),
                          void *(*_realloc) ( void *, size_t ),
                          void  (*_dealloc) ( void * )
                        )
{
    int size = _element_bytes * _count;
    size_t i = 1;

    // init members
    _pool->alloc = _alloc;
    _pool->realloc = _realloc;
    _pool->dealloc = _dealloc;

    _pool->count = 0;
    _pool->capacity = _count;
    _pool->element_bytes = _element_bytes;

    // init data
    _pool->data = _pool->alloc( size );
    ex_memzero ( _pool->data, size );

    // init nodes
    _pool->nodes = _pool->alloc( sizeof(ex_pool_node_t) * _count );
    _pool->used_nodes_begin = NULL;
    _pool->used_nodes_end = NULL;
    _pool->free_nodes = _pool->nodes + (_count-1);
    _pool->used_bits = ex_bitarray_new_with_allocator( _count, _alloc, _realloc, _dealloc );

    // init head node
    _pool->free_nodes->prev = NULL;
    _pool->free_nodes->next = _pool->free_nodes-1;
    --_pool->free_nodes;

    // init other node
    while ( i < _count ) {
        _pool->free_nodes->prev = _pool->free_nodes+1;

        if ( i == _count - 1 ) {
            _pool->free_nodes->next = NULL;
        }
        else {
            _pool->free_nodes->next = _pool->free_nodes-1;
            --_pool->free_nodes;
        }
        ++i;
    }
}

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
static inline void *__pool_alloc( size_t _size ) { return ex_malloc_tag ( _size, "ex_pool_t" ); }
static inline void *__pool_realloc( void *_ptr, size_t _size ) { return ex_realloc_tag ( _ptr, _size, "ex_pool_t" ); }
static inline void  __pool_dealloc( void *_ptr ) { ex_free ( _ptr ); }
// ------------------------------------------------------------------ 

ex_pool_t *ex_pool_new ( size_t _element_bytes, size_t _count )
{
    ex_pool_t *pool = ex_malloc ( sizeof(ex_pool_t) );
    __pool_init( pool, 
                 _element_bytes, 
                 _count,
                 __pool_alloc,
                 __pool_realloc,
                 __pool_dealloc
               );
    return pool;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ex_pool_t *ex_pool_new_with_allocator ( size_t _element_bytes, size_t _count,
                                        void *(*_alloc) ( size_t ),
                                        void *(*_realloc) ( void *, size_t ),
                                        void  (*_dealloc) ( void * ) )
{
    ex_pool_t *pool = _alloc ( sizeof(ex_pool_t) );
    __pool_init( pool, 
                 _element_bytes, 
                 _count,
                 _alloc,
                 _realloc,
                 _dealloc
               );
    return pool;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_pool_delete ( ex_pool_t *_pool ) {
    void  (*dealloc) ( void * ) = _pool->dealloc;

    ex_assert( _pool != NULL );

    _pool->dealloc(_pool->data);
    _pool->data = NULL;

    _pool->dealloc(_pool->nodes);
    _pool->nodes = NULL;

    ex_bitarray_delete( _pool->used_bits );
    _pool->used_bits = NULL;

    _pool->element_bytes = 0;
    _pool->count = 0;
    _pool->capacity = 0;

    _pool->alloc = NULL;
    _pool->realloc = NULL;
    _pool->dealloc = NULL;

    dealloc(_pool);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_pool_reserve ( ex_pool_t *_pool, size_t _count ) 
{
    size_t size = _count * _pool->element_bytes;
    int i = _count - 1;

    // we don't process resizing if the new size is small than the _capacity
    if ( _count <= _pool->capacity )
        return;

    //
    _pool->data = _pool->realloc( _pool->data, size );
    _pool->nodes = _pool->realloc( _pool->nodes,  sizeof(ex_pool_node_t) * _count  );
    ex_bitarray_resize ( _pool->used_bits, _count );
    _pool->capacity = _count;

    _pool->used_nodes_begin = NULL;
    _pool->used_nodes_end = NULL;
    _pool->free_nodes = NULL;

    while ( i >= 0 ) {
        // if curren index is in used.
        if ( ex_bitarray_get ( _pool->used_bits, i ) ) {
            __push_to_used_reverse ( _pool, _pool->nodes + i );
        }
        else {
            __push_to_free ( _pool, _pool->nodes + i );
        }
        --i;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_pool_add_new ( ex_pool_t *_pool, void **_node ) {
    ex_pool_node_t *node = NULL;
    int idx = -1;

    node = __request_free_node(_pool);
    ex_assert ( node != NULL );

    __push_to_used( _pool, node );
    idx = node - _pool->nodes;

    ++_pool->count;
    
    *_node = (char *)(_pool->data) + idx * _pool->element_bytes;
    return idx;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_pool_add ( ex_pool_t *_pool, const void *_value ) {
    ex_pool_node_t *node = NULL;
    int idx = -1;

    node = __request_free_node(_pool);
    ex_assert ( node != NULL );

    __push_to_used( _pool, node );
    idx = node - _pool->nodes;

    // if _value is NULL, that means add an empty node.
    if ( _value )
        memcpy ( (char *)(_pool->data) + idx * _pool->element_bytes, _value, _pool->element_bytes );

    ++_pool->count;
    
    return idx;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_pool_cpy ( ex_pool_t *_to, const ex_pool_t *_from ) {
    int i;
    ex_assert ( _to->element_bytes == _from->element_bytes );

    if ( _to->capacity < _from->capacity ) {
        _to->capacity = _from->capacity;
        _to->data = _to->realloc( _to->data, _to->capacity * _to->element_bytes );
        _to->nodes = _to->realloc( _to->nodes,  _to->capacity * sizeof(ex_pool_node_t) );
    }

    //
    memcpy ( _to->data, _from->data, _from->capacity * _from->element_bytes );
    memcpy ( _to->nodes, _from->nodes,  _from->capacity * sizeof(ex_pool_node_t) );
    ex_bitarray_cpy ( _to->used_bits, _from->used_bits );

    //
    _to->used_nodes_begin = NULL;
    _to->used_nodes_end = NULL;
    _to->free_nodes = NULL;

    i = _to->capacity - 1;
    while ( i >= 0 ) {
        // if curren index is in used.
        if ( ex_bitarray_get ( _to->used_bits, i ) ) {
            __push_to_used_reverse ( _to, _to->nodes + i );
        }
        else {
            __push_to_free ( _to, _to->nodes + i );
        }
        --i;
    }
    _to->count = _from->count;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_pool_isvalid ( const ex_pool_t *_pool, int _idx ) {
    return ex_bitarray_get(_pool->used_bits, _idx) == 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void *ex_pool_remove_at ( ex_pool_t *_pool, int _idx ) {
    ex_assert( _idx >= 0 && _idx < (int)_pool->capacity );
    ex_assert( ex_bitarray_get(_pool->used_bits, _idx) == 1 );

    return __remove_at ( _pool, _idx );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void *ex_pool_remove_at_safe ( ex_pool_t *_pool, int _idx ) {
    if ( _idx < 0 || _idx >= (int)_pool->capacity )
        return NULL;
    if ( ex_bitarray_get(_pool->used_bits, _idx) != 1 )
        return NULL;

    return __remove_at ( _pool, _idx );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void *ex_pool_get ( const ex_pool_t *_pool, int _idx )
{
    ex_assert( _idx >= 0 && (size_t)_idx < _pool->capacity );
    // ex_assert( ex_bitarray_get(_pool->used_bits, _idx) == 1, NULL, "error: the node is not in used." );
    if ( ex_bitarray_get(_pool->used_bits, _idx) != 1 )
        return NULL;

    return (char *)(_pool->data) + _idx * _pool->element_bytes;
}
