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

ex_bitarray_t *ex_bitarray_alloc ( size_t _bitcount )
{
    ex_bitarray_t *bitArray = ex_malloc ( sizeof(ex_bitarray_t) );
    ex_bitarray_init ( bitArray, _bitcount, 
                       ex_func_alloc,
                       ex_func_realloc,
                       ex_func_dealloc );
    return bitArray;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_bitarray_free ( ex_bitarray_t *_bitarray )
{
    ex_assert( _bitarray != NULL );

    ex_bitarray_deinit(_bitarray);
    _bitarray->count = 0;
    ex_free(_bitarray);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_bitarray_init ( ex_bitarray_t *_bitarray, 
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
// ------------------------------------------------------------------ 

void ex_bitarray_deinit ( ex_bitarray_t *_bitarray ) {
    ex_assert( _bitarray != NULL );

    _bitarray->dealloc(_bitarray->data);
    _bitarray->data = NULL;

    _bitarray->alloc = NULL;
    _bitarray->realloc = NULL;
    _bitarray->dealloc = NULL;
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
