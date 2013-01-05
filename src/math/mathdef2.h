// ======================================================================================
// File         : mathdef2.h
// Author       : Wu Jie 
// Last Change  : 01/25/2011 | 01:34:54 AM | Tuesday,January
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MATHDEF2_H_1295890496
#define MATHDEF2_H_1295890496
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" { 
#endif
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// extern
///////////////////////////////////////////////////////////////////////////////

extern const ex_vec2f_t ex_vec2f_zero;
extern const ex_vec2f_t ex_vec2f_one;

extern const ex_vec3f_t ex_vec3f_zero;
extern const ex_vec3f_t ex_vec3f_one;

extern const ex_vec4f_t ex_vec4f_zero;
extern const ex_vec4f_t ex_vec4f_one;

extern const ex_mat22f_t ex_mat22f_zero;
extern const ex_mat22f_t ex_mat22f_identity;

extern const ex_mat33f_t ex_mat33f_zero;
extern const ex_mat33f_t ex_mat33f_identity;

extern const ex_mat44f_t ex_mat44f_zero;
extern const ex_mat44f_t ex_mat44f_identity;

extern const ex_quatf_t ex_quatf_zero;
extern const ex_quatf_t ex_quatf_identity;

extern const ex_angf_t ex_angf_zero;

///////////////////////////////////////////////////////////////////////////////
// macro
///////////////////////////////////////////////////////////////////////////////

// UNUSED { 
// #define EX_VEC2F_ZERO       0.0f,0.0f
// #define EX_VEC2F_ONE        1.0f,1.0f

// #define EX_VEC3F_ZERO       0.0f,0.0f,0.0f
// #define EX_VEC3F_ONE        1.0f,1.0f,1.0f

// #define EX_VEC4F_ZERO       0.0f,0.0f,0.0f,0.0f
// #define EX_VEC4F_ONE        1.0f,1.0f,1.0f,1.0f

// #define EX_MAT22F_ZERO      0.0f,0.0f,0.0f,0.0f
// #define EX_MAT22F_IDENTITY  1.0f,0.0f,1.0f,0.0f

// #define EX_MAT33F_ZERO      0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
// #define EX_MAT33F_IDENTITY  1.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,1.0f

// #define EX_MAT44F_ZERO      0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
// #define EX_MAT44F_IDENTITY  1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f

// #define EX_QUATF_ZERO       0.0f,0.0f,0.0f,0.0f
// #define EX_QUATF_IDENTITY   0.0f,0.0f,0.0f,1.0f

// #define EX_ANGF_ZERO        0.0f
// } UNUSED end 

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 


// #################################################################################
#endif // END MATHDEF2_H_1295890496
// #################################################################################
