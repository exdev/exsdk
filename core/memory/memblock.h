// ======================================================================================
// File         : memblock.h
// Author       : Wu Jie 
// Last Change  : 03/14/2013 | 10:41:08 AM | Thursday,March
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MEMBLOCK_H_1363228870
#define MEMBLOCK_H_1363228870
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" {
#endif
// ######################### 

typedef struct ex_memblock_t {
    // private
    size_t capacity;
    size_t element_bytes;
    size_t count;
    void *data;

    // alloc methods
    void *(*alloc)      ( size_t );
    void *(*realloc)    ( void *, size_t );
    void  (*dealloc)    ( void * );

} ex_memblock_t;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern ex_memblock_t *ex_memblock_alloc ( size_t _element_bytes, size_t _count );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_memblock_free ( ex_memblock_t *_block );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_memblock_init ( ex_memblock_t *_block, 
                              size_t _element_bytes, 
                              size_t _count,
                              void *(*_alloc) ( size_t ),
                              void *(*_realloc) ( void *, size_t ),
                              void  (*_dealloc) ( void * )
                            );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_memblock_deinit ( ex_memblock_t *_block ); 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_memblock_reserve ( ex_memblock_t *_block, size_t _count ); 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline size_t ex_memblock_count ( const ex_memblock_t *_block ) { return _block->count; }
static inline size_t ex_memblock_capacity ( const ex_memblock_t *_block ) { return _block->capacity; }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void *ex_memblock_request ( ex_memblock_t *_block, int _count );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void *ex_memblock_get ( const ex_memblock_t *_block, size_t _idx );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_memblock_clear ( const ex_memblock_t *_block );

// ######################### 
#ifdef __cplusplus
} // end extern "C"
#endif
// ######################### 

// #################################################################################
#endif // END MEMBLOCK_H_1363228870
// #################################################################################
