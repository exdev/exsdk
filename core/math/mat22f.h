// ======================================================================================
// File         : mat22f.h
// Author       : Wu Jie 
// Last Change  : 11/19/2010 | 09:40:13 AM | Friday,November
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MAT22F_H_1290130815
#define MAT22F_H_1290130815
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "vec2f.h"

// ######################### 
#ifdef __cplusplus
extern "C" { 
#endif
// ######################### 

//! @defgroup ex_mat22f_t matrix 2x2 float
//! @ingroup Math
//! @{

// ------------------------------------------------------------------ 
/*! 
 @struct ex_mat22f_t
 @details
 
 The data of matrix 2x2 is construct by an union structure with float elements.\n
 The matrix can be expressed in formular as:
 
 \f$
   \left[\begin{array}{ c c }
   m_{00} & m_{01} \\
   m_{10} & m_{11}
   \end{array} \right]
 \f$
 
 and in array as:

 \f$
   \left[\begin{array}{ c c }
   m_{00}, m_{01}, m_{10}, m_{11}
   \end{array} \right]
 \f$
*/// ------------------------------------------------------------------ 

typedef struct ex_mat22f_t {
    union {
        struct { 
            float m00, m01;
            float m10, m11;
        }; // end struct
        float m[4];
    };
} ex_mat22f_t;

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat22f_set ( ex_mat22f_t *_m, 
                      float _m00, float _m01,
                      float _m10, float _m11 )
 @retval _m the result matrix
 @param _m00
 @param _m01
 @param _m10
 @param _m11
 @details set the matrix _m by rest of the parameters:

 \f[
   m = \left[\begin{array}{ c c }
   \_m_{00} & \_m_{01} \\
   \_m_{10} & \_m_{11}
   \end{array} \right]
 \f]
*/// ------------------------------------------------------------------ 

static inline void ex_mat22f_set ( ex_mat22f_t *_m, 
                         float _m00, float _m01,
                         float _m10, float _m11 ) { 
    _m->m00 = _m00, _m->m01 = _m01; 
    _m->m10 = _m10, _m->m11 = _m11; 
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline static inline float ex_mat22f_m_get ( ex_mat22f_t *_m, uint _row, uint _col ) 
 @param _m the matrix
 @param _row the row index, range in [0,2)
 @param _col the col index, range in [0,2)
 @return result
 @details get the matrix element in (_row, _col)
*/// ------------------------------------------------------------------ 

static inline float ex_mat22f_m_get ( const ex_mat22f_t *_m, uint _row, uint _col ) { 
    ex_assert( _row >= 0 && _row < 2, "out of range" );
    ex_assert( _col >= 0 && _col < 2, "out of range" );
    return _m->m[2*_row+_col];
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat22f_m_set ( ex_mat22f_t *_m, uint _row, uint _col, float _v ) 
 @param _m the matrix
 @param _row the row index, range in [0,2)
 @param _col the col index, range in [0,2)
 @param _v the in value
 @return result
 @details get the matrix element in (_row, _col)
*/// ------------------------------------------------------------------ 

static inline void ex_mat22f_m_set ( ex_mat22f_t *_m, uint _row, uint _col, float _v ) { 
    ex_assert( _row >= 0 && _row < 2, "out of range" );
    ex_assert( _col >= 0 && _col < 2, "out of range" );
    _m->m[2*_row+_col] = _v;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat22f_row ( ex_vec2f_t* _r, const ex_mat22f_t *_m, uint _row )
 @retval _r the result vector
 @param _m the matrix
 @param _row the row index, range in [0,2)
 @details get the matrix by _row and return it in vector2, for example: 
 @code
 ex_vec2f_t r;
 ex_mat22f_t m = ex_mat22f_zero;
 ex_mat22f_row( &r, &m, 0 ); // set r to row 0 as -- (m.m00, m.m01)
 @endcode
 the r is equal to vector2 (m.m00, m.m01) 
*/// ------------------------------------------------------------------ 

static inline void ex_mat22f_row ( ex_vec2f_t *_r, const ex_mat22f_t *_m, uint _row ) {
    ex_assert( _row >= 0 && _row < 2, "out of range" );
    _r->x = _m->m[2*_row+0]; 
    _r->y = _m->m[2*_row+1]; 
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat22f_col ( ex_vec2f_t *_r, const ex_mat22f_t *_m, uint _col )
 @retval _r the result vector
 @param _m the matrix
 @param _col the column index, range in [0,2)
 @details get the matrix by _row and return it in vector2, for example: 
 @code
 ex_vec2f_t r;
 ex_mat22f_t m = ex_mat22f_zero;
 ex_mat22f_col( &r, &m, 0 ); // set r to column 0 as -- (m.m00, m.m10)
 @endcode
 the r is equal to vector2 (m.m00, m.m10) 
*/// ------------------------------------------------------------------ 

static inline void ex_mat22f_col ( ex_vec2f_t *_r, const ex_mat22f_t *_m, uint _col ) {
    ex_assert( _col >= 0 && _col < 2, "out of range" );
    _r->x = _m->m[2*0+_col]; 
    _r->y = _m->m[2*1+_col]; 
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat22f_neg ( ex_mat22f_t *_m )
 @param _m in matrix
 @retval _m the result matrix
 @details get the negtive value from matrix _m, override and return it as the result:

 \f[
   \_m 
   =
   -\left[\begin{array}{ c c }
   m_{00} & m_{01} \\
   m_{10} & m_{11}
   \end{array} \right]
   = 
   \left[\begin{array}{ c c }
   -m_{00} & -m_{01} \\
   -m_{10} & -m_{11}
   \end{array} \right]
 \f]
 @sa ex_mat22f_get_neg
*/// ------------------------------------------------------------------ 

static inline void ex_mat22f_neg ( ex_mat22f_t *_m ) {
    _m->m00 = -_m->m00, _m->m01 = -_m->m01; 
    _m->m10 = -_m->m10, _m->m11 = -_m->m11; 
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat22f_get_neg ( const ex_mat22f_t *_m, ex_mat22f_t *_r )
 @retval _r the result matrix
 @param _m in matrix
 @details get the negtive value from matrix _m and set it in matrix _r as the result:
 @sa ex_mat22f_neg
*/// ------------------------------------------------------------------ 

static inline void ex_mat22f_get_neg ( const ex_mat22f_t *_m, ex_mat22f_t *_r ) {
    ex_assert ( _r != _m, "can't use self as return value." );
    _r->m00 = -_m->m00, _r->m01 = -_m->m01; 
    _r->m10 = -_m->m10, _r->m11 = -_m->m11; 
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat22f_abs ( ex_mat22f_t *_m )
 @param _m in matrix
 @retval _m the result matrix
 @details get the absolute value from matrix _m, override and return it as the result:

 \f[
   \_m 
   =
   \left|\begin{array}{ c c }
   m_{00} & m_{01} \\
   m_{10} & m_{11}
   \end{array} \right|
   = 
   \left[\begin{array}{ c c }
   |m_{00}| & |m_{01}| \\
   |m_{10}| & |m_{11}|
   \end{array} \right]
 \f]
 @sa ex_mat22f_get_abs
*/// ------------------------------------------------------------------ 

static inline void ex_mat22f_abs ( ex_mat22f_t *_m ) {
    _m->m00 = fabsf(_m->m00), _m->m01 = fabsf(_m->m01); 
    _m->m10 = fabsf(_m->m10), _m->m11 = fabsf(_m->m11); 
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat22f_get_abs ( const ex_mat22f_t *_m, ex_mat22f_t *_r )
 @retval _r the result matrix
 @param _m in matrix
 @details get the absolute value from matrix _m and set it in matrix _r as the result:
 @sa ex_mat22f_abs
*/// ------------------------------------------------------------------ 

static inline void ex_mat22f_get_abs ( const ex_mat22f_t *_m, ex_mat22f_t *_r ) {
    ex_assert ( _r != _m, "can't use self as return value." );
    _r->m00 = fabsf(_m->m00), _r->m01 = fabsf(_m->m01); 
    _r->m10 = fabsf(_m->m10), _r->m11 = fabsf(_m->m11); 
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat22f_add ( ex_mat22f_t *_r, const ex_mat22f_t *_lhs, const ex_mat22f_t *_rhs )
 @retval _r the result matrix
 @param _lhs left hand side matrix 
 @param _rhs right hand side matrix 
 @details
 \f[
   \_r = Mat_a + Mat_b = 
   \left[\begin{array}{ c c }
   a_{00} & a_{01} \\
   a_{10} & a_{11}
   \end{array} \right] +
   \left[\begin{array}{ c c }
   b_{00} & b_{01} \\
   b_{10} & b_{11}
   \end{array} \right]
   =
   \left[\begin{array}{ c c }
   a_{00} + b_{00} & a_{01} + b_{01} \\
   a_{10} + b_{10} & a_{11} + b_{11}
   \end{array} \right]
 \f]
*/// ------------------------------------------------------------------ 

static inline void ex_mat22f_add ( ex_mat22f_t *_r, const ex_mat22f_t *_lhs, const ex_mat22f_t *_rhs ) {
    _r->m00 = _lhs->m00 + _rhs->m00; _r->m01 = _lhs->m01 + _rhs->m01;
    _r->m10 = _lhs->m10 + _rhs->m10; _r->m11 = _lhs->m11 + _rhs->m11;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat22f_sub ( ex_mat22f_t *_r, const ex_mat22f_t *_lhs, const ex_mat22f_t *_rhs )
 @retval _r the result matrix
 @param _lhs left hand side matrix 
 @param _rhs right hand side matrix 
 @details
 \f[
   \_r = Mat_a + Mat_b = 
   \left[\begin{array}{ c c }
   a_{00} & a_{01} \\
   a_{10} & a_{11}
   \end{array} \right] -
   \left[\begin{array}{ c c }
   b_{00} & b_{01} \\
   b_{10} & b_{11}
   \end{array} \right]
   =
   \left[\begin{array}{ c c }
   a_{00} - b_{00} & a_{01} - b_{01} \\
   a_{10} - b_{10} & a_{11} - b_{11}
   \end{array} \right]
 \f]
*/// ------------------------------------------------------------------ 

static inline void ex_mat22f_sub ( ex_mat22f_t *_r, const ex_mat22f_t *_lhs, const ex_mat22f_t *_rhs ) {
    _r->m00 = _lhs->m00 - _rhs->m00; _r->m01 = _lhs->m01 - _rhs->m01;
    _r->m10 = _lhs->m10 - _rhs->m10; _r->m11 = _lhs->m11 - _rhs->m11;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat22f_mul ( ex_mat22f_t *_r, const ex_mat22f_t *_lhs, const ex_mat22f_t *_rhs )
 @retval _r the result matrix
 @param _lhs left hand side matrix 
 @param _rhs right hand side matrix 
 @details
 \f[
   \_r = Mat_a * Mat_b = 
   \left[\begin{array}{ c c }
   a_{00} & a_{01} \\
   a_{10} & a_{11}
   \end{array} \right] *
   \left[\begin{array}{ c c }
   b_{00} & b_{01} \\
   b_{10} & b_{11}
   \end{array} \right]
   =
   \left[\begin{array}{ c c }
   a_{00} * b_{00} + a_{01} * b_{10} & a_{00} * b_{01} + a_{01} * b_{11} \\
   a_{10} * b_{00} + a_{11} * b_{10} & a_{10} * b_{01} + a_{11} * b_{11}
   \end{array} \right]
 \f]
*/// ------------------------------------------------------------------ 

static inline void ex_mat22f_mul ( ex_mat22f_t *_r, const ex_mat22f_t *_lhs, const ex_mat22f_t *_rhs ) {
    float m00, m01, m10, m11;

    m00 = _lhs->m00 * _rhs->m00 + _lhs->m01 * _rhs->m10;
    m01 = _lhs->m00 * _rhs->m01 + _lhs->m01 * _rhs->m11;
    m10 = _lhs->m10 * _rhs->m00 + _lhs->m11 * _rhs->m10;
    m11 = _lhs->m10 * _rhs->m01 + _lhs->m11 * _rhs->m11;

    ex_mat22f_set( _r, 
                m00, m01,
                m10, m11 );
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat22f_mul_scalar ( ex_mat22f_t *_r, const ex_mat22f_t *_lhs, float _rhs )
 @retval _r the result matrix
 @param _lhs left hand side matrix 
 @param _rhs right hand side scalar 
 @details
 \f[
   \_r = Mat_a * s = 
   \left[\begin{array}{ c c }
   a_{00} & a_{01} \\
   a_{10} & a_{11}
   \end{array} \right] *
   s
   =
   \left[\begin{array}{ c c }
   a_{00} * s & a_{01} * s \\
   a_{10} * s & a_{11} * s
   \end{array} \right]
 \f]
*/// ------------------------------------------------------------------ 

static inline void ex_mat22f_mul_scalar ( ex_mat22f_t *_r, const ex_mat22f_t *_lhs, float _rhs ) {
    _r->m00 = _lhs->m00 * _rhs;
    _r->m01 = _lhs->m01 * _rhs;
    _r->m10 = _lhs->m10 * _rhs;
    _r->m11 = _lhs->m11 * _rhs;
}

// ------------------------------------------------------------------ 
/*! 
 @fn void ex_mat22f_mul_vec2f ( ex_vec2f_t *_r, const ex_mat22f_t *_lhs, const ex_vec2f_t *_rhs )
 @retval _r the result vector
 @param _lhs left hand side matrix 
 @param _rhs right hand side vector 
 @details
 \f[
   \_r = Mat_a * Vec_b = \left[\begin{array}{ c c }
   a_{00} & a_{01} \\
   a_{10} & a_{11}
   \end{array} \right] * 
   \left[\begin{array}{ c }
   b_{0} \\
   b_{1}
   \end{array} \right] = \left[\begin{array}{ c c }
   a_{00} * b_{0} + a_{01} * b_{1} & a_{10} * b_{0} + a_{11} * b_{1}
   \end{array} \right]
 \f]
 @sa ex_vec2f_mul_mat22f
*/// ------------------------------------------------------------------ 

extern void ex_mat22f_mul_vec2f ( ex_vec2f_t *_r, const ex_mat22f_t *_lhs, const ex_vec2f_t *_rhs );

// ------------------------------------------------------------------ 
/*! 
 @fn void ex_vec2f_mul_mat22f ( ex_vec2f_t *_r, const ex_vec2f_t *_lhs, const ex_mat22f_t *_rhs )
 @retval _r the result vector
 @param _lhs left hand side vector
 @param _rhs right hand side matrix  
 @details
 \f[
   \_r = Vec_a * Mat_b = \left[\begin{array}{ c c }
   a_{0} & a_{1}
   \end{array} \right] * 
   \left[\begin{array}{ c c }
   b_{00} & b_{01} \\
   b_{10} & b_{11}
   \end{array} \right] = \left[\begin{array}{ c c }
   a_{0} * b_{00} + a_{1} * b_{10} & a_{0} * b_{01} + a_{1} * b_{11}
   \end{array} \right]
 \f]
 @sa ex_mat22f_mul_vec2f
*/// ------------------------------------------------------------------ 

extern void ex_vec2f_mul_mat22f ( ex_vec2f_t *_r, const ex_vec2f_t *_lhs, const ex_mat22f_t *_rhs );

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_scalar_div_mat22f ( ex_mat22f_t *_r, float _lhs, const ex_mat22f_t *_rhs )
 @retval _r the result vector
 @param _lhs left hand side float
 @param _rhs right hand side matrix  
 @details
 \f[
   \_r = s / Mat_b = 
   s /
   \left[\begin{array}{ c c }
   b_{00} & b_{01} \\
   b_{10} & b_{11}
   \end{array} \right]
   =
   \left[\begin{array}{ c c }
   s / b_{00} & s / b_{01} \\
   s / b_{10} & s / b_{11}
   \end{array} \right]
 \f]
 @sa ex_mat22f_div_scalar
*/// ------------------------------------------------------------------ 

static inline void ex_scalar_div_mat22f ( ex_mat22f_t *_r, float _lhs, const ex_mat22f_t *_rhs ) {
    _r->m00 = _lhs / _rhs->m00;
    _r->m01 = _lhs / _rhs->m01;
    _r->m10 = _lhs / _rhs->m10;
    _r->m11 = _lhs / _rhs->m11;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat22f_div_scalar ( ex_mat22f_t *_r, const ex_mat22f_t *_lhs, float _rhs )
 @retval _r the result vector
 @param _lhs left hand side matrix  
 @param _rhs right hand side float
 @details
 \f[
   \_r = Mat_a / s = 
   \left[\begin{array}{ c c }
   a_{00} & a_{01} \\
   a_{10} & a_{11}
   \end{array} \right] /
   s
   =
   \left[\begin{array}{ c c }
   a_{00} / s & a_{01} / s \\
   a_{10} / s & a_{11} / s
   \end{array} \right]
 \f]
 @sa ex_scalar_div_mat22f
*/// ------------------------------------------------------------------ 

static inline void ex_mat22f_div_scalar ( ex_mat22f_t *_r, const ex_mat22f_t *_lhs, float _rhs ) {
    _r->m00 = _lhs->m00 / _rhs;
    _r->m01 = _lhs->m01 / _rhs;
    _r->m10 = _lhs->m10 / _rhs;
    _r->m11 = _lhs->m11 / _rhs;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat22f_transpose ( ex_mat22f_t *_m )
 @retval _m the result vector
 @param _m the in matrix
 @details get the transposed matrix from matrix _m, override and return it.

 \f[
   \left[\begin{array}{ c c }
   a_{00} & a_{01} \\
   a_{10} & a_{11}
   \end{array} \right] 
   \stackrel{transpose}\Longrightarrow
   \left[\begin{array}{ c c }
   a_{00} & a_{10} \\
   a_{01} & a_{11}
   \end{array} \right]
 \f]

 @sa ex_mat22f_get_transpose
*/// ------------------------------------------------------------------ 

static inline void ex_mat22f_transpose ( ex_mat22f_t *_m ) {
    float swap;
    swap = _m->m01;
    _m->m01 = _m->m10;
    _m->m10 = swap; 
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_mat22f_get_transpose ( const ex_mat22f_t *_m, ex_mat22f_t *_r )
 @retval _r the result vector
 @param _m the in matrix
 @details get the transposed matrix from matrix _m, return it to matrix _r
 @sa ex_mat22f_transpose
*/// ------------------------------------------------------------------ 

static inline void ex_mat22f_get_transpose ( const ex_mat22f_t *_m, ex_mat22f_t *_r ) {
    ex_assert ( _r != _m, "can't use self as return value." );
    _r->m00 = _m->m00, _r->m01 = _m->m10;
    _r->m10 = _m->m01, _r->m11 = _m->m11;
}

// ------------------------------------------------------------------ 
/*! 
 @fn bool ex_mat22f_inverse ( ex_mat22f_t *_m )
 @retval _m the result vector
 @param _m the in matrix
 @return if the inverse operation successed 
 - true: successful
 - false: failed
 @details get the inversed matrix from matrix _m, override and return it.
 @sa ex_mat22f_get_inverse
*/// ------------------------------------------------------------------ 

extern bool ex_mat22f_inverse ( ex_mat22f_t *_m );

// ------------------------------------------------------------------ 
/*! 
 @fn bool ex_mat22f_get_inverse ( const ex_mat22f_t *_m, ex_mat22f_t *_r )
 @retval _r the result vector
 @param _m the in matrix
 @return if the inverse operation successed 
 - true: successful
 - false: failed
 @details get the inversed matrix from matrix _m, return it to matrix _r
 @sa ex_mat22f_inverse
*/// ------------------------------------------------------------------ 

extern bool ex_mat22f_get_inverse ( const ex_mat22f_t *_m, ex_mat22f_t *_r );

//! @}

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 

// #################################################################################
#endif // END MAT22F_H_1290130815
// #################################################################################
