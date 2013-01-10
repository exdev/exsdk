// ======================================================================================
// File         : array.c
// Author       : Wu Jie 
// Last Change  : 07/07/2010 | 13:23:51 PM | Wednesday,July
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

static inline void __array_init ( ex_array_t *_array, 
                                  size_t _element_bytes, 
                                  size_t _count,
                                  void *(*_alloc) ( size_t ),
                                  void *(*_realloc) ( void *, size_t ),
                                  void  (*_dealloc) ( void * ) )
{
    size_t bytes = _element_bytes * _count; 

    // init members
    _array->alloc = _alloc;
    _array->realloc = _realloc;
    _array->dealloc = _dealloc;

    _array->element_bytes = _element_bytes;
    _array->count = 0;
    _array->capacity = _count;

    // init data
    _array->data = _array->alloc( bytes );
    ex_memzero ( _array->data, bytes );
}

static inline uint32 __ceilpow2u ( uint32 _value ) {
    uint32 result = 1;
    while ( result < _value ) {
        result <<= 1; 
    }
    return result;
}

// ------------------------------------------------------------------ 
// Desc: 
static inline void *__array_alloc( size_t _size ) { return ex_malloc_tag ( _size, "ex_array_t" ); }
static inline void *__array_realloc( void *_ptr, size_t _size ) { return ex_realloc_tag ( _ptr, _size, "ex_array_t" ); }
static inline void  __array_dealloc( void *_ptr ) { ex_free ( _ptr ); }
// ------------------------------------------------------------------ 

ex_array_t *ex_array_new ( size_t _element_bytes, size_t _count ) {
    ex_array_t *arr = ex_malloc ( sizeof(ex_array_t) );
    __array_init ( arr, _element_bytes, _count,
                   __array_alloc,
                   __array_realloc,
                   __array_dealloc
                 );
    return arr;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ex_array_t *ex_array_new_with_allocator ( size_t _element_bytes, size_t _count,
                                          void *(*_alloc) ( size_t ),
                                          void *(*_realloc) ( void *, size_t ),
                                          void  (*_dealloc) ( void * ) )
{
    ex_array_t *arr = _alloc ( sizeof(ex_array_t) );
    __array_init ( arr, _element_bytes, _count,
                   _alloc,
                   _realloc,
                   _dealloc
                 );
    return arr;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_array_delete ( ex_array_t *_array ) {
    void  (*dealloc) ( void * ) = _array->dealloc;

    ex_assert_return( _array != NULL, /*dummy*/, "error: invalid _array, can not be NULL" );

    _array->dealloc(_array->data);
    _array->data = NULL;

    _array->element_bytes = 0;
    _array->count = 0;
    _array->capacity = 0;

    _array->alloc = NULL;
    _array->realloc = NULL;
    _array->dealloc = NULL;

    dealloc(_array);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_array_set ( ex_array_t *_array, size_t _idx, const void *_value ) {
    void *val_addr;

    ex_assert_return( _array != NULL, /*dummy*/, "error: invalid _array, can not be NULL" );
    ex_assert_return( _idx < _array->count, /*dummy*/, "error: _idx out of range" );

    val_addr = (char *)(_array->data) + _idx * _array->element_bytes;
    memcpy ( val_addr, _value, _array->element_bytes );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void *ex_array_get ( const ex_array_t *_array, size_t _idx ) {
    ex_assert_return( _array != NULL, NULL, "error: invalid _array, can not be NULL" );
    ex_assert_return( _idx < _array->count, NULL, "error: _idx out of range" );

    return (char *)(_array->data) + _idx * _array->element_bytes;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void *ex_array_add ( ex_array_t *_array, const void *_value ) {
    void *val_addr;

    ex_assert_return( _array != NULL, NULL, "error: invalid _array, can not be NULL" );

    if ( _array->count >= _array->capacity ) {
        _array->capacity *= 2;
        _array->data = _array->realloc ( _array->data, _array->capacity * _array->element_bytes );
    }

    //
    val_addr = (char *)(_array->data) + _array->count * _array->element_bytes;

    // if _value is NULL, that means insert an empty node.
    if ( _value )
        memcpy ( val_addr, _value, _array->element_bytes );

    ++_array->count;
    return val_addr;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void *ex_array_add_range ( ex_array_t *_array, const void *_data, size_t _count ) {
    void *val_addr;
    ex_assert_return( _array != NULL, NULL, "error: invalid _array, can not be NULL" );

    if ( _array->count + _count >= _array->capacity ) {
        _array->capacity = __ceilpow2u(_array->count + _count);
        _array->data = _array->realloc ( _array->data, _array->capacity * _array->element_bytes );
    }

    //
    val_addr = (char *)(_array->data) + _array->count * _array->element_bytes;

    //
    if ( _data )
        memcpy ( val_addr, _data, _array->element_bytes * _count );

    _array->count += _count;
    return val_addr;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void *ex_array_insert ( ex_array_t *_array, size_t _idx, const void *_value ) {
    void *val_addr;

    ex_assert_return( _array != NULL, NULL, "error: invalid _array, can not be NULL" );
    ex_assert_return( _idx <= _array->count, NULL, "error: _idx out of range" );

    if ( _array->count >= _array->capacity ) {
        _array->capacity *= 2;
        _array->data = _array->realloc ( _array->data, _array->capacity * _array->element_bytes );
    }
    if ( _idx < _array->count ) {
        memmove( (char *)(_array->data) + (_idx + 1) * _array->element_bytes,
                 (char *)(_array->data) +  _idx * _array->element_bytes,
                 (_array->count - _idx)  * _array->element_bytes);
    }

    val_addr = (char *)(_array->data) + _idx * _array->element_bytes;

    // if _value is NULL, that means insert an empty node.
    if ( _value )
        memcpy ( val_addr, _value, _array->element_bytes );
    ++_array->count;
    return val_addr;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void *ex_array_insert_range ( ex_array_t *_array, size_t _idx, const void *_data, size_t _count ) {
    void *val_addr;

    ex_assert_return( _array != NULL, NULL, "error: invalid _array, can not be NULL" );
    ex_assert_return( _idx <= _array->count, NULL, "error: _idx out of range" );

    if ( _array->count >= _array->capacity ) {
        _array->capacity = __ceilpow2u(_array->count + _count);
        _array->data = _array->realloc ( _array->data, _array->capacity * _array->element_bytes );
    }
    if ( _idx < _array->count ) {
        memmove( (char *)(_array->data) + (_idx + _count) * _array->element_bytes,
                 (char *)(_array->data) +  _idx * _array->element_bytes,
                 _count * _array->element_bytes);

        val_addr = (char *)(_array->data) + _idx * _array->element_bytes;
        memcpy ( val_addr, _data, _array->element_bytes * _count );
    }

    _array->count += _count;
    return val_addr;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_array_ncpy ( ex_array_t *_to, const void *_buf, size_t _count ) {
    if ( _to->capacity < _count ) {
        _to->capacity *= 2;
        _to->data = _to->realloc ( _to->data, _to->capacity * _to->element_bytes );
    }
    memcpy ( _to->data, _buf, _count * _to->element_bytes );
    _to->count = _count;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_array_remove_at ( ex_array_t *_array, size_t _idx ) {
    ex_assert_return( _array != NULL, /*dummy*/, "error: invalid _array, can not be NULL" );
    ex_assert_return( _idx < _array->count, /*dummy*/, "error: _idx out of range" );

    // don't do any thing if we only have one element in the array.
    if ( _idx != _array->count-1 ) {
        memmove ( ex_array_get( _array, _idx ),
                  ex_array_get( _array, _idx+1 ), 
                  _array->element_bytes * (_array->count - _idx - 1) );
    }

    // count the size
    --_array->count;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_array_remove_at_fast ( ex_array_t *_array, size_t _idx ) {
    ex_assert_return( _array != NULL, /*dummy*/, "error: invalid _array, can not be NULL" );
    ex_assert_return( _idx < _array->count, /*dummy*/, "error: _idx out of range" );

    // don't do any thing if we only have one element in the array.
    if ( _idx != _array->count-1 ) {
        // over write the erased element address by fill it with the last element.
        memcpy ( ex_array_get( _array, _idx ),
                 ex_array_get( _array, _array->count-1 ), 
                 _array->element_bytes );
    }

    // count the size
    --_array->count;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_array_remove_range ( ex_array_t *_array, size_t _idx, size_t _count ) {
    ex_assert_return( _array != NULL, /*dummy*/, "error: invalid _array, can not be NULL" );
    ex_assert_return( _idx < _array->count, /*dummy*/, "error: _idx out of range" );
    ex_assert_return( _idx + _count <= _array->count, /*dummy*/, "error: the remove count is exceed from index" );

    if ( _idx + _count != _array->count ) {
        memmove ( ex_array_get ( _array, _idx ), 
                  ex_array_get ( _array, _idx + _count), 
                 (_array->count - (_idx + _count)) * _array->element_bytes);
    }

    _array->count -= _count;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_array_remove_all ( ex_array_t *_array ) {
    ex_assert_return( _array != NULL, /*dummy*/, "error: invalid _array, can not be NULL" );
    _array->count = 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_array_sort( ex_array_t *_array, int (*_cmp)(const void *, const void *) ) {
    ex_assert_return( _array != NULL, /*dummy*/, "error: invalid _array, can not be NULL" );

    qsort ( _array->data, _array->count, _array->element_bytes, _cmp );
}
