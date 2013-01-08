// ======================================================================================
// File         : pool.h
// Author       : Wu Jie 
// Last Change  : 06/26/2010 | 14:15:10 PM | Saturday,June
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef POOL_H_1277532911
#define POOL_H_1277532911
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" {
#endif
// ######################### 

// Purpose: ex_pool_t is index fixed array 
//          When erase a item from ex_pool_t, the index of the other item will not changed.

///////////////////////////////////////////////////////////////////////////////
// decls
///////////////////////////////////////////////////////////////////////////////

#include "bitarray.h"

///////////////////////////////////////////////////////////////////////////////
// foreach
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
/*! 
 @def ex_pool_each
 @param _pool the in pool
 @param _type the type of the element in the pool.
 @param _el the element variable you want to define.
 @details macro for easy iterates the pool container.

 when use the macro, it will define the local variable below:
 - __node__: the current node of the pool
 - __id__: the current index.

 to finish the code, you must write ex_pool_each_end.

 Usage:
 @code
 ex_pool_t *my_pool = ex_pool_alloc( sizeof(float), 10 );
 ex_pool_each ( my_pool, float, item ) {
    printf( "item_%d is %f", idx, item );
 } ex_pool_each_end;
 @endcode
 @sa ex_pool_each_end
 @note DO NOT USE continue in this loop, use ex_pool_continue instead 
*/// ------------------------------------------------------------------ 

#define ex_pool_each( _pool, _type, _el ) \
    { \
        ex_pool_node_t *__node__ = (_pool)->used_nodes_begin; \
        ex_pool_node_t *__node_next__; \
        _type _el; \
        int __id__; \
        while ( __node__ ) { \
            __node_next__ = __node__->next; \
            __id__ = __node__ - (_pool)->nodes; \
            _el = *( (_type *) ex_pool_get( _pool, __id__ ) );

// ------------------------------------------------------------------ 
/*! 
 @def ex_pool_raw_each
 @param _pool the in pool
 @param _type the point-type of the element in the pool.
 @param _el the element variable you want to define.
 @details macro for easy iterates the pool container.

 when use the macro, it will define the local variable below:
 - __node__: the current node of the pool
 - __id__: the current index.

 to finish the code, you must write ex_pool_each_end.

 Usage:
 @code
 ex_pool_t *my_pool = ex_pool_alloc( sizeof(float), 10 );
 ex_pool_raw_each ( my_pool, float *, item ) {
    printf( "item_%d is %f", __id__, *item );
 } ex_pool_each_end;
 @endcode
 @sa ex_pool_each_end
 @note DO NOT USE continue in this loop, use ex_pool_continue instead 
*/// ------------------------------------------------------------------ 

#define ex_pool_raw_each( _pool, _type, _el ) \
    { \
        ex_pool_node_t *__node__ = (_pool)->used_nodes_begin; \
        ex_pool_node_t *__node_next__; \
        _type _el; \
        int __id__; \
        while ( __node__ ) { \
            __node_next__ = __node__->next; \
            __id__ = __node__ - (_pool)->nodes; \
            _el = (_type) ex_pool_get( _pool, __id__ );

// ------------------------------------------------------------------ 
/*! 
 @def ex_pool_each_end
 @details macro to end the ex_pool_each, ex_pool_raw_each macro
 @sa ex_pool_each
 @sa ex_pool_raw_each
*/// ------------------------------------------------------------------ 

#define ex_pool_each_end \
            __node__ = __node_next__; \
        } \
    }

// ------------------------------------------------------------------ 
/*! 
 @def ex_pool_continue
 @details macro to let the continue work in each
 @sa ex_pool_each
 @sa ex_pool_raw_each
*/// ------------------------------------------------------------------ 

#define ex_pool_continue \
    { \
        __node__ = __node_next__; \
        continue; \
    }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

//
typedef struct ex_pool_node_t {
    struct ex_pool_node_t *prev;
    struct ex_pool_node_t *next;
} ex_pool_node_t;

//
typedef struct ex_pool_t {
    // private
    size_t count;
    size_t capacity;
    size_t element_bytes;
    void *data;
    ex_pool_node_t *nodes;
    ex_bitarray_t *used_bits;

    ex_pool_node_t *used_nodes_begin;
    ex_pool_node_t *used_nodes_end;
    ex_pool_node_t *free_nodes;

    // alloc methods
    void *(*alloc)      ( size_t );
    void *(*realloc)    ( void *, size_t );
    void  (*dealloc)    ( void * );
} ex_pool_t;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

#define ex_pool(_type,_count) ex_pool_new( sizeof(_type), _count )
extern ex_pool_t *ex_pool_new ( size_t _element_bytes, size_t _count );
extern ex_pool_t *ex_pool_new_with_allocator ( size_t _element_bytes, size_t _count,
                                               void *(*_alloc) ( size_t ),
                                               void *(*_realloc) ( void *, size_t ),
                                               void  (*_dealloc) ( void * )
                                             );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_pool_delete ( ex_pool_t *_pool );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_pool_reserve ( ex_pool_t *_pool, size_t _count ); 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline size_t ex_pool_count ( const ex_pool_t *_pool ) { return _pool->count; }
static inline size_t ex_pool_capacity ( const ex_pool_t *_pool ) { return _pool->capacity; }

// ------------------------------------------------------------------ 
// Desc: 
// @param _value: if NULL, means add an empty node.
// ------------------------------------------------------------------ 

extern int ex_pool_add_new ( ex_pool_t *_pool, void **_node );
extern int ex_pool_add ( ex_pool_t *_pool, const void *_value );

static inline int ex_pool_add_int8 ( ex_pool_t *_pool, int8 _value ) { return ex_pool_add ( _pool, &_value ); }
static inline int ex_pool_add_int16 ( ex_pool_t *_pool, int16 _value ) { return ex_pool_add ( _pool, &_value ); }
static inline int ex_pool_add_int32 ( ex_pool_t *_pool, int32 _value ) { return ex_pool_add ( _pool, &_value ); }
static inline int ex_pool_add_int64 ( ex_pool_t *_pool, int64 _value ) { return ex_pool_add ( _pool, &_value ); }

static inline int ex_pool_add_uint8 ( ex_pool_t *_pool, uint8 _value ) { return ex_pool_add ( _pool, &_value ); }
static inline int ex_pool_add_uint16 ( ex_pool_t *_pool, uint16 _value ) { return ex_pool_add ( _pool, &_value ); }
static inline int ex_pool_add_uint32 ( ex_pool_t *_pool, uint32 _value ) { return ex_pool_add ( _pool, &_value ); }
static inline int ex_pool_add_uint64 ( ex_pool_t *_pool, uint64 _value ) { return ex_pool_add ( _pool, &_value ); }

static inline int ex_pool_add_float ( ex_pool_t *_pool, float _value ) { return ex_pool_add ( _pool, &_value ); }
static inline int ex_pool_add_double ( ex_pool_t *_pool, double _value ) { return ex_pool_add ( _pool, &_value ); }

static inline int ex_pool_add_string ( ex_pool_t *_pool, char *_value ) { return ex_pool_add ( _pool, &_value ); }
static inline int ex_pool_add_wstring ( ex_pool_t *_pool, wchar_t *_value ) { return ex_pool_add ( _pool, &_value ); }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void *ex_pool_get ( const ex_pool_t *_pool, int _idx );

static inline int8 ex_pool_get_int8 ( const ex_pool_t *_pool, int _idx ) { return *((int8 *)ex_pool_get ( _pool, _idx )); }
static inline int16 ex_pool_get_int16 ( const ex_pool_t *_pool, int _idx ) { return *((int16 *)ex_pool_get ( _pool, _idx )); }
static inline int32 ex_pool_get_int32 ( const ex_pool_t *_pool, int _idx ) { return *((int32 *)ex_pool_get ( _pool, _idx )); }
static inline int64 ex_pool_get_int64 ( const ex_pool_t *_pool, int _idx ) { return *((int64 *)ex_pool_get ( _pool, _idx )); }

static inline uint8 ex_pool_get_uint8 ( const ex_pool_t *_pool, int _idx ) { return *((uint8 *)(ex_pool_get ( _pool, _idx ))); }
static inline uint16 ex_pool_get_uint16 ( const ex_pool_t *_pool, int _idx ) { return *((uint16 *)ex_pool_get ( _pool, _idx )); }
static inline uint32 ex_pool_get_uint32 ( const ex_pool_t *_pool, int _idx ) { return *((uint32 *)ex_pool_get ( _pool, _idx )); }
static inline uint64 ex_pool_get_uint64 ( const ex_pool_t *_pool, int _idx ) { return *((uint64 *)ex_pool_get ( _pool, _idx )); }

static inline float ex_pool_get_float ( const ex_pool_t *_pool, int _idx ) { return *((float *)ex_pool_get ( _pool, _idx )); }
static inline double ex_pool_get_double ( const ex_pool_t *_pool, int _idx ) { return *((double *)ex_pool_get ( _pool, _idx )); }

static inline char *ex_pool_get_string ( const ex_pool_t *_pool, int _idx ) { return *((char **)ex_pool_get ( _pool, _idx )); }
static inline wchar_t *ex_pool_get_wstring ( const ex_pool_t *_pool, int _idx ) { return *((wchar_t **)ex_pool_get ( _pool, _idx )); }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_pool_cpy ( ex_pool_t *_to, const ex_pool_t *_from );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern bool ex_pool_isvalid ( const ex_pool_t *_pool, int _idx );
extern void *ex_pool_remove_at ( ex_pool_t *_pool, int _idx );
extern void *ex_pool_remove_at_safe ( ex_pool_t *_pool, int _idx );

// ######################### 
#ifdef __cplusplus
} // end extern "C"
#endif
// ######################### 

// #################################################################################
#endif // END POOL_H_1277532911
// #################################################################################


