// ======================================================================================
// File         : circlef.h
// Author       : Wu Jie 
// Last Change  : 01/08/2011 | 22:48:07 PM | Saturday,January
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef CIRCLEF_H_1294498089
#define CIRCLEF_H_1294498089
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" { 
#endif
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// struct
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: ex_circlef_t 
// ------------------------------------------------------------------ 

typedef struct ex_circlef_t {
    ex_vec2f_t center;
    float radius;
} ex_circlef_t;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_circlef_set ( ex_circlef_t *_r, 
                                    ex_vec2f_t _center, 
                                    float _radius ) 
{ 
    _r->center = _center;
    _r->radius = _radius;
}

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 


// #################################################################################
#endif // END CIRCLEF_H_1294498089
// #################################################################################

