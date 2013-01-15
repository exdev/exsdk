// ======================================================================================
// File         : array.h
// Author       : Wu Jie 
// Last Change  : 07/07/2010 | 13:10:55 PM | Wednesday,July
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef ARRAY_H_1278479457
#define ARRAY_H_1278479457
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" {
#endif
// ######################### 

//! @defgroup Container

//! @defgroup ex_array_t dynamic array (like stl::vector)
//! @ingroup Container
//! @{

///////////////////////////////////////////////////////////////////////////////
// decls
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
/*! 
 @def ex_array_each
 @param _array the in array
 @param _type the type of the element in the array.
 @param _el the element variable you want to define.
 @details macro for easy iterates the array container.

 when use the macro, it will define the local variable below:
 - __idx__: the current index.

 to finish the code, you must write ex_array_each_end.

 Usage:
 @code
 ex_array_t* my_array = ex_array_notype( sizeof(float), 10 );
 ex_array_each ( my_array, float, item ) {
    printf( "item_%d is %f", __idx__, item );
 } ex_array_each_end;
 @endcode
 @sa ex_array_each_end
 @note DO NOT USE continue in this loop, use ex_array_continue instead 
*/// ------------------------------------------------------------------ 

#define ex_array_each( _array, _type, _el ) \
    { \
        _type _el; \
        size_t __idx__ = 0; \
        while ( __idx__ < (_array)->count ) { \
            _el = *( (_type *) ((_array)->data) + __idx__ );

// ------------------------------------------------------------------ 
/*! 
 @def ex_array_raw_each
 @param _array the in array
 @param _type the point-type of the element in the array.
 @param _el the element variable you want to define.
 @details macro for easy iterates the array container.

 when use the macro, it will define the local variable below:
 - __idx__: the current index.

 to finish the code, you must write ex_array_each_end.

 Usage:
 @code
 ex_array_t* my_array = ex_array_notype( sizeof(float), 10 );
 ex_array_raw_each ( my_array, float*, item ) {
    printf( "item_%d is %f", __idx__, *item );
 } ex_array_each_end;
 @endcode
 @sa ex_array_each_end
 @note DO NOT USE continue in this loop, use ex_array_continue instead 
*/// ------------------------------------------------------------------ 

#define ex_array_raw_each( _array, _type, _el ) \
    { \
        _type _el; \
        size_t __idx__ = 0; \
        while ( __idx__ < (_array)->count ) { \
            _el = (_type) ((_array)->data) + __idx__;

// ------------------------------------------------------------------ 
/*! 
 @def ex_array_each_end
 @details macro to end the ex_array_each, ex_array_raw_each macro
 @sa ex_array_each
 @sa ex_array_raw_each
*/// ------------------------------------------------------------------ 

#define ex_array_each_end \
            ++__idx__; \
        } \
    }

// ------------------------------------------------------------------ 
/*! 
 @def ex_array_continue
 @details macro to let the continue work in each
 @sa ex_array_each
 @sa ex_array_raw_each
*/// ------------------------------------------------------------------ 

#define ex_array_continue \
    { \
        ++__idx__; \
        continue; \
    }

// ------------------------------------------------------------------ 
/*! 
 @struct ex_array_t
 @details

 The data structure of dynamic array used in ex_array_ functions 
 
*/// ------------------------------------------------------------------ 

typedef struct ex_array_t {
    char *data;
    size_t element_bytes;
    size_t count;
    size_t capacity;

    // alloc methods
    void *(*alloc)      ( size_t );
    void *(*realloc)    ( void *, size_t );
    void  (*dealloc)    ( void * );
} ex_array_t;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern ex_array_t *ex_array_alloc ( size_t _element_bytes, size_t _count );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_array_free ( ex_array_t *_array );

// ------------------------------------------------------------------ 
// Desc: 
// NOTE: if you want to create a no-manager array, do it like this:
// ex_array_t *arr = ex_malloc_nomng ( sizeof(ex_array_t) );
// ex_array_init ( arr, _element_typeid, _element_bytes, _count,
//                 ex_func_alloc_nomng,
//                 ex_func_realloc_nomng,
//                 ex_func_dealloc_nomng
//               );
// ex_array_deinit(arr);
// ex_free_nomng(arr)
// ------------------------------------------------------------------ 

extern void ex_array_init ( ex_array_t *_array, 
                            size_t _element_bytes, 
                            size_t _count,
                            void *(*_alloc) ( size_t ),
                            void *(*_realloc) ( void *, size_t ),
                            void  (*_dealloc) ( void * ) );

// ------------------------------------------------------------------ 
/*! 
 @fn void ex_array_deinit ( ex_array_t *_array )
 @param _array the in array.
 @details destroy the data in the array, release the memory ( not including the array )
 @note you need to free the array by your self
*/// ------------------------------------------------------------------ 

extern void ex_array_deinit ( ex_array_t *_array );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_array_set ( ex_array_t *_array, size_t _idx, const void *_value );

// ------------------------------------------------------------------ 
/*! 
 @fn void *ex_array_get ( const ex_array_t *_array, size_t _idx )
 @param _array the in array.
 @param _idx the element index
 @return get the element pointer address
 @details get the array element by index

 Example:
 @code
 float *result = NULL;
 // create an array to store float, the default size is 10.
 ex_array_t *my_array = ex_array_notype ( sizeof(float), 10 );
 ex_array_add_float ( my_array, 10.0f ); // push at index 0
 ex_array_add_float ( my_array, 20.0f ); // push at index 1
 ex_array_add_float ( my_array, 30.0f ); // push at index 2
 ex_array_add_float ( my_array, 40.0f ); // push at index 3
 result = (float *)ex_array_get ( my_array, 1 ); // get from index 1
 printf( "the result is %f", *result ); // the result is 20.0f
 @endcode

 @note you must cast the type of the element by yourself.
*/// ------------------------------------------------------------------ 

extern void *ex_array_get ( const ex_array_t *_array, size_t _idx );

// ------------------------------------------------------------------ 
/*! 
 @fn static inline size_t ex_array_count ( ex_array_t *_array )
 @param _array the in array
 @details get the array element count.
*/// ------------------------------------------------------------------ 

static inline size_t ex_array_count ( const ex_array_t *_array ) { return _array->count; } 

// ------------------------------------------------------------------ 
/*! 
 @fn void *ex_array_add ( ex_array_t *_array, void *_value )
 @param _array the in array.
 @param _value the value add to the array
 @return the pointer address of the added element in the array
 @details add the value to the array, the array will copy the value through
 the parameter _value by allocating it in the passing array use exsdk's
 memory manage method. 

 Example:
 @code
 float *result;
 float val = 10.0f;
 // create an array to store float, the default size is 10.
 ex_array_t *my_array = ex_array_notype ( sizeof(float), 10 );
 {
     float val = 10.0f;
     result = (float *)ex_array_add ( my_array, &val );
 }
 printf( "the result is %f", *result ); // the result is 10.0f
 @endcode
*/// ------------------------------------------------------------------ 

extern void *ex_array_add ( ex_array_t *_array, const void *_value );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void *ex_array_add_range ( ex_array_t *_array, const void *_data, size_t _count );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void *ex_array_insert ( ex_array_t *_array, size_t _idx, const void *_value );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void *ex_array_insert_range ( ex_array_t *_array, size_t _idx, const void *_data, size_t _count );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_array_ncpy ( ex_array_t *_to, const void *_buf, size_t _count );
static inline void ex_array_cpy ( ex_array_t *_to, const ex_array_t *_from ) {
    ex_assert ( _to->element_bytes == _from->element_bytes );
    ex_array_ncpy ( _to, _from->data, _from->count );
}

// ------------------------------------------------------------------ 
/*! 
 @fn void ex_array_remove_at ( ex_array_t *_array, size_t _idx )
 @param _array the in array
 @param _idx the remove element index. 
 @details remove the element by index.
 @sa ex_array_remove_at_fast
*/// ------------------------------------------------------------------ 

extern void ex_array_remove_at ( ex_array_t *_array, size_t _idx );

// ------------------------------------------------------------------ 
/*! 
 @fn void ex_array_remove_at_fast ( ex_array_t *_array, size_t _idx )
 @param _array the in array
 @param _idx the remove element index. 
 @details remove the element by index. the method will move the last
 element to the removed element adress, which make it faster than \ref
 ex_array_remove_at.
 @note using the method will break the indexing order in the array.
 @sa ex_array_remove_at
*/// ------------------------------------------------------------------ 

extern void ex_array_remove_at_fast ( ex_array_t *_array, size_t _idx );

// ------------------------------------------------------------------ 
/*! 
 @fn void ex_array_remove_range ( ex_array_t *_array, size_t _idx, size_t _count )
 @param _array the in array
 @param _idx the start index to remove
 @param _count the count of element to remove
 @details remove n count of element from index i
*/// ------------------------------------------------------------------ 

extern void ex_array_remove_range ( ex_array_t *_array, size_t _idx, size_t _count );

// ------------------------------------------------------------------ 
/*! 
 @fn void ex_array_remove_all ( ex_array_t *_array )
 @param _array the in array
 @details remove all elements in the array. This is very fast, because 
 it won't do anything but just set the array count to zero. 
*/// ------------------------------------------------------------------ 

extern void ex_array_remove_all ( ex_array_t *_array );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// TODO:
extern void ex_array_shrink ( ex_array_t *_array );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_array_sort( ex_array_t *_array, int (*_cmp)(const void *, const void *) );

//! @}

// ######################### 
#ifdef __cplusplus
} // end extern "C"
#endif
// ######################### 

// #################################################################################
#endif // END ARRAY_H_1278479457
// #################################################################################


