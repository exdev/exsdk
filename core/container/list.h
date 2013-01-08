// ======================================================================================
// File         : list.h
// Author       : Wu Jie 
// Last Change  : 06/29/2010 | 17:54:26 PM | Tuesday,June
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef LIST_H_1277805267
#define LIST_H_1277805267
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" {
#endif
// ######################### 

// ------------------------------------------------------------------ 
/*! 
 @def ex_list_each
 @param _list the in list
 @param _type the type of the value in the list.
 @param _el the value variable you want to define.
 @details macro for easy iterates the hashmap container.

 when use the macro, it will define the local variable below:
 - __node__: the current node of the list
 - __idx__: the index

 to finish the code, you must write ex_list_each_end.

 Usage:
 @code
 ex_list_t *my_list = ex_list_alloc( sizeof(float), 10 );
 ex_list_each ( my_list, float, item ) {
    printf( "item_%d is %f", __idx__, item );
 } ex_list_each_end;
 @endcode
 @sa ex_list_each_end
 @note DO NOT USE continue in this loop, use ex_list_continue instead 
*/// ------------------------------------------------------------------ 

#define ex_list_each( _list, _type, _el ) \
    { \
        ex_list_node_t *__node__ = (_list)->head; \
        ex_list_node_t *__node_next__; \
        int __idx__ = 0; \
        _type _el; \
        while ( __node__ ) { \
            __node_next__ = __node__->next; \
            _el = *( (_type *) ( __node__->value ) );

// ------------------------------------------------------------------ 
/*! 
 @def ex_list_raw_each
 @param _list the in list
 @param _type the type of the value in the list.
 @param _el the value variable you want to define.
 @details macro for easy iterates the hashmap container.

 when use the macro, it will define the local variable below:
 - __node__: the current node of the list
 - __idx__: the index

 to finish the code, you must write ex_list_each_end.

 Usage:
 @code
 ex_list_t *my_list = ex_list_alloc( sizeof(float), 10 );
 ex_list_raw_each ( my_list, float *, item ) {
    printf( "item_%d is %f", __idx__, *item );
 } ex_list_each_end;
 @endcode
 @sa ex_list_each_end
 @note DO NOT USE continue in this loop, use ex_list_continue instead 
*/// ------------------------------------------------------------------ 

#define ex_list_raw_each( _list, _type, _el ) \
    { \
        ex_list_node_t *__node__ = (_list)->head; \
        ex_list_node_t *__node_next__; \
        int __idx__ = 0; \
        _type _el; \
        while ( __node__ ) { \
            __node_next__ = __node__->next; \
            _el = (_type) ( __node__->value );

// ------------------------------------------------------------------ 
/*! 
 @def ex_list_each_end
 @details macro to end the ex_list_each, ex_list_raw_each macro
 @sa ex_list_each
 @sa ex_list_raw_each
*/// ------------------------------------------------------------------ 

#define ex_list_each_end \
            ++__idx__; \
            __node__ = __node_next__; \
        } \
    }

// ------------------------------------------------------------------ 
/*! 
 @def ex_list_continue
 @details macro to let the continue work in each
 @sa ex_list_each
 @sa ex_list_raw_each
*/// ------------------------------------------------------------------ 

#define ex_list_continue \
    { \
        ++__idx__; \
        __node__ = __node_next__; \
        continue; \
    }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// when allocate the node, it actually allocate the a memory block which the
// size is equal to the size of the node plus the size of the value store in the node.
// then it assign the address of the value to the node->value in the node. 

typedef struct ex_list_node_t {
    void *value;
    struct ex_list_node_t *prev;
    struct ex_list_node_t *next;
} ex_list_node_t;

//
typedef struct ex_list_t {
    // private
    size_t count;
    size_t element_bytes;
    ex_list_node_t *head;
    ex_list_node_t *tail;

    // alloc methods
    void *(*alloc)      ( size_t );
    void *(*realloc)    ( void *, size_t );
    void  (*dealloc)    ( void * );
} ex_list_t;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern ex_list_t *ex_list_alloc ( size_t _element_bytes );
#define ex_list(_type) ex_list_alloc( sizeof(_type) )

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_list_free ( ex_list_t *_list );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_list_init ( ex_list_t *_list, 
                           size_t _element_bytes, 
                           void *(*_alloc) ( size_t ),
                           void *(*_realloc) ( void *, size_t ),
                           void  (*_dealloc) ( void * )
                         );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_list_deinit ( ex_list_t *_list ); 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_list_append ( ex_list_t *_list, const void *_value );
extern void ex_list_prepend ( ex_list_t *_list, const void *_value );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_list_insert_back ( ex_list_t *_list, ex_list_node_t *_at, const void *_value );
extern void ex_list_insert_front ( ex_list_t *_list, ex_list_node_t *_at, const void *_value );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern ex_list_node_t *ex_list_remove_at ( ex_list_t *_list, ex_list_node_t *_at );
static inline ex_list_node_t *ex_list_pop_front ( ex_list_t *_list ) {
    return ex_list_remove_at ( _list, _list->head );
}
static inline ex_list_node_t *ex_list_pop_back ( ex_list_t *_list ) {
    return ex_list_remove_at ( _list, _list->tail );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// TODO { 
extern void ex_list_cpy ( ex_list_t *_to, ex_list_t *_from );
// } TODO end 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline size_t ex_list_count ( const ex_list_t *_list ) { return _list->count; }
static inline ex_list_node_t *ex_list_head ( const ex_list_t *_list ) { return _list->head; }
static inline ex_list_node_t *ex_list_tail ( const ex_list_t *_list ) { return _list->tail; }

// ######################### 
#ifdef __cplusplus
} // end extern "C"
#endif
// ######################### 

// #################################################################################
#endif // END LIST_H_1277805267
// #################################################################################


