// ======================================================================================
// File         : ptr.h
// Author       : Wu Jie 
// Last Change  : 06/30/2010 | 10:08:31 AM | Wednesday,June
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef PTR_H_1277863712
#define PTR_H_1277863712
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" { 
#endif
// ######################### 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void *ex_ptr_add ( void *_ptr, size_t _offset ) { return (void *)((size_t)_ptr + _offset); }
static inline void *ex_ptr_sub ( void *_ptr, size_t _offset ) { return (void *)((size_t)_ptr - _offset); }
static inline size_t ex_ptr_diff ( void *_lhs, void *_rhs ) { return (size_t)_lhs - (size_t)_rhs; }
static inline size_t ex_ptr_to_addr ( void *_ptr ) { return (size_t)_ptr; }
static inline void *ex_addr_to_ptr ( size_t _addr ) { return (void *)_addr; }

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 


// #################################################################################
#endif // END PTR_H_1277863712
// #################################################################################


