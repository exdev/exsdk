// ======================================================================================
// File         : hashmap.h
// Author       : Wu Jie 
// Last Change  : 06/28/2010 | 08:03:23 AM | Monday,June
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef HASHMAP_H_1277683404
#define HASHMAP_H_1277683404
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" {
#endif
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "pool.h"

///////////////////////////////////////////////////////////////////////////////
// foreach
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
/*! 
 @def ex_hashmap_each
 @param _hashmap the in hashmap
 @param _type the type of the value in the hashmap.
 @param _el the value variable you want to define.
 @details macro for easy iterates the hashmap container.

 when use the macro, it will define the local variable below:
 - __node__: the current node of the hashmap
 - __node_begin__: the the beginning of the node

 to finish the code, you must write ex_hashmap_each_end.

 Usage:
 @code
 ex_hashmap_t *my_hashmap = ex_hashmap_alloc( sizeof(int), sizeof(float), 10 );
 ex_hashmap_each ( my_hashmap, float, item ) {
    printf( "item is %f", item );
 } ex_hashmap_each_end;
 @endcode
 @sa ex_hashmap_each_end
 @note DO NOT USE continue in this loop, use ex_hashmap_continue instead 
*/// ------------------------------------------------------------------ 

#define ex_hashmap_each( _hashmap, _type, _el ) \
    { \
        ex_pool_node_t *__node__ = (_hashmap)->nodes->used_nodes_begin; \
        ex_pool_node_t *__node_begin__ = (_hashmap)->nodes->nodes; \
        ex_pool_node_t *__node_next__; \
        size_t __idx__; \
        _type _el; \
        void *__key__; \
        while ( __node__ ) { \
            __node_next__ = __node__->next; \
            __idx__ = __node__ - __node_begin__; \
            __key__ = ( (char *)(_hashmap)->keys + __idx__ * (_hashmap)->key_bytes ); \
            _el = *( (_type *) ( (char *)(_hashmap)->values + __idx__ * (_hashmap)->value_bytes ) );

// ------------------------------------------------------------------ 
/*! 
 @def ex_hashmap_each
 @param _hashmap the in hashmap
 @param _type the point-type of the value in the hashmap.
 @param _el the value variable you want to define.
 @details macro for easy iterates the hashmap container.

 when use the macro, it will define the local variable below:
 - __node__: the current node of the hashmap
 - __node_begin__: the the beginning of the node

 to finish the code, you must write ex_hashmap_each_end.

 Usage:
 @code
 ex_hashmap_t *my_hashmap = ex_hashmap_alloc( sizeof(int), sizeof(float), 10 );
 ex_hashmap_raw_each ( my_hashmap, float *, item ) {
    printf( "item is %f", *item );
 } ex_hashmap_each_end;
 @endcode
 @sa ex_hashmap_each_end
 @note DO NOT USE continue in this loop, use ex_hashmap_continue instead 
*/// ------------------------------------------------------------------ 

#define ex_hashmap_raw_each( _hashmap, _type, _el ) \
    { \
        ex_pool_node_t *__node__ = (_hashmap)->nodes->used_nodes_begin; \
        ex_pool_node_t *__node_begin__ = (_hashmap)->nodes->nodes; \
        ex_pool_node_t *__node_next__; \
        size_t __idx__; \
        _type _el; \
        while ( __node__ ) { \
            __node_next__ = __node__->next; \
            __idx__ = __node__ - __node_begin__; \
            __key__ = ( (char *)(_hashmap)->keys + __idx__ * (_hashmap)->key_bytes ); \
            _el = (_type)( (char *)(_hashmap)->values + __idx__ * (_hashmap)->value_bytes );

// ------------------------------------------------------------------ 
/*! 
 @def ex_hashmap_each_end
 @details macro to end the ex_hashmap_each, ex_hashmap_raw_each macro
 @sa ex_hashmap_each
 @sa ex_hashmap_raw_each
*/// ------------------------------------------------------------------ 

#define ex_hashmap_each_end \
            __node__ = __node_next__; \
        } \
    }

// ------------------------------------------------------------------ 
/*! 
 @def ex_hashmap_continue
 @details macro to let the continue work in each
 @sa ex_hashmap_each
 @sa ex_hashmap_raw_each
*/// ------------------------------------------------------------------ 

#define ex_hashmap_continue \
    { \
        __node__ = __node_next__; \
        continue; \
    }

///////////////////////////////////////////////////////////////////////////////
// decls
// the size of indices, keys, values is fixed when inited.
// the node pool is flexible.
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

//
typedef uint32 (*hashkey_t) (const void *);
typedef int (*keycmp_t) (const void *, const void *);

//
typedef struct ex_hashmap_node_t {
    size_t prev; // prev hash index
    size_t next; // next hash index
} ex_hashmap_node_t;

//
typedef struct ex_hashmap_t {
    // public
    size_t capacity;

    // private
    size_t hashsize;
    void *keys;
    size_t key_bytes;
    void *values;
    size_t value_bytes;
    size_t *indices;
    ex_pool_t *nodes;
    hashkey_t hashkey;
    keycmp_t keycmp;

    // alloc methods
    void *(*alloc)      ( size_t );
    void *(*realloc)    ( void *, size_t );
    void  (*dealloc)    ( void * );
} ex_hashmap_t;

// NOTE: in this way, we can still trace the memory leak.
static inline void *__ex_hashmap_alloc( size_t _size ) { return ex_malloc_tag ( _size, "ex_hashmap_t" ); }
static inline void *__ex_hashmap_realloc( void *_ptr, size_t _size ) { return ex_realloc_tag ( _ptr, _size, "ex_hashmap_t" ); }
static inline void  __ex_hashmap_dealloc( void *_ptr ) { ex_free ( _ptr ); }

static inline void *__ex_hashmap_alloc_nomng( size_t _size ) { return ex_malloc_nomng ( _size ); }
static inline void *__ex_hashmap_realloc_nomng( void *_ptr, size_t _size ) { return ex_realloc_nomng ( _ptr, _size ); }
static inline void  __ex_hashmap_dealloc_nomng( void *_ptr ) { ex_free_nomng ( _ptr ); }

// ------------------------------------------------------------------ 
// Desc: 
// ex_hashmap
// ex_hashmap_notype
// ------------------------------------------------------------------ 

extern ex_hashmap_t *ex_hashmap_alloc ( size_t _key_bytes, size_t _value_bytes, 
                                        size_t _count, 
                                        hashkey_t _hashkey, keycmp_t _keycmp );

// ex_hashset
#define ex_hashset(_type,_count) \
    ex_hashmap_alloc(EX_TYPEID(_type), EX_RTTI(_type)->size, \
                     EX_TYPEID(_type), EX_RTTI(_type)->size, \
                     _count, \
                     ex_hashkey_##_type, ex_keycmp_##_type \
                    )

// ex_hashmap
#define ex_hashmap(_key_type,_val_type,_count) \
    ex_hashmap_alloc(EX_TYPEID(_key_type), EX_RTTI(_key_type)->size, \
                     EX_TYPEID(_val_type), EX_RTTI(_val_type)->size, \
                     _count, \
                     ex_hashkey_##_key_type, ex_keycmp_##_key_type \
                    )

// ex_hashset_notype
#define ex_hashset_notype(_element_bytes,_count,_hashkey,_keycmp) \
    ex_hashmap_alloc(_element_bytes, \
                     _element_bytes, \
                     _count, \
                     _hashkey, _keycmp \
                    )

// ex_hashmap_notype
#define ex_hashmap_notype(_key_bytes,_val_bytes,_count,_hashkey,_keycmp) \
    ex_hashmap_alloc(_key_bytes, \
                     _val_bytes, \
                     _count, \
                     _hashkey, _keycmp \
                    )

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_hashmap_free ( ex_hashmap_t *_hashmap );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_hashmap_init ( ex_hashmap_t *_hashmap, 
                              size_t _key_bytes, size_t _value_bytes, 
                              size_t _count, 
                              hashkey_t _hashkey, keycmp_t _keycmp, 
                              void *(*_alloc) ( size_t ),
                              void *(*_realloc) ( void *, size_t ),
                              void  (*_dealloc) ( void * )
                            );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_hashmap_deinit ( ex_hashmap_t *_hashmap ); 


// ------------------------------------------------------------------ 
// Desc: 
// NOTE: this operation is deprecated, you need to check if the value 
//  exists then go for it.
// ------------------------------------------------------------------ 

extern void ex_hashmap_insert_new ( ex_hashmap_t *_hashmap, const void *_key, const void *_val, size_t _hash_idx, size_t *_index );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void *ex_hashmap_get ( const ex_hashmap_t *_hashmap, const void *_key, size_t *_index );
extern size_t ex_hashmap_get_hashidx ( const ex_hashmap_t *_hashmap, const void *_key, size_t *_index );
extern void *ex_hashmap_get_by_idx ( const ex_hashmap_t *_hashmap, size_t _index );

// ------------------------------------------------------------------ 
// Desc: 
//  @return: false: already exists
// ------------------------------------------------------------------ 

extern bool ex_hashmap_insert ( ex_hashmap_t *_hashmap, const void *_key, const void *_val, size_t *_index );
// set will still set the already exists value, insert new one
extern bool ex_hashmap_set ( ex_hashmap_t *_hashmap, const void *_key, const void *_val );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_hashmap_cpy ( ex_hashmap_t *_to, const ex_hashmap_t *_from );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void *ex_hashmap_remove_at ( ex_hashmap_t *_hashmap, const void *_key );
extern void *ex_hashmap_remove_by_idx ( ex_hashmap_t *_hashmap, uint32 _hash_idx, size_t _idx );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline size_t ex_hashmap_count ( const ex_hashmap_t *_hashmap ) { return ex_pool_count(_hashmap->nodes); }
static inline size_t ex_hashmap_capacity ( const ex_hashmap_t *_hashmap ) { return _hashmap->capacity; }

///////////////////////////////////////////////////////////////////////////////
// useful callback
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: useful hash functions 
// ------------------------------------------------------------------ 

static inline uint32 ex_hashkey_cstr ( const void *_val ) { return ex_hashstr( *((const char **)_val) ); }
// DISABLE can use ex_hashkey_string instead: static inline uint32 hashkey_wstring ( void *_val ) { return ex_hashstr_w( *((wchar_t **)_val) ); }
// static inline uint32 ex_hashkey_strid ( const void *_val ) { return *((const strid_t *)_val); }
static inline uint32 ex_hashkey_int ( const void *_val ) { return (uint32)(*((const int *)_val)); }
static inline uint32 ex_hashkey_uint32 ( const void *_val ) { return *((const uint32 *)_val); }
static inline uint32 ex_hashkey_uint64 ( const void *_val ) { return (uint32)(*((const uint64 *)_val)); }
static inline uint32 ex_hashkey_uid ( const void *_val ) { return (uint32)(*((const ex_uid_t *)_val)); }
static inline uint32 ex_hashkey_ptr ( const void *_val ) { return (uint32)((size_t)(*(const void **)_val) >> 4); }

// ------------------------------------------------------------------ 
// Desc: useful keycmp functions
// ------------------------------------------------------------------ 

static inline int ex_keycmp_cstr ( const void *_lhs, const void *_rhs ) { return strcmp ( *((const char **)_lhs), *((const char **)_rhs) ); }
// DISABLE can use ex_keycmp_string instead: static inline int keycmp_wstring ( void *_lhs, void *_rhs ) { return wcscmp ( *((wchar_t **)_lhs), *((wchar_t **)_rhs) ); }
// static inline int ex_keycmp_strid ( const void *_lhs, const void *_rhs ) { return *((const strid_t *)_lhs) - *((const strid_t *)_rhs); }
static inline int ex_keycmp_int ( const void *_lhs, const void *_rhs ) { return *((const int *)_lhs) - *((const int *)_rhs); }
static inline int ex_keycmp_uint32 ( const void *_lhs, const void *_rhs ) { return *((const uint32 *)_lhs) - *((const uint32 *)_rhs); }
static inline int ex_keycmp_uint64 ( const void *_lhs, const void *_rhs ) { uint64 re = *((const uint64 *)_lhs) - *((const uint64 *)_rhs); return re > 0 ? 1 : (re == 0 ? 0 : -1); }
static inline int ex_keycmp_uid ( const void *_lhs, const void *_rhs ) { ex_uid_t re = *((const ex_uid_t *)_lhs) - *((const ex_uid_t *)_rhs); return re > 0 ? 1 : (re == 0 ? 0 : -1); }
static inline int ex_keycmp_ptr ( const void *_lhs, const void *_rhs ) { return (size_t)*((const void **)_lhs) - (size_t)*((const void **)_rhs); }

// ######################### 
#ifdef __cplusplus
} // end extern "C"
#endif
// ######################### 

// #################################################################################
#endif // END HASHMAP_H_1277683404
// #################################################################################


