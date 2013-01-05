// ======================================================================================
// File         : mat44f.h
// Author       : Wu Jie 
// Last Change  : 11/12/2010 | 13:38:33 PM | Friday,November
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MAT44F_H_1289540317
#define MAT44F_H_1289540317
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "vec4f.h"

// ######################### 
#ifdef __cplusplus
extern "C" { 
#endif
// ######################### 

//! @defgroup ex_mat44f_t matrix 4x4 float
//! @ingroup Math
//! @{

// ------------------------------------------------------------------ 
/*! 
 @struct ex_mat44f_t
 @details
 
 The data of matrix 4x4 is construct by an union structure with float elements.\n
 The matrix can be expressed in formular as:
 
 \f$
   \left[\begin{array}{ c c c c }
   m_{00} & m_{01} & m_{02} & m_{03} \\
   m_{10} & m_{11} & m_{12} & m_{13} \\
   m_{20} & m_{21} & m_{22} & m_{23} \\
   m_{30} & m_{31} & m_{32} & m_{33}
   \end{array} \right]
 \f$
 
 and in array as:

 \f$
   \left[\begin{array}{ c c c c c c c c c c c c c c c c}
   m_{00}, m_{01}, m_{02}, m_{03}, m_{10}, m_{11}, m_{12}, m_{13}, 
   m_{20}, m_{21}, m_{22}, m_{23}, m_{30}, m_{31}, m_{32}, m_{33}
   \end{array} \right]
 \f$
*/// ------------------------------------------------------------------ 

typedef struct ex_mat44f_t {
    union {
        struct { 
            float m00, m01, m02, m03;
            float m10, m11, m12, m13;
            float m20, m21, m22, m23;
            float m30, m31, m32, m33;
        }; // end struct
        float m[16];
    };
} ex_mat44f_t;

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat44f_set ( ex_mat44f_t *_m, 
                         float _m00, float _m01, float _m02, float _m03,
                         float _m10, float _m11, float _m12, float _m13,
                         float _m20, float _m21, float _m22, float _m23,
                         float _m30, float _m31, float _m32, float _m33 )
 @retval _m the result matrix
 @param _m00
 @param _m01
 @param _m02
 @param _m03
 @param _m10
 @param _m11
 @param _m12
 @param _m13
 @param _m20
 @param _m21
 @param _m22
 @param _m23
 @param _m30
 @param _m31
 @param _m32
 @param _m33
 @details set the matrix _m by rest of the parameters:

 \f[
   m = \left[\begin{array}{ c c c c }
   \_m_{00} & \_m_{01} & \_m_{02} & \_m_{03} \\
   \_m_{10} & \_m_{11} & \_m_{12} & \_m_{13} \\
   \_m_{20} & \_m_{21} & \_m_{22} & \_m_{23} \\
   \_m_{30} & \_m_{31} & \_m_{32} & \_m_{33}
   \end{array} \right]
 \f]
*/// ------------------------------------------------------------------ 

static inline void ex_mat44f_set ( ex_mat44f_t *_m, 
                         float _m00, float _m01, float _m02, float _m03,
                         float _m10, float _m11, float _m12, float _m13,
                         float _m20, float _m21, float _m22, float _m23,
                         float _m30, float _m31, float _m32, float _m33 ) { 
    _m->m00 = _m00, _m->m01 = _m01, _m->m02 = _m02, _m->m03 = _m03;
    _m->m10 = _m10, _m->m11 = _m11, _m->m12 = _m12, _m->m13 = _m13; 
    _m->m20 = _m20, _m->m21 = _m21, _m->m22 = _m22, _m->m23 = _m23; 
    _m->m30 = _m30, _m->m31 = _m31, _m->m32 = _m32, _m->m33 = _m33; 
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline static inline float ex_mat44f_m_get ( ex_mat44f_t *_m, uint _row, uint _col ) 
 @param _m the matrix
 @param _row the row index, range in [0,4)
 @param _col the col index, range in [0,4)
 @return result
 @details get the matrix element in (_row, _col)
*/// ------------------------------------------------------------------ 

static inline float ex_mat44f_m_get ( const ex_mat44f_t *_m, uint _row, uint _col ) { 
    ex_assert( _row >= 0 && _row < 4, "out of range" );
    ex_assert( _col >= 0 && _col < 4, "out of range" );
    return _m->m[4*_row+_col];
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat44f_m_set ( ex_mat33f_t *_m, uint _row, uint _col, float _v ) 
 @param _m the matrix
 @param _row the row index, range in [0,4)
 @param _col the col index, range in [0,4)
 @param _v the in value
 @return result
 @details get the matrix element in (_row, _col)
*/// ------------------------------------------------------------------ 

static inline void ex_mat44f_m_set ( ex_mat44f_t *_m, uint _row, uint _col, float _v ) { 
    ex_assert( _row >= 0 && _row < 4, "out of range" );
    ex_assert( _col >= 0 && _col < 4, "out of range" );
    _m->m[4*_row+_col] = _v;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat44f_row ( ex_vec4f_t *_r, const ex_mat44f_t *_m, uint _row )
 @retval _r the result vector
 @param _m the matrix
 @param _row the row index, range in [0,4)
 @details get the matrix by _row and return it in vector4, for example: 
 @code
 ex_vec4f_t r;
 ex_mat44f_t m = ex_mat44f_zero;
 mat44f_row( &r, &m, 0 ); // set r to row 0 as -- (m.m00, m.m01, m.m02, m.m03)
 @endcode
 the r is equal to vector4 (m.m00, m.m01, m.m02, m.m03) 
*/// ------------------------------------------------------------------ 

static inline void ex_mat44f_row ( ex_vec4f_t *_r, const ex_mat44f_t *_m, uint _row ) {
    ex_assert( _row >= 0 && _row < 4, "out of range" );
    _r->x = _m->m[4*_row+0]; 
    _r->y = _m->m[4*_row+1]; 
    _r->z = _m->m[4*_row+2]; 
    _r->w = _m->m[4*_row+3]; 
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat44f_col ( ex_vec4f_t *_r, const ex_mat44f_t *_m, uint _col )
 @retval _r the result vector
 @param _m the matrix
 @param _col the column index, range in [0,4)
 @details get the matrix by _row and return it in vector3, for example: 
 @code
 ex_vec4f_t r;
 ex_mat44f_t m = ex_mat44f_zero;
 mat44f_col( &r, &m, 0 ); // set r to column 0 as -- (m.m00, m.m10, m.m20, m.m30)
 @endcode
 the r is equal to vector4 (m.m00, m.m10, m.m20, m.m30) 
*/// ------------------------------------------------------------------ 

static inline void ex_mat44f_col ( ex_vec4f_t *_r, const ex_mat44f_t *_m, uint _col ) {
    ex_assert( _col >= 0 && _col < 4, "out of range" );
    _r->x = _m->m[4*0+_col]; 
    _r->y = _m->m[4*1+_col]; 
    _r->z = _m->m[4*2+_col]; 
    _r->w = _m->m[4*3+_col]; 
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat44f_neg ( ex_mat44f_t *_m )
 @param _m in matrix
 @retval _m the result matrix
 @details get the negtive value from matrix _m, override and return it as the result:

 \f[
   \_m =
   -\left[\begin{array}{ c c c c }
   m_{00} & m_{01} & m_{02} & m_{03} \\
   m_{10} & m_{11} & m_{12} & m_{13} \\
   m_{20} & m_{21} & m_{22} & m_{23} \\
   m_{30} & m_{31} & m_{32} & m_{33}
   \end{array} \right]
   = 
   \left[\begin{array}{ c c c c }
   -m_{00} & -m_{01} & -m_{02} & -m_{03} \\
   -m_{10} & -m_{11} & -m_{12} & -m_{13} \\
   -m_{20} & -m_{21} & -m_{22} & -m_{23} \\
   -m_{30} & -m_{31} & -m_{32} & -m_{33}
   \end{array} \right]
 \f]
 @sa mat44f_get_neg
*/// ------------------------------------------------------------------ 

static inline void ex_mat44f_neg ( ex_mat44f_t *_m ) {
    _m->m00 = -_m->m00, _m->m01 = -_m->m01, _m->m02 = -_m->m02, _m->m03 = -_m->m03; 
    _m->m10 = -_m->m10, _m->m11 = -_m->m11, _m->m12 = -_m->m12, _m->m13 = -_m->m13; 
    _m->m20 = -_m->m20, _m->m21 = -_m->m21, _m->m22 = -_m->m22, _m->m23 = -_m->m23; 
    _m->m30 = -_m->m30, _m->m31 = -_m->m31, _m->m32 = -_m->m32, _m->m33 = -_m->m33; 
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat44f_get_neg ( const ex_mat44f_t *_m, ex_mat44f_t *_r )
 @retval _r the result matrix
 @param _m in matrix
 @details get the negtive value from matrix _m and set it in matrix _r.
 @sa mat44f_neg
*/// ------------------------------------------------------------------ 

static inline void ex_mat44f_get_neg ( const ex_mat44f_t *_m, ex_mat44f_t *_r ) {
    ex_assert ( _r != _m, "can't use self as return value." );
    _r->m00 = -_m->m00, _r->m01 = -_m->m01, _r->m02 = -_m->m02, _r->m03 = -_m->m03; 
    _r->m10 = -_m->m10, _r->m11 = -_m->m11, _r->m12 = -_m->m12, _r->m13 = -_m->m13; 
    _r->m20 = -_m->m20, _r->m21 = -_m->m21, _r->m22 = -_m->m22, _r->m23 = -_m->m23; 
    _r->m30 = -_m->m30, _r->m31 = -_m->m31, _r->m32 = -_m->m32, _r->m33 = -_m->m33; 
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat44f_abs ( ex_mat44f_t *_m )
 @param _m in matrix
 @retval _m the result matrix
 @details get the absolute value from matrix _m, override and return it as the result:

 \f[
   \_m = |Mat_m| = 
   \left|\begin{array}{ c c c c }
   m_{00} & m_{01} & m_{02} & m_{03} \\
   m_{10} & m_{11} & m_{12} & m_{13} \\
   m_{20} & m_{21} & m_{22} & m_{23} \\
   m_{30} & m_{31} & m_{32} & m_{33}
   \end{array} \right|
   =
   \left[\begin{array}{ c c c c }
   |m_{00}| & |m_{01}| & |m_{02}| & |m_{03}| \\
   |m_{10}| & |m_{11}| & |m_{12}| & |m_{13}| \\
   |m_{20}| & |m_{21}| & |m_{22}| & |m_{23}| \\
   |m_{30}| & |m_{31}| & |m_{32}| & |m_{33}|
   \end{array} \right]
 \f]
 @sa mat44f_get_abs
*/// ------------------------------------------------------------------ 

static inline void ex_mat44f_abs ( ex_mat44f_t *_m ) {
    _m->m00 = fabsf(_m->m00), _m->m01 = fabsf(_m->m01), _m->m02 = fabsf(_m->m02), _m->m03 = fabsf(_m->m03); 
    _m->m10 = fabsf(_m->m10), _m->m11 = fabsf(_m->m11), _m->m12 = fabsf(_m->m12), _m->m13 = fabsf(_m->m13); 
    _m->m20 = fabsf(_m->m20), _m->m21 = fabsf(_m->m21), _m->m22 = fabsf(_m->m22), _m->m23 = fabsf(_m->m23); 
    _m->m30 = fabsf(_m->m30), _m->m31 = fabsf(_m->m31), _m->m32 = fabsf(_m->m32), _m->m33 = fabsf(_m->m33); 
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat44f_get_abs ( const ex_mat44f_t *_m, ex_mat44f_t *_r )
 @retval _r the result matrix
 @param _m in matrix
 @details get the absolute value from matrix _m and set it in matrix _r as the result:
 @sa mat44f_abs
*/// ------------------------------------------------------------------ 

static inline void ex_mat44f_get_abs ( const ex_mat44f_t *_m, ex_mat44f_t *_r ) {
    ex_assert ( _r != _m, "can't use self as return value." );
    _r->m00 = fabsf(_m->m00), _r->m01 = fabsf(_m->m01), _r->m02 = fabsf(_m->m02), _r->m03 = fabsf(_m->m03); 
    _r->m10 = fabsf(_m->m10), _r->m11 = fabsf(_m->m11), _r->m12 = fabsf(_m->m12), _r->m13 = fabsf(_m->m13); 
    _r->m20 = fabsf(_m->m20), _r->m21 = fabsf(_m->m21), _r->m22 = fabsf(_m->m22), _r->m23 = fabsf(_m->m23); 
    _r->m30 = fabsf(_m->m30), _r->m31 = fabsf(_m->m31), _r->m32 = fabsf(_m->m32), _r->m33 = fabsf(_m->m33); 
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat44f_add ( ex_mat44f_t *_r, const ex_mat44f_t *_lhs, const ex_mat44f_t *_rhs )
 @retval _r the result matrix
 @param _lhs left hand side matrix 
 @param _rhs right hand side matrix 
 @details
 \f[
   \_r = Mat_a + Mat_b = 
   \left[\begin{array}{ c c c c }
   a_{00} & a_{01} & a_{02} & a_{03} \\
   a_{10} & a_{11} & a_{12} & a_{13} \\
   a_{20} & a_{21} & a_{22} & a_{23} \\
   a_{30} & a_{31} & a_{32} & a_{33}
   \end{array} \right] +
   \left[\begin{array}{ c c c c }
   b_{00} & b_{01} & b_{02} & b_{03} \\
   b_{10} & b_{11} & b_{12} & b_{13} \\
   b_{20} & b_{21} & b_{22} & b_{23} \\
   b_{30} & b_{31} & b_{32} & b_{33}
   \end{array} \right]
   =
   \left[\begin{array}{ c c c c }
   a_{00} + b_{00} & a_{01} + b_{01} & a_{02} + b_{02} & a_{03} + b_{03} \\
   a_{10} + b_{10} & a_{11} + b_{11} & a_{12} + b_{12} & a_{13} + b_{13} \\
   a_{20} + b_{20} & a_{21} + b_{21} & a_{22} + b_{22} & a_{23} + b_{23} \\
   a_{30} + b_{30} & a_{31} + b_{31} & a_{32} + b_{32} & a_{33} + b_{33}
   \end{array} \right]
 \f]
*/// ------------------------------------------------------------------ 

static inline void ex_mat44f_add ( ex_mat44f_t *_r, const ex_mat44f_t *_lhs, const ex_mat44f_t *_rhs ) {
    _r->m00 = _lhs->m00 + _rhs->m00; 
    _r->m01 = _lhs->m01 + _rhs->m01; 
    _r->m02 = _lhs->m02 + _rhs->m02;
    _r->m03 = _lhs->m03 + _rhs->m03;

    _r->m10 = _lhs->m10 + _rhs->m10; 
    _r->m11 = _lhs->m11 + _rhs->m11;
    _r->m12 = _lhs->m12 + _rhs->m12;
    _r->m13 = _lhs->m13 + _rhs->m13;

    _r->m20 = _lhs->m20 + _rhs->m20; 
    _r->m21 = _lhs->m21 + _rhs->m21;
    _r->m22 = _lhs->m22 + _rhs->m22;
    _r->m23 = _lhs->m23 + _rhs->m23;

    _r->m30 = _lhs->m30 + _rhs->m30; 
    _r->m31 = _lhs->m31 + _rhs->m31;
    _r->m32 = _lhs->m32 + _rhs->m32;
    _r->m33 = _lhs->m33 + _rhs->m33;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat44f_sub ( ex_mat44f_t *_r, const ex_mat44f_t *_lhs, const ex_mat44f_t *_rhs )
 @retval _r the result matrix
 @param _lhs left hand side matrix 
 @param _rhs right hand side matrix 
 @details
 \f[
   \_r = Mat_a - Mat_b = 
   \left[\begin{array}{ c c c c }
   a_{00} & a_{01} & a_{02} & a_{03} \\
   a_{10} & a_{11} & a_{12} & a_{13} \\
   a_{20} & a_{21} & a_{22} & a_{23} \\
   a_{30} & a_{31} & a_{32} & a_{33}
   \end{array} \right] -
   \left[\begin{array}{ c c c c }
   b_{00} & b_{01} & b_{02} & b_{03} \\
   b_{10} & b_{11} & b_{12} & b_{13} \\
   b_{20} & b_{21} & b_{22} & b_{23} \\
   b_{30} & b_{31} & b_{32} & b_{33}
   \end{array} \right]
   =
   \left[\begin{array}{ c c c c }
   a_{00} - b_{00} & a_{01} - b_{01} & a_{02} - b_{02} & a_{03} - b_{03} \\
   a_{10} - b_{10} & a_{11} - b_{11} & a_{12} - b_{12} & a_{13} - b_{13} \\
   a_{20} - b_{20} & a_{21} - b_{21} & a_{22} - b_{22} & a_{23} - b_{23} \\
   a_{30} - b_{30} & a_{31} - b_{31} & a_{32} - b_{32} & a_{33} - b_{33}
   \end{array} \right]
 \f]
*/// ------------------------------------------------------------------ 

static inline void ex_mat44f_sub ( ex_mat44f_t *_r, const ex_mat44f_t *_lhs, const ex_mat44f_t *_rhs ) {
    _r->m00 = _lhs->m00 - _rhs->m00; 
    _r->m01 = _lhs->m01 - _rhs->m01;
    _r->m02 = _lhs->m02 - _rhs->m02;
    _r->m03 = _lhs->m03 - _rhs->m03;

    _r->m10 = _lhs->m10 - _rhs->m10;
    _r->m11 = _lhs->m11 - _rhs->m11;
    _r->m12 = _lhs->m12 - _rhs->m12;
    _r->m13 = _lhs->m13 - _rhs->m13;

    _r->m20 = _lhs->m20 - _rhs->m20;
    _r->m21 = _lhs->m21 - _rhs->m21;
    _r->m22 = _lhs->m22 - _rhs->m22;
    _r->m23 = _lhs->m23 - _rhs->m23;

    _r->m30 = _lhs->m30 - _rhs->m30;
    _r->m31 = _lhs->m31 - _rhs->m31;
    _r->m32 = _lhs->m32 - _rhs->m32;
    _r->m33 = _lhs->m33 - _rhs->m33;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat44f_mul ( ex_mat44f_t *_r, const ex_mat44f_t *_lhs, const ex_mat44f_t *_rhs )
 @retval _r the result matrix
 @param _lhs left hand side matrix 
 @param _rhs right hand side matrix 
 @details
 \f[
   \_r = Mat_a * Mat_b = 
   \left[\begin{array}{ c c c c }
   a_{00} & a_{01} & a_{02} & a_{03} \\
   a_{10} & a_{11} & a_{12} & a_{13} \\
   a_{20} & a_{21} & a_{22} & a_{23} \\
   a_{30} & a_{31} & a_{32} & a_{33}
   \end{array} \right] *
   \left[\begin{array}{ c c c c }
   b_{00} & b_{01} & b_{02} & b_{03} \\
   b_{10} & b_{11} & b_{12} & b_{13} \\
   b_{20} & b_{21} & b_{22} & b_{23} \\
   b_{30} & b_{31} & b_{32} & b_{33}
   \end{array} \right]
   =
   \left[\begin{array}{ c c c c }
   m_{00} & m_{01} & m_{02} & m_{03} \\
   m_{10} & m_{11} & m_{12} & m_{13} \\
   m_{20} & m_{21} & m_{22} & m_{23} \\
   m_{30} & m_{31} & m_{32} & m_{33}
   \end{array} \right]
 \f]

 where:

 \f[
   \left[\begin{array}{c}
   m_{00} = a_{00} * b_{00} + a_{01} * b_{10} + a_{02} * b_{20} + a_{03} * b_{30} \\ 
   m_{01} = a_{00} * b_{01} + a_{01} * b_{11} + a_{02} * b_{21} + a_{03} * b_{31} \\
   m_{02} = a_{00} * b_{02} + a_{01} * b_{12} + a_{02} * b_{22} + a_{03} * b_{32} \\
   m_{03} = a_{00} * b_{03} + a_{01} * b_{13} + a_{02} * b_{23} + a_{03} * b_{33} \\
   m_{10} = a_{10} * b_{00} + a_{11} * b_{10} + a_{12} * b_{20} + a_{13} * b_{30} \\
   m_{11} = a_{10} * b_{01} + a_{11} * b_{11} + a_{12} * b_{21} + a_{13} * b_{31} \\
   m_{13} = a_{10} * b_{02} + a_{11} * b_{12} + a_{12} * b_{22} + a_{13} * b_{32} \\
   m_{13} = a_{10} * b_{03} + a_{11} * b_{13} + a_{12} * b_{23} + a_{13} * b_{33} \\
   m_{20} = a_{20} * b_{00} + a_{21} * b_{10} + a_{22} * b_{20} + a_{23} * b_{30} \\
   m_{21} = a_{20} * b_{01} + a_{21} * b_{11} + a_{22} * b_{21} + a_{23} * b_{31} \\
   m_{22} = a_{20} * b_{02} + a_{21} * b_{12} + a_{22} * b_{22} + a_{23} * b_{32} \\
   m_{23} = a_{20} * b_{03} + a_{21} * b_{13} + a_{22} * b_{23} + a_{23} * b_{33} \\
   m_{30} = a_{30} * b_{00} + a_{31} * b_{10} + a_{32} * b_{20} + a_{33} * b_{30} \\
   m_{31} = a_{30} * b_{01} + a_{31} * b_{11} + a_{32} * b_{21} + a_{33} * b_{31} \\
   m_{32} = a_{30} * b_{02} + a_{31} * b_{12} + a_{32} * b_{22} + a_{33} * b_{32} \\
   m_{33} = a_{30} * b_{03} + a_{31} * b_{13} + a_{32} * b_{23} + a_{33} * b_{33}
   \end{array} \right]
 \f]
*/// ------------------------------------------------------------------ 

static inline void ex_mat44f_mul ( ex_mat44f_t *_r, const ex_mat44f_t *_lhs, const ex_mat44f_t *_rhs ) {
    float m00, m01, m02, m03; 
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float m30, m31, m32, m33;

    m00 = _lhs->m00 * _rhs->m00 + _lhs->m01 * _rhs->m10 + _lhs->m02 * _rhs->m20 + _lhs->m03 * _rhs->m30;
    m01 = _lhs->m00 * _rhs->m01 + _lhs->m01 * _rhs->m11 + _lhs->m02 * _rhs->m21 + _lhs->m03 * _rhs->m31;
    m02 = _lhs->m00 * _rhs->m02 + _lhs->m01 * _rhs->m12 + _lhs->m02 * _rhs->m22 + _lhs->m03 * _rhs->m32;
    m03 = _lhs->m00 * _rhs->m03 + _lhs->m01 * _rhs->m13 + _lhs->m02 * _rhs->m23 + _lhs->m03 * _rhs->m33;

    m10 = _lhs->m10 * _rhs->m00 + _lhs->m11 * _rhs->m10 + _lhs->m12 * _rhs->m20 + _lhs->m13 * _rhs->m30;
    m11 = _lhs->m10 * _rhs->m01 + _lhs->m11 * _rhs->m11 + _lhs->m12 * _rhs->m21 + _lhs->m13 * _rhs->m31;
    m12 = _lhs->m10 * _rhs->m02 + _lhs->m11 * _rhs->m12 + _lhs->m12 * _rhs->m22 + _lhs->m13 * _rhs->m32;
    m13 = _lhs->m10 * _rhs->m03 + _lhs->m11 * _rhs->m13 + _lhs->m12 * _rhs->m23 + _lhs->m13 * _rhs->m33;

    m20 = _lhs->m20 * _rhs->m00 + _lhs->m21 * _rhs->m10 + _lhs->m22 * _rhs->m20 + _lhs->m23 * _rhs->m30;
    m21 = _lhs->m20 * _rhs->m01 + _lhs->m21 * _rhs->m11 + _lhs->m22 * _rhs->m21 + _lhs->m23 * _rhs->m31;
    m22 = _lhs->m20 * _rhs->m02 + _lhs->m21 * _rhs->m12 + _lhs->m22 * _rhs->m22 + _lhs->m23 * _rhs->m32;
    m23 = _lhs->m20 * _rhs->m03 + _lhs->m21 * _rhs->m13 + _lhs->m22 * _rhs->m23 + _lhs->m23 * _rhs->m33;

    m30 = _lhs->m30 * _rhs->m00 + _lhs->m31 * _rhs->m10 + _lhs->m32 * _rhs->m20 + _lhs->m33 * _rhs->m30;
    m31 = _lhs->m30 * _rhs->m01 + _lhs->m31 * _rhs->m11 + _lhs->m32 * _rhs->m21 + _lhs->m33 * _rhs->m31;
    m32 = _lhs->m30 * _rhs->m02 + _lhs->m31 * _rhs->m12 + _lhs->m32 * _rhs->m22 + _lhs->m33 * _rhs->m32;
    m33 = _lhs->m30 * _rhs->m03 + _lhs->m31 * _rhs->m13 + _lhs->m32 * _rhs->m23 + _lhs->m33 * _rhs->m33;

    ex_mat44f_set( _r, 
                   m00, m01, m02, m03,
                   m10, m11, m12, m13,
                   m20, m21, m22, m23,
                   m30, m31, m32, m33 );
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat44f_mul_scalar ( ex_mat44f_t *_r, const ex_mat44f_t *_lhs, float _rhs )
 @retval _r the result matrix
 @param _lhs left hand side matrix 
 @param _rhs right hand side scalar 
 @details
 \f[
   \_r = Mat_a * s = 
   \left[\begin{array}{ c c c }
   a_{00} & a_{01} & a_{02} & a_{03} \\
   a_{10} & a_{11} & a_{12} & a_{13} \\
   a_{20} & a_{21} & a_{22} & a_{23} \\
   a_{30} & a_{31} & a_{32} & a_{33}
   \end{array} \right] *
   s
   =
   \left[\begin{array}{ c c c }
   a_{00} * s & a_{01} * s & a_{02} * s & a_{03} * s \\
   a_{10} * s & a_{11} * s & a_{12} * s & a_{13} * s \\
   a_{20} * s & a_{21} * s & a_{22} * s & a_{23} * s \\
   a_{30} * s & a_{31} * s & a_{32} * s & a_{33} * s
   \end{array} \right]
 \f]
*/// ------------------------------------------------------------------ 

static inline void ex_mat44f_mul_scalar ( ex_mat44f_t *_r, const ex_mat44f_t *_lhs, float _rhs ) {
    _r->m00 = _lhs->m00 * _rhs; 
    _r->m01 = _lhs->m01 * _rhs; 
    _r->m02 = _lhs->m02 * _rhs;
    _r->m03 = _lhs->m03 * _rhs;

    _r->m10 = _lhs->m10 * _rhs; 
    _r->m11 = _lhs->m11 * _rhs; 
    _r->m12 = _lhs->m12 * _rhs;
    _r->m13 = _lhs->m13 * _rhs;

    _r->m20 = _lhs->m20 * _rhs; 
    _r->m21 = _lhs->m21 * _rhs; 
    _r->m22 = _lhs->m22 * _rhs;
    _r->m23 = _lhs->m23 * _rhs;

    _r->m30 = _lhs->m30 * _rhs; 
    _r->m31 = _lhs->m31 * _rhs; 
    _r->m32 = _lhs->m32 * _rhs;
    _r->m33 = _lhs->m33 * _rhs;
}

// ------------------------------------------------------------------ 
/*! 
 @fn void ex_mat44f_mul_vec4f ( ex_vec4f_t *_r, const ex_mat44f_t *_lhs, const ex_vec4f_t *_rhs )
 @retval _r the result vector
 @param _lhs left hand side matrix 
 @param _rhs right hand side vector 
 @details
 \f[
   \_r = Mat_a * Vec_b = \left[\begin{array}{ c c c c }
   a_{00} & a_{01} & a_{02} & a_{03} \\
   a_{10} & a_{11} & a_{12} & a_{13} \\
   a_{20} & a_{21} & a_{22} & a_{23} \\
   a_{30} & a_{31} & a_{32} & a_{33}
   \end{array} \right] * 
   \left[\begin{array}{ c }
   b_{0} \\
   b_{1} \\
   b_{2} \\
   b_{3}
   \end{array} \right] = \left[\begin{array}{ c c c c }
   a_{00} * b_{0} + a_{01} * b_{1} + a_{02} * b_{2} + a_{03} * b_{3} & 
   a_{10} * b_{0} + a_{11} * b_{1} + a_{12} * b_{2} + a_{13} * b_{3} &
   a_{20} * b_{0} + a_{21} * b_{1} + a_{22} * b_{2} + a_{23} * b_{3} &
   a_{30} * b_{0} + a_{31} * b_{1} + a_{32} * b_{2} + a_{33} * b_{3}
   \end{array} \right]
 \f]
 @sa ex_vec4f_mul_mat44f
*/// ------------------------------------------------------------------ 

extern void ex_mat44f_mul_vec4f ( ex_vec4f_t *_r, const ex_mat44f_t *_lhs, const ex_vec4f_t *_rhs );

// ------------------------------------------------------------------ 
/*! 
 @fn void ex_vec4f_mul_mat44f ( ex_vec4f_t *_r, const ex_vec4f_t *_lhs, const ex_mat44f_t *_rhs )
 @retval _r the result vector
 @param _lhs left hand side vector
 @param _rhs right hand side matrix  
 @details
 \f[
   \_r = Vec_a * Mat_b = \left[\begin{array}{ c c c c }
   a_{0} & a_{1} & a_{2} & a_{3}
   \end{array} \right] * 
   \left[\begin{array}{ c c c c }
   b_{00} & b_{01} & b_{02} & b_{03} \\
   b_{10} & b_{11} & b_{12} & b_{13} \\
   b_{20} & b_{21} & b_{22} & b_{23} \\
   b_{30} & b_{31} & b_{32} & b_{33}
   \end{array} \right] = \left[\begin{array}{ c c c c }
   a_{0} * b_{00} + a_{1} * b_{10} + a_{2} * b_{20} + a_{3} * b_{30} & 
   a_{0} * b_{01} + a_{1} * b_{11} + a_{2} * b_{21} + a_{3} * b_{31} &
   a_{0} * b_{02} + a_{1} * b_{12} + a_{2} * b_{22} + a_{3} * b_{32} &
   a_{0} * b_{03} + a_{1} * b_{13} + a_{2} * b_{23} + a_{3} * b_{33}
   \end{array} \right]
 \f]
 @sa mat44f_mul_vec4f
*/// ------------------------------------------------------------------ 

extern void ex_vec4f_mul_mat44f ( ex_vec4f_t *_r, const ex_vec4f_t *_lhs, const ex_mat44f_t *_rhs );

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_scalar_div_mat44f ( ex_mat44f_t *_r, float _lhs, const ex_mat44f_t *_rhs )
 @retval _r the result vector
 @param _lhs left hand side float
 @param _rhs right hand side matrix  
 @details
 \f[
   \_r = s / Mat_b = 
   s /
   \left[\begin{array}{ c c c c }
   b_{00} & b_{01} & b_{02} & b_{03} \\
   b_{10} & b_{11} & b_{12} & b_{13} \\
   b_{20} & b_{21} & b_{22} & b_{23} \\
   b_{30} & b_{31} & b_{32} & b_{33}
   \end{array} \right]
   =
   \left[\begin{array}{ c c c c }
   s / b_{00} & s / b_{01} & s / b_{02} & s / b_{03} \\
   s / b_{10} & s / b_{11} & s / b_{12} & s / b_{13} \\
   s / b_{20} & s / b_{21} & s / b_{22} & s / b_{23} \\
   s / b_{30} & s / b_{31} & s / b_{32} & s / b_{33}
   \end{array} \right]
 \f]
 @sa mat44f_div_scalar
*/// ------------------------------------------------------------------ 

static inline void ex_scalar_div_mat44f ( ex_mat44f_t *_r, float _lhs, const ex_mat44f_t *_rhs ) {
    _r->m00 = _lhs / _rhs->m00; 
    _r->m01 = _lhs / _rhs->m01; 
    _r->m02 = _lhs / _rhs->m02;
    _r->m03 = _lhs / _rhs->m03;

    _r->m10 = _lhs / _rhs->m10;
    _r->m11 = _lhs / _rhs->m11;
    _r->m12 = _lhs / _rhs->m12;
    _r->m13 = _lhs / _rhs->m13;

    _r->m20 = _lhs / _rhs->m20;
    _r->m21 = _lhs / _rhs->m21;
    _r->m22 = _lhs / _rhs->m22;
    _r->m23 = _lhs / _rhs->m23;

    _r->m30 = _lhs / _rhs->m30;
    _r->m31 = _lhs / _rhs->m31;
    _r->m32 = _lhs / _rhs->m32;
    _r->m33 = _lhs / _rhs->m33;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat44f_div_scalar ( ex_mat44f_t *_r, const ex_mat44f_t *_lhs, float _rhs )
 @retval _r the result vector
 @param _lhs left hand side matrix  
 @param _rhs right hand side float
 @details
 \f[
   \_r = Mat_a / s = 
   \left[\begin{array}{ c c c c }
   a_{00} & a_{01} & a_{02} & a_{03} \\
   a_{10} & a_{11} & a_{12} & a_{13} \\
   a_{20} & a_{21} & a_{22} & a_{23} \\
   a_{30} & a_{31} & a_{32} & a_{33}
   \end{array} \right] /
   s
   =
   \left[\begin{array}{ c c c c }
   a_{00} / s & a_{01} / s & a_{02} / s & a_{03} / s \\
   a_{10} / s & a_{11} / s & a_{12} / s & a_{13} / s \\
   a_{20} / s & a_{21} / s & a_{22} / s & a_{23} / s \\
   a_{30} / s & a_{31} / s & a_{32} / s & a_{33} / s
   \end{array} \right]
 \f]
 @sa ex_scalar_div_mat44f
*/// ------------------------------------------------------------------ 

static inline void ex_mat44f_div_scalar ( ex_mat44f_t *_r, const ex_mat44f_t *_lhs, float _rhs ) {
    _r->m00 = _lhs->m00 / _rhs;
    _r->m01 = _lhs->m01 / _rhs;
    _r->m02 = _lhs->m02 / _rhs;
    _r->m03 = _lhs->m03 / _rhs;

    _r->m10 = _lhs->m10 / _rhs;
    _r->m11 = _lhs->m11 / _rhs;
    _r->m12 = _lhs->m12 / _rhs;
    _r->m13 = _lhs->m13 / _rhs;

    _r->m20 = _lhs->m20 / _rhs;
    _r->m21 = _lhs->m21 / _rhs;
    _r->m22 = _lhs->m22 / _rhs;
    _r->m23 = _lhs->m23 / _rhs;

    _r->m30 = _lhs->m30 / _rhs;
    _r->m31 = _lhs->m31 / _rhs;
    _r->m32 = _lhs->m32 / _rhs;
    _r->m33 = _lhs->m33 / _rhs;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat44f_transpose ( ex_mat44f_t *_m )
 @retval _m the result vector
 @param _m the in matrix
 @details get the transposed matrix from matrix _m, override and return it.

 \f[
   \left[\begin{array}{ c c c c }
   a_{00} & a_{01} & a_{02} & a_{03} \\
   a_{10} & a_{11} & a_{12} & a_{13} \\
   a_{20} & a_{21} & a_{22} & a_{23} \\
   a_{30} & a_{31} & a_{32} & a_{33}
   \end{array} \right] 
   \stackrel{transpose}\Longrightarrow
   \left[\begin{array}{ c c c c }
   a_{00} & a_{10} & a_{20} & a_{30} \\
   a_{01} & a_{11} & a_{21} & a_{31} \\
   a_{02} & a_{12} & a_{22} & a_{32} \\
   a_{03} & a_{13} & a_{23} & a_{33}
   \end{array} \right]
 \f]

 @sa mat44f_get_transpose
*/// ------------------------------------------------------------------ 

static inline void ex_mat44f_transpose ( ex_mat44f_t *_m ) {
    float swap;

    swap = _m->m01;
    _m->m01 = _m->m10;
    _m->m10 = swap;

    swap = _m->m02;
    _m->m02 = _m->m20;
    _m->m20 = swap;

    swap = _m->m12;
    _m->m12 = _m->m21;
    _m->m21 = swap;

    swap = _m->m03;
    _m->m03 = _m->m30;
    _m->m30 = swap;

    swap = _m->m13;
    _m->m13 = _m->m31;
    _m->m31 = swap;

    swap = _m->m23;
    _m->m23 = _m->m32;
    _m->m32 = swap;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat44f_get_transpose ( const ex_mat44f_t *_m, ex_mat44f_t *_r )
 @retval _r the result vector
 @param _m the in matrix
 @details get the transposed matrix from matrix _m, return it to matrix _r
 @sa ex_mat44f_transpose
*/// ------------------------------------------------------------------ 

static inline void ex_mat44f_get_transpose ( const ex_mat44f_t *_m, ex_mat44f_t *_r ) {
    ex_assert ( _r != _m, "can't use self as return value." );
    ex_mat44f_set( _r,
                   _m->m00, _m->m10, _m->m20, _m->m30,
                   _m->m01, _m->m11, _m->m21, _m->m31,
                   _m->m02, _m->m12, _m->m22, _m->m32,
                   _m->m03, _m->m13, _m->m23, _m->m33 );
}

// ------------------------------------------------------------------ 
/*! 
 @fn bool ex_mat44f_inverse ( ex_mat44f_t *_m )
 @retval _m the result vector
 @param _m the in matrix
 @return if the inverse operation successed 
 - true: successful
 - false: failed
 @details get the inversed matrix from matrix _m, override and return it.
 @sa mat44f_get_inverse
*/// ------------------------------------------------------------------ 

extern bool ex_mat44f_inverse ( ex_mat44f_t *_m );

// ------------------------------------------------------------------ 
/*! 
 @fn bool ex_mat44f_get_inverse ( const ex_mat44f_t *_m, ex_mat44f_t *_r )
 @retval _r the result vector
 @param _m the in matrix
 @return if the inverse operation successed 
 - true: successful
 - false: failed
 @details get the inversed matrix from matrix _m, return it to matrix _r
 @sa mat44f_inverse
*/// ------------------------------------------------------------------ 

extern bool ex_mat44f_get_inverse ( const ex_mat44f_t *_m, ex_mat44f_t *_r );

//! @}

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 

// #################################################################################
#endif // END MAT44F_H_1289540317
// #################################################################################


