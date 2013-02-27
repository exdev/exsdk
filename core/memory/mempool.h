// ======================================================================================
// File         : mempool.h
// Author       : Wu Jie 
// Last Change  : 02/27/2013 | 09:25:13 AM | Wednesday,February
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MEMPOOL_H_1361928314
#define MEMPOOL_H_1361928314
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" {
#endif
// ######################### 

typedef struct ex_mempool_t {
    // private
    size_t capacity;
    size_t element_bytes;
    size_t block_count;
    size_t free_count;
    void *data;
    size_t *free_indices;

    // alloc methods
    void *(*alloc)      ( size_t );
    void *(*realloc)    ( void *, size_t );
    void  (*dealloc)    ( void * );

} ex_mempool_t;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern ex_mempool_t *ex_mempool_alloc ( size_t _element_bytes, size_t _count );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_mempool_free ( ex_mempool_t *_pool );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_mempool_init ( ex_mempool_t *_pool, 
                              size_t _element_bytes, 
                              size_t _count,
                              void *(*_alloc) ( size_t ),
                              void *(*_realloc) ( void *, size_t ),
                              void  (*_dealloc) ( void * )
                            );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_mempool_deinit ( ex_mempool_t *_pool ); 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_mempool_reserve ( ex_mempool_t *_pool, size_t _count ); 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline size_t ex_mempool_capacity ( const ex_mempool_t *_pool ) { return _pool->capacity; }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern size_t ex_mempool_request ( ex_mempool_t *_pool, void **_address );
extern void ex_mempool_return ( ex_mempool_t *_pool, size_t _idx );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void *ex_mempool_get ( const ex_mempool_t *_pool, size_t _idx );

// ######################### 
#ifdef __cplusplus
} // end extern "C"
#endif
// ######################### 

// #################################################################################
#endif // END MEMPOOL_H_1361928314
// #################################################################################
