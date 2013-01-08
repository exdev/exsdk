// ======================================================================================
// File         : bitarray.h
// Author       : Wu Jie 
// Last Change  : 06/26/2010 | 14:36:05 PM | Saturday,June
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef BITARRAY_H_1277534167
#define BITARRAY_H_1277534167
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" {
#endif
// ######################### 

/**********************************
USAGE:

    ex_bitarray_t *bitArray = ex_bitarray_alloc ( 10 );
    ex_bitarray_free ( bitArray );
***********************************/

// ------------------------------------------------------------------ 
// Desc: ex_bitarray_t 
// ------------------------------------------------------------------ 

typedef struct ex_bitarray_t {
    char *data;
    size_t count;

    // alloc methods
    void *(*alloc)      ( size_t );
    void *(*realloc)    ( void *, size_t );
    void  (*dealloc)    ( void * );
} ex_bitarray_t; // end struct _bitarray

// NOTE: in this way, we can still trace the memory leak.
static inline void *__ex_bitarray_alloc( size_t _size ) { return ex_malloc_tag ( _size, "ex_bitarray_t" ); }
static inline void *__ex_bitarray_realloc( void *_ptr, size_t _size ) { return ex_realloc_tag ( _ptr, _size, "ex_bitarray_t" ); }
static inline void  __ex_bitarray_dealloc( void *_ptr ) { ex_free ( _ptr ); }

static inline void *__ex_bitarray_alloc_nomng( size_t _size ) { return ex_malloc_nomng ( _size ); }
static inline void *__ex_bitarray_realloc_nomng( void *_ptr, size_t _size ) { return ex_realloc_nomng ( _ptr, _size ); }
static inline void  __ex_bitarray_dealloc_nomng( void *_ptr ) { ex_free_nomng ( _ptr ); }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern ex_bitarray_t *ex_bitarray_alloc ( size_t _bitcount );
#define ex_bitarray(_bitcount) ex_bitarray_alloc(_bitcount);

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_bitarray_free ( ex_bitarray_t *_bitarray );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_bitarray_init ( ex_bitarray_t *_bitarray, 
                               size_t _bitcount,
                               void *(*_alloc) ( size_t ),
                               void *(*_realloc) ( void *, size_t ),
                               void  (*_dealloc) ( void * ) );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_bitarray_deinit ( ex_bitarray_t *_bitarray );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern int ex_bitarray_get ( const ex_bitarray_t *_bitarray, size_t _idx );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_bitarray_set ( ex_bitarray_t *_bitarray, size_t _idx, int _value );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_bitarray_resize ( ex_bitarray_t *_bitarray, size_t _bitcount ); 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline size_t ex_bitarray_count ( const ex_bitarray_t *_bitarray ) { return _bitarray->count; } 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_bitarray_ncpy ( ex_bitarray_t *_to, const void *_buf, size_t _bitcount );
static inline void ex_bitarray_cpy ( ex_bitarray_t *_to, const ex_bitarray_t *_from ) {
    ex_bitarray_ncpy ( _to, _from->data, _from->count );
}

// ######################### 
#ifdef __cplusplus
} // end extern "C"
#endif
// ######################### 

// #################################################################################
#endif // END BITARRAY_H_1277534167
// #################################################################################


