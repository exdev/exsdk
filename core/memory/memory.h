// ======================================================================================
// File         : memory.h
// Author       : Wu Jie 
// Last Change  : 06/26/2010 | 13:25:37 PM | Saturday,June
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MEMORY_H_1277529938
#define MEMORY_H_1277529938
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" {
#endif
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// config
///////////////////////////////////////////////////////////////////////////////

#define EX_MEM_ALIGN 16

///////////////////////////////////////////////////////////////////////////////
// private memory functions
///////////////////////////////////////////////////////////////////////////////

extern void *ex_malloc_mng( size_t _size, const char *_tag, const char *_file_name, const char *_func_name, size_t _line_nr );
extern void *ex_realloc_mng( void *_ptr, size_t _size, const char *_tag, const char *_file_name, const char *_func_name, size_t _line_nr );
extern void ex_free_mng( void *_ptr, const char *_file_name, const char *_func_name, size_t _line_nr );

///////////////////////////////////////////////////////////////////////////////
// memory mng
///////////////////////////////////////////////////////////////////////////////

// success: 0
// already inited: 1
// failed: -1
extern int ex_mem_init ();
extern void ex_mem_deinit ();
extern bool ex_mem_initialized ();

///////////////////////////////////////////////////////////////////////////////
// global namespace function declaration & define 
///////////////////////////////////////////////////////////////////////////////

// -----------------------------------
#ifndef EX_USE_DL_MALLOC
// -----------------------------------

    // malloc
    #define ex_malloc_nomng( size )                         malloc(size)
    #define ex_malloc( size )                               malloc(size)
    #define ex_malloc_tag( size, tag )                      malloc(size)

    // realloc
    #define ex_realloc_nomng( ptr, size )                   realloc(ptr,size)
    #define ex_realloc( ptr, size )                         realloc(ptr,size)
    #define ex_realloc_tag( ptr, size, tag )                realloc(ptr,size)

    // free
    #define ex_free_nomng( ptr )                            free(ptr)
    #define ex_free( ptr )                                  free(ptr)

// -----------------------------------
#else // use managed memory
// -----------------------------------

///////////////////////////////////////////////////////////////////////////////
// ex_malloc
///////////////////////////////////////////////////////////////////////////////

#define ex_malloc_nomng( size )             dlmemalign( EX_MEM_ALIGN, size)

#ifdef EX_USE_MEMORY_MANAGER
    #define ex_malloc( size )                               ex_malloc_mng( size, "default", __FILE__, __FUNCTION__, __LINE__ )
    #define ex_malloc_tag( size, tag )                      ex_malloc_mng( size, tag, __FILE__, __FUNCTION__, __LINE__ ) 
#else
    #define ex_malloc( size )                               ex_malloc_nomng( size )
    #define ex_malloc_tag( size, tag )                      ex_malloc_nomng( size )
#endif

///////////////////////////////////////////////////////////////////////////////
// ex_realloc
///////////////////////////////////////////////////////////////////////////////

#define ex_realloc_nomng( ptr, size )       dlrealloc(ptr,size)

#ifdef EX_USE_MEMORY_MANAGER
    #define ex_realloc( ptr, size )                             ex_realloc_mng( ptr, size, "default", __FILE__, __FUNCTION__, __LINE__ )
    #define ex_realloc_tag( ptr, size, tag )                    ex_realloc_mng( ptr, size, tag, __FILE__, __FUNCTION__, __LINE__ )
#else
    #define ex_realloc( ptr, size )                             ex_realloc_nomng( ptr, size )
    #define ex_realloc_tag( ptr, size, tag )                    ex_realloc_nomng( ptr, size ) 
#endif

///////////////////////////////////////////////////////////////////////////////
// free
///////////////////////////////////////////////////////////////////////////////

// ========================================================
// free
// ========================================================

#define ex_free_nomng( ptr )                dlfree( ptr )

#ifdef EX_USE_MEMORY_MANAGER
    #define ex_free( ptr )                                  ex_free_mng( ptr, __FILE__, __FUNCTION__, __LINE__ )
#else
    #define ex_free( ptr )                                  ex_free_nomng( ptr )
#endif

// -----------------------------------
#endif // end if EX_USE_SYSTEM_MEMORY
// -----------------------------------

// ex_safe_free_nomng
#define ex_safe_free_nomng(ptr) \
    if ( ptr ) { \
        ex_free_nomng(ptr); \
        ptr = NULL; \
    }

// ex_safe_free
#define ex_safe_free( ptr ) \
    if ( ptr ) { \
        ex_free(ptr); \
        ptr = NULL; \
    }

///////////////////////////////////////////////////////////////////////////////
// ex_stack_malloc
///////////////////////////////////////////////////////////////////////////////

#define EX_HAVE_ALLOCA 1

#if EX_HAVE_ALLOCA
    #define ex_stack_malloc(size)     alloca(size)
    #define ex_stack_free(ptr)
#else
    #define ex_stack_malloc(size)     ex_malloc(size)
    #define ex_stack_free(ptr)        ex_free(ptr)
#endif

///////////////////////////////////////////////////////////////////////////////
// common memory operations
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void *ex_memzero ( void *_ptr, size_t _size ) { 
    return memset ( _ptr, 0x00, _size ); 
}

// ------------------------------------------------------------------
// Desc: mem swap
// ------------------------------------------------------------------

// TODO { 
// static inline void memswap( void *_p1, void *_p2, size_t _size ) {
    // void *pTmp = ex_stack_malloc(EX_ALIGN_ROUND(_size,EX_DEFAULT_ALIGNMENT));

    // memcpy( pTmp, _p1,  _size );
    // memcpy( _p1,  _p2,  _size );
    // memcpy( _p2,  pTmp, _size );
// }
// } TODO end 

// ------------------------------------------------------------------ 
// Desc: NOTE: this is for container nomng memory api uses ( such as array, list, ....) 
// ------------------------------------------------------------------ 

static inline void *ex_func_alloc_nomng ( size_t _size ) { return ex_malloc_nomng ( _size ); }
static inline void *ex_func_realloc_nomng ( void *_ptr, size_t _size ) { return ex_realloc_nomng ( _ptr, _size ); }
static inline void  ex_func_dealloc_nomng ( void *_ptr ) { ex_free_nomng ( _ptr ); }

static inline void *ex_func_alloc ( size_t _size ) { return ex_malloc ( _size ); }
static inline void *ex_func_realloc ( void *_ptr, size_t _size ) { return ex_realloc ( _ptr, _size ); }
static inline void  ex_func_dealloc ( void *_ptr ) { ex_free ( _ptr ); }

///////////////////////////////////////////////////////////////////////////////
// debugs
///////////////////////////////////////////////////////////////////////////////

size_t ex_total_org_memory ();
size_t ex_total_dbg_memory ();
size_t ex_accumulate_org_memory ();
size_t ex_accumulate_dbg_memory ();

size_t ex_total_dl_memory ();

// ######################### 
#ifdef __cplusplus
} // end extern "C"
#endif
// ######################### 

// #################################################################################
#endif // END MEMORY_H_1277529938
// #################################################################################


