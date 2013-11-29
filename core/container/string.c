// ======================================================================================
// File         : string.c
// Author       : Wu Jie 
// Last Change  : 11/28/2013 | 11:38:22 AM | Thursday,November
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

#define BUF_SIZE 256

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ex_str_t *ex_str_alloc ( const char *_cstr ) {
    char *buffer = NULL;
    size_t buf_size = -1;
    size_t cstr_len = -1;
    ex_str_t *new_str;
    
    cstr_len = strlen(_cstr);
    buf_size = ex_ceilpow2u(cstr_len+1);
    buffer = (char *)ex_malloc( buf_size);
    strncpy( buffer, _cstr, cstr_len );
    buffer[cstr_len] = '\0';

    new_str = (ex_str_t *)ex_malloc( sizeof(ex_str_t) );
    new_str->data = buffer;
    new_str->count = cstr_len;
    new_str->capacity = buf_size;

    return new_str;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ex_str_t *ex_str_allocf ( const char *_fmt, ... ) {
    int result = -1;
    char *buffer = NULL;
    ex_str_t *new_str;
    size_t buffer_size = BUF_SIZE;

    buffer = ex_malloc(buffer_size);
    EX_GET_VA_STRING_WITH_RESULT( buffer, BUF_SIZE-1, _fmt, &result ); // NOTE: the buffer_size-1 will leave 1 character for null terminal
    if ( result == -1 ) {
        buffer_size = BUF_SIZE * 2;

        // keep get va string until success 
        do {
            buffer = (char *)ex_realloc( buffer, buffer_size * sizeof(char) );
            EX_GET_VA_STRING_WITH_RESULT( buffer, buffer_size-1, _fmt, &result ); // NOTE: the buffer_size-1 will leave 1 character for null terminal
            buffer_size *= 2;
        } while ( result == -1 );
    }
    buffer[result] = '\0';

    new_str = (ex_str_t *)ex_malloc( sizeof(ex_str_t) );
    new_str->data = buffer;
    new_str->count = result;
    new_str->capacity = buffer_size;

    return new_str;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_str_free ( ex_str_t *_exstr ) {
    _exstr->count = 0;
    _exstr->capacity = 0;
    ex_free(_exstr->data);
    ex_free(_exstr);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_str_cat ( ex_str_t *_exstr, const char *_cstr ) { 
    size_t cstr_len = -1;
    size_t original_len;

    original_len = _exstr->count;
    cstr_len = strlen(_cstr);
    ex_str_ncat ( _exstr, _cstr, cstr_len );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_str_ncat ( ex_str_t *_exstr, const char *_cstr, size_t _size ) { 
    size_t original_len;

    original_len = _exstr->count;
    if ( _size+1 > (_exstr->capacity-_exstr->count) ) {
        _exstr->capacity = ex_ceilpow2u(_exstr->count + _size + 1);
        _exstr->count = _exstr->count + _size + 1;
        _exstr->data = ex_realloc( _exstr->data, _exstr->capacity * sizeof(char) );
    }

    strncpy ( _exstr->data+original_len, _cstr, _size );
    _exstr->data[_exstr->count] = '\0';
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_str_catf ( ex_str_t *_exstr, const char *_fmt, ... ) { 
    int result = -1;
    int status;
    char buf[BUF_SIZE];
    char *buffer = NULL;

    EX_GET_VA_STRING_WITH_RESULT( buf, BUF_SIZE, _fmt, &result );
    buffer = buf;
    if ( result == -1 ) {
        char *dyn_buf = NULL;
        int buffer_count = BUF_SIZE * 2;

        // keep get va string until success 
        do {
            dyn_buf = (char *)ex_realloc_nomng( dyn_buf, buffer_count * sizeof(char) );
            EX_GET_VA_STRING_WITH_RESULT( dyn_buf, buffer_count, _fmt, &result ); // NOTE: the buffer_count-1 will leave 1 character for null terminal
            buffer_count *= 2;
        } while ( result == -1 );
        buffer = dyn_buf;
    }
    ex_str_ncat ( _exstr, buffer, result );

    // if we use dynamic buffer, free it
    if ( buffer != buf )
        ex_free_nomng ( buffer );
}
