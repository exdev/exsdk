// ======================================================================================
// File         : bitarray.c
// Author       : Wu Jie 
// Last Change  : 06/26/2010 | 18:31:14 PM | Saturday,June
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

static inline void __bitarray_init ( ex_bitarray_t *_bitarray, 
                                     size_t _bitcount,
                                     void *(*_alloc) ( size_t ),
                                     void *(*_realloc) ( void *, size_t ),
                                     void  (*_dealloc) ( void * ) ) 
{
    size_t bytes = (_bitcount + 7)/8;

    _bitarray->alloc = _alloc;
    _bitarray->realloc = _realloc;
    _bitarray->dealloc = _dealloc;

    _bitarray->data = _bitarray->alloc(bytes);
    ex_memzero ( _bitarray->data, bytes );
    _bitarray->count = _bitcount;
}

// ------------------------------------------------------------------ 
// Desc: 
static inline void *__bitarray_alloc( size_t _size ) { return ex_malloc_tag ( _size, "ex_bitarray_t" ); }
static inline void *__bitarray_realloc( void *_ptr, size_t _size ) { return ex_realloc_tag ( _ptr, _size, "ex_bitarray_t" ); }
static inline void  __bitarray_dealloc( void *_ptr ) { ex_free ( _ptr ); }
// ------------------------------------------------------------------ 

ex_bitarray_t *ex_bitarray_new ( size_t _bitcount )
{
    ex_bitarray_t *bitArray = ex_malloc ( sizeof(ex_bitarray_t) );
    __bitarray_init ( bitArray, _bitcount, 
                      __bitarray_alloc,
                      __bitarray_realloc,
                      __bitarray_dealloc );
    return bitArray;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ex_bitarray_t *ex_bitarray_new_with_allocator ( size_t _bitcount,
                                                void *(*_alloc) ( size_t ),
                                                void *(*_realloc) ( void *, size_t ),
                                                void  (*_dealloc) ( void * ) )
{
    ex_bitarray_t *bitArray = _alloc ( sizeof(ex_bitarray_t) );
    __bitarray_init ( bitArray, _bitcount, 
                      _alloc,
                      _realloc,
                      _dealloc );
    return bitArray;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_bitarray_delete ( ex_bitarray_t *_bitarray ) {
    void  (*dealloc) ( void * ) = _bitarray->dealloc;

    ex_assert( _bitarray != NULL );

    _bitarray->dealloc(_bitarray->data);
    _bitarray->data = NULL;

    _bitarray->alloc = NULL;
    _bitarray->realloc = NULL;
    _bitarray->dealloc = NULL;

    _bitarray->count = 0;

    dealloc(_bitarray);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int ex_bitarray_get ( const ex_bitarray_t *_bitarray, size_t _idx )
{
    char *ptr;

    ex_assert ( _idx >= 0 && _idx < _bitarray->count );
    ptr = _bitarray->data + _idx / 8;
    return ( *ptr & (1 << (_idx % 8) ) ) != 0; /* 0 or 1 */
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_bitarray_set ( ex_bitarray_t *_bitarray, size_t _idx, int _value ) 
{
    char *ptr;

    ex_assert ( _idx >= 0 && _idx < _bitarray->count );
    ex_assert ( _value == 0 || _value == 1 );

    ptr = _bitarray->data + _idx / 8;
    if ( _value )
        *ptr |= 1 << ( _idx % 8 ); /*set bit*/
    else
        *ptr &= ~(1 << (_idx % 8)); /*clear bit*/
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// managed
void ex_bitarray_resize ( ex_bitarray_t *_bitarray, size_t _bitcount ) 
{
    size_t old_bytes, new_bytes;

    if ( _bitarray->count == _bitcount )
        return;

    old_bytes = (_bitarray->count + 7)/8;
    new_bytes = (_bitcount + 7)/8;

    _bitarray->data = _bitarray->realloc(_bitarray->data, new_bytes);
    // if new size is more than the old one, we need to set clear the memory to zero.
    if ( new_bytes > old_bytes )
        ex_memzero ( _bitarray->data + old_bytes, new_bytes - old_bytes );
    _bitarray->count = _bitcount;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_bitarray_ncpy ( ex_bitarray_t *_to, const void *_buf, size_t _bitcount ) {
    ex_bitarray_resize ( _to, _bitcount );
    memcpy( _to->data, _buf, (_bitcount+7)/8 );
}
