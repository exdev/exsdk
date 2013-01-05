// ======================================================================================
// File         : vec2f.h
// Author       : Wu Jie 
// Last Change  : 11/11/2010 | 11:08:19 AM | Thursday,November
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef VEC2F_H_1289444900
#define VEC2F_H_1289444900
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" { 
#endif
// ######################### 

//! @defgroup ex_vec2f_t vector2 float
//! @ingroup Math
//! @{

///////////////////////////////////////////////////////////////////////////////
// define
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
/*! 
 @struct ex_vec2f_t
 @details
 
 The data of vector2 is construct by an union structure with float elements.\n
 The vector2 can be expressed in formular as:
 
 \f$
   \left[\begin{array}{ c c }
   x & y
   \end{array} \right]
 \f$
 
 and in array as:

 \f$
   \left[\begin{array}{ c c }
   v_{0}, v_{1}
   \end{array} \right]
 \f$

 @note you can use: 

 @code
 ex_vec2f_t v = { 1.0f, 1.0f }; 
 @endcode

 to initialize a vector.  
*/// ------------------------------------------------------------------ 

typedef struct ex_vec2f_t {
    union {
        struct { float x, y; }; // end struct
        float v[2];
    };
} ex_vec2f_t;

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_vec2f_set ( ex_vec2f_t *_r, float _x, float _y )
 @retval _r the result vector2
 @param x
 @param y
 @details set the vector2 _r by rest of the parameters:

 \f[
   q = \left[\begin{array}{ c c }
   \_x & \_y
   \end{array} \right]
 \f]
*/// ------------------------------------------------------------------ 

static inline void ex_vec2f_set ( ex_vec2f_t *_r, float _x, float _y ) { _r->x = _x, _r->y = _y; }

// ------------------------------------------------------------------ 
/*! 
 @fn static inline bool ex_vec2f_is_equal ( ex_vec2f_t *_lhs, ex_vec2f_t *_rhs )
 @param _lhs the left hand side vector2
 @param _rhs the right hand side vector2
 @return the result of the comparation
 @details compare if the two vector2 is equal to each other
*/// ------------------------------------------------------------------ 

static inline bool ex_vec2f_is_equal ( const ex_vec2f_t *_lhs, const ex_vec2f_t *_rhs ) { 
    return ex_is_equalf(_lhs->x,_rhs->x,EX_FLOAT_EPS)
        && ex_is_equalf(_lhs->y,_rhs->y,EX_FLOAT_EPS);
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_vec2f_neg ( ex_vec2f_t *_v )
 @retval _v the result vector2
 @param _v the in vector2
 @details get the negtive value from vector2 _v, override and return it as the result:

 \f[
   q = -\left[\begin{array}{ c c }
   x & y
   \end{array} \right]
   = \left[\begin{array}{ c c }
   -x & -y
   \end{array} \right]
 \f]
 @sa ex_vec2f_get_neg
*/// ------------------------------------------------------------------ 

static inline void ex_vec2f_neg ( ex_vec2f_t *_v ) { 
    _v->x = -_v->x; 
    _v->y = -_v->y; 
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_vec2f_get_neg ( const ex_vec2f_t *_v, ex_vec2f_t *_r )
 @retval _r the result vector2
 @param _v the in vector2
 @details get the negtive value from vector2 _v, set and return it to vector2 _v
 @sa ex_vec2f_neg
*/// ------------------------------------------------------------------ 

static inline void ex_vec2f_get_neg ( const ex_vec2f_t *_v, ex_vec2f_t *_r ) { 
    ex_assert ( _r != _v, "can't use self as return value." );
    _r->x = -_v->x; 
    _r->y = -_v->y; 
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_vec2f_add ( ex_vec2f_t *_r, const ex_vec2f_t *_lhs, const ex_vec2f_t *_rhs )
 @retval _r the result vector2
 @param _lhs the left hand side vector2
 @param _rhs the right hand side vector2
 @details
 \f[
   \_r = Vec_a + Vec_b = 
   \left[\begin{array}{ c c }
   a_{x} & a_{y}
   \end{array} \right] +
   \left[\begin{array}{ c c }
   b_{x} & b_{y}
   \end{array} \right]
   =
   \left[\begin{array}{ c c }
   a_{x} + b_{x} & 
   a_{y} + b_{y}
   \end{array} \right]
 \f]
*/// ------------------------------------------------------------------ 

static inline void ex_vec2f_add ( ex_vec2f_t *_r, const ex_vec2f_t *_lhs, const ex_vec2f_t *_rhs ) { 
    _r->x = _lhs->x + _rhs->x;
    _r->y = _lhs->y + _rhs->y;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_vec2f_add_scalar ( ex_vec2f_t *_r, const ex_vec2f_t *_lhs, float _rhs )
 @retval _r the result vector2
 @param _lhs the left hand side vector2
 @param _rhs the right hand side float
 @details
 \f[
   \_r = Vec_a + s = 
   \left[\begin{array}{ c c }
   a_{x} & a_{y}
   \end{array} \right] + s
   =
   \left[\begin{array}{ c c }
   a_{x} + s & 
   a_{y} + s
   \end{array} \right]
 \f]
*/// ------------------------------------------------------------------ 

static inline void ex_vec2f_add_scalar ( ex_vec2f_t *_r, const ex_vec2f_t *_lhs, float _rhs ) { 
    _r->x = _lhs->x + _rhs;
    _r->y = _lhs->y + _rhs;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_vec2f_sub ( ex_vec2f_t *_r, const ex_vec2f_t *_lhs, const ex_vec2f_t *_rhs )
 @retval _r the result vector2
 @param _lhs the left hand side vector2
 @param _rhs the right hand side vector2
 @details
 \f[
   \_r = Vec_a - Vec_b = 
   \left[\begin{array}{ c c }
   a_{x} & a_{y}
   \end{array} \right] -
   \left[\begin{array}{ c c }
   b_{x} & b_{y}
   \end{array} \right]
   =
   \left[\begin{array}{ c c }
   a_{x} - b_{x} & 
   a_{y} - b_{y}
   \end{array} \right]
 \f]
*/// ------------------------------------------------------------------ 

static inline void ex_vec2f_sub ( ex_vec2f_t *_r, const ex_vec2f_t *_lhs, const ex_vec2f_t *_rhs ) { 
    _r->x = _lhs->x - _rhs->x;
    _r->y = _lhs->y - _rhs->y;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_vec2f_sub_scalar ( ex_vec2f_t *_r, const ex_vec2f_t *_lhs, float _rhs )
 @retval _r the result vector2
 @param _lhs the left hand side vector2
 @param _rhs the right hand side float
 @details
 \f[
   \_r = Vec_a - s = 
   \left[\begin{array}{ c c }
   a_{x} & a_{y}
   \end{array} \right] - s
   =
   \left[\begin{array}{ c c }
   a_{x} - s & 
   a_{y} - s
   \end{array} \right]
 \f]
*/// ------------------------------------------------------------------ 

static inline void ex_vec2f_sub_scalar ( ex_vec2f_t *_r, const ex_vec2f_t *_lhs, float _rhs ) { 
    _r->x = _lhs->x - _rhs;
    _r->y = _lhs->y - _rhs;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_scalar_sub_vec2f ( ex_vec2f_t *_r, float _lhs, const ex_vec2f_t *_rhs )
 @retval _r the result vector2
 @param _lhs the left hand side float
 @param _rhs the right hand side vector2
 @details
 \f[
   \_r = s - Vec_b = 
   s - 
   \left[\begin{array}{ c c }
   b_{x} & b_{y}
   \end{array} \right]
   =
   \left[\begin{array}{ c c }
   s - b_{x} & 
   s - b_{y}
   \end{array} \right]
 \f]
*/// ------------------------------------------------------------------ 

static inline void ex_scalar_sub_vec2f ( ex_vec2f_t *_r, float _lhs, const ex_vec2f_t *_rhs ) { 
    _r->x = _lhs - _rhs->x;
    _r->y = _lhs - _rhs->y;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_vec2f_mul ( ex_vec2f_t *_r, const ex_vec2f_t *_lhs, const ex_vec2f_t *_rhs )
 @retval _r the result vector2
 @param _lhs the left hand side vector2
 @param _rhs the right hand side vector2
 @details
 \f[
   \_r = Vec_a * Vec_b = 
   \left[\begin{array}{ c c }
   a_{x} & a_{y}
   \end{array} \right] *
   \left[\begin{array}{ c c }
   b_{x} & b_{y}
   \end{array} \right]
   =
   \left[\begin{array}{ c c }
   a_{x} * b_{x} & 
   a_{y} * b_{y}
   \end{array} \right]
 \f]
*/// ------------------------------------------------------------------ 

static inline void ex_vec2f_mul ( ex_vec2f_t *_r, const ex_vec2f_t *_lhs, const ex_vec2f_t *_rhs ) { 
    _r->x = _lhs->x * _rhs->x;
    _r->y = _lhs->y * _rhs->y;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_vec2f_mul_scalar ( ex_vec2f_t *_r, const ex_vec2f_t *_lhs, float _rhs )
 @retval _r the result vector2
 @param _lhs the left hand side vector2
 @param _rhs the right hand side float
 @details
 \f[
   \_r = Vec_a * s = 
   \left[\begin{array}{ c c }
   a_{x} & a_{y}
   \end{array} \right] * s
   =
   \left[\begin{array}{ c c }
   a_{x} * s & 
   a_{y} * s
   \end{array} \right]
 \f]
*/// ------------------------------------------------------------------ 

static inline void ex_vec2f_mul_scalar ( ex_vec2f_t *_r, const ex_vec2f_t *_lhs, float _rhs ) { 
    _r->x = _lhs->x * _rhs;
    _r->y = _lhs->y * _rhs;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_vec2f_div ( ex_vec2f_t *_r, const ex_vec2f_t *_lhs, const ex_vec2f_t *_rhs )
 @retval _r the result vector2
 @param _lhs the left hand side vector2
 @param _rhs the right hand side vector2
 @details
 \f[
   \_r = Vec_a / Vec_b = 
   \left[\begin{array}{ c c }
   a_{x} & a_{y}
   \end{array} \right] /
   \left[\begin{array}{ c c }
   b_{x} & b_{y}
   \end{array} \right]
   =
   \left[\begin{array}{ c c }
   a_{x} / b_{x} & 
   a_{y} / b_{y}
   \end{array} \right]
 \f]
*/// ------------------------------------------------------------------ 

static inline void ex_vec2f_div ( ex_vec2f_t *_r, const ex_vec2f_t *_lhs, const ex_vec2f_t *_rhs ) { 
    _r->x = _lhs->x / _rhs->x;
    _r->y = _lhs->y / _rhs->y;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_vec2f_div_scalar ( ex_vec2f_t *_r, const ex_vec2f_t *_lhs, float _rhs )
 @retval _r the result vector2
 @param _lhs the left hand side vector2
 @param _rhs the right hand side float
 @details
 \f[
   \_r = Vec_a / s = 
   \left[\begin{array}{ c c }
   a_{x} & a_{y}
   \end{array} \right] / s
   =
   \left[\begin{array}{ c c }
   a_{x} / s & 
   a_{y} / s
   \end{array} \right]
 \f]
*/// ------------------------------------------------------------------ 

static inline void ex_vec2f_div_scalar ( ex_vec2f_t *_r, const ex_vec2f_t *_lhs, float _rhs ) { 
    _r->x = _lhs->x / _rhs;
    _r->y = _lhs->y / _rhs;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_scalar_div_vec2f ( ex_vec2f_t *_r, float _lhs, const ex_vec2f_t *_rhs )
 @retval _r the result vector2
 @param _lhs the left hand side float
 @param _rhs the right hand side vector2
 @details
 \f[
   \_r = s / Vec_b = 
   s / 
   \left[\begin{array}{ c c }
   b_{x} & b_{y}
   \end{array} \right]
   =
   \left[\begin{array}{ c c }
   s / b_{x} & 
   s / b_{y}
   \end{array} \right]
 \f]
*/// ------------------------------------------------------------------ 

static inline void ex_scalar_div_vec2f ( ex_vec2f_t *_r, float _lhs, const ex_vec2f_t *_rhs ) { 
    _r->x = _lhs / _rhs->x;
    _r->y = _lhs / _rhs->y;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline float ex_vec2f_dot ( const ex_vec2f_t *_lhs, const ex_vec2f_t *_rhs )
 @param _lhs the left hand vector2
 @param _rhs the right hand vector2
 @return the dot product result
 @details get the dot product
 \f[
   \left[\begin{array}{ c c }
   a_{x} & a_{y}
   \end{array} \right]
   dot
   \left[\begin{array}{ c }
   b_{x} \\ 
   b_{y}
   \end{array} \right]
   =
   a_{x} * b_{x} + 
   a_{y} * b_{y}
 \f]
*/// ------------------------------------------------------------------ 

static inline float ex_vec2f_dot ( const ex_vec2f_t *_lhs, const ex_vec2f_t *_rhs ) {
    return _lhs->x * _rhs->x + _lhs->y * _rhs->y;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline float ex_vec2f_cross ( const ex_vec2f_t *_lhs, const ex_vec2f_t *_rhs )
 @param _lhs the left hand vector2
 @param _rhs the right hand vector2
 @return the cross product result
 @details get the cross product
 \f[
   \left[\begin{array}{ c c }
   a_{x} & a_{y}
   \end{array} \right]
   cross
   \left[\begin{array}{ c }
   b_{x} \\ 
   b_{y}
   \end{array} \right]
   =
   a_{x} * b_{y} - 
   a_{y} * b_{x}
 \f]
*/// ------------------------------------------------------------------ 

static inline float ex_vec2f_cross ( const ex_vec2f_t *_lhs, const ex_vec2f_t *_rhs ) {
    return _lhs->x * _rhs->y - _lhs->y * _rhs->x;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline float ex_vec2f_len( const ex_vec2f_t *_v )
 @param _v the in vector2
 @return the length of the in vector2
 @details return the length of vector2 _v
 @sa ex_vec2f_lenSQR
*/// ------------------------------------------------------------------ 

static inline float ex_vec2f_len ( const ex_vec2f_t *_v ) {
    return sqrtf ( ex_vec2f_dot(_v,_v) );
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline float ex_vec2f_lenSQR( const ex_vec2f_t *_v )
 @param _v the in vector2
 @return the length square of the in vector2
 @details return the length square of vector2 _v
 @sa ex_vec2f_len
*/// ------------------------------------------------------------------ 

static inline float ex_vec2f_lenSQR ( const ex_vec2f_t *_v ) {
    return ex_vec2f_dot(_v,_v);
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline bool ex_vec2f_is_normalized ( const ex_vec2f_t *_v )
 @param _v the in vector2
 @return if the inverse operation successed 
 - true: successful
 - false: failed
 @details check if the in vector2 is normalized 
 @sa ex_vec2f_get_normalize
 @sa ex_vec2f_normalize
*/// ------------------------------------------------------------------ 

static inline bool ex_vec2f_is_normalized ( const ex_vec2f_t *_v ) {
    return ex_is_equalf( ex_vec2f_lenSQR(_v), 1.0f, EX_FLOAT_EPS);
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline bool ex_vec2f_normalize ( ex_vec2f_t *_v )
 @param _v the in vector2
 @return if the inverse operation successed 
 - true: successful
 - false: failed
 @details check if the in vector2 is normalized 
 @sa ex_vec2f_is_normalized
 @sa ex_vec2f_get_normalize
*/// ------------------------------------------------------------------ 

static inline bool ex_vec2f_normalize ( ex_vec2f_t *_v ) {
    float length_sqr = ex_vec2f_lenSQR(_v);
    float inv_length = 0.0f; 

    if ( ex_is_equalf( length_sqr, 1.0f, EX_FLOAT_EPS ) )
        return true;

    if( ex_is_zerof( length_sqr, EX_FLOAT_EPS ) )
        return false;

    inv_length = ex_inv_sqrtf( length_sqr );
    ex_vec2f_mul_scalar ( _v, _v, inv_length );
    return true;
}

// ------------------------------------------------------------------ 
/*! 
 @fn bool ex_vec2f_get_normalize ( const ex_vec2f_t *_v, ex_vec2f_t *_r )
 @retval _r the result vector2
 @param _v the in vector2
 @return if the inverse operation successed 
 - true: successful
 - false: failed
 @details get the normalized vector2 from _r, set and return it to vector2 _v
 @sa ex_vec2f_is_normalized
 @sa ex_vec2f_normalize
*/// ------------------------------------------------------------------ 

static inline bool ex_vec2f_get_normalize ( const ex_vec2f_t *_v, ex_vec2f_t *_r ) {
    float length_sqr, inv_length;

    ex_assert ( _r != _v, "can't use self as return value." );
    length_sqr = ex_vec2f_lenSQR(_v);
    inv_length = 0.0f; 

    if ( ex_is_equalf( length_sqr, 1.0f, EX_FLOAT_EPS ) ) {
        return true;
    }

    if( ex_is_zerof( length_sqr, EX_FLOAT_EPS ) ) {
        return false;
    }

    inv_length = ex_inv_sqrtf( length_sqr );
    ex_vec2f_mul_scalar ( _r, _v, inv_length );
    return true;
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_vec2f_get_truncate ( ex_vec2f_t *_r, const ex_vec2f_t *_v, float _maxLength )
 @retval _r the result vector2
 @param _v the in vector2
 @param _maxLength the truncate length
 @details check if vector is large than _maxLength, if yes, truncate it to _maxLength
 @sa ex_vec2f_truncate
*/// ------------------------------------------------------------------ 

static inline void ex_vec2f_get_truncate ( ex_vec2f_t *_r, const ex_vec2f_t *_v, float _maxLength ) {
    const float maxLengthSQR = _maxLength * _maxLength;
    const float vecLengthSQR = ex_vec2f_lenSQR(_v);
    if ( vecLengthSQR > maxLengthSQR )
        ex_vec2f_mul_scalar (_r, _r, _maxLength / sqrtf (vecLengthSQR) );
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_vec2f_truncate ( ex_vec2f_t *_r, float _maxLength )
 @retval _r the result vector2
 @param _r the in vector2
 @param _maxLength the truncate length
 @details check if vector is large than _maxLength, if yes, truncate it to _maxLength
 @sa ex_vec2f_truncate
*/// ------------------------------------------------------------------ 

static inline void ex_vec2f_truncate ( ex_vec2f_t *_r, float _maxLength ) {
    const float maxLengthSQR = _maxLength * _maxLength;
    const float vecLengthSQR = ex_vec2f_lenSQR(_r);
    if ( vecLengthSQR > maxLengthSQR )
        ex_vec2f_mul_scalar (_r, _r, _maxLength / sqrtf (vecLengthSQR) );
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_vec2f_project_to ( ex_vec2f_t *_r, const ex_vec2f_t *_from, const ex_vec2f_t *_to )
 @retval _r the result vector2
 @param _from the in vector 
 @param _to the vector parallel to
 @details return component of vector parallel to a unit _to vector
 more details, check http://mathworld.wolfram.com/DotProduct.html
 @note _to must be normalized.
*/// ------------------------------------------------------------------ 

static inline void ex_vec2f_project_to ( ex_vec2f_t *_r, const ex_vec2f_t *_from, const ex_vec2f_t *_to ) {
    float projection;
    ex_assert ( ex_vec2f_is_normalized(_to), "vector _to must be normalized." );
    projection = ex_vec2f_dot( _from, _to );
    ex_vec2f_mul_scalar( _r, _to, projection );
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_vec2f_perpendicular_to ( ex_vec2f_t *_r, const ex_vec2f_t *_from, const ex_vec2f_t *_to )
 @retval _r the result vector2
 @param _from the in vector 
 @param _to the vector perpendicular to
 @details return component of vector perpendicular to a unit _to vector
 more details, check http://mathworld.wolfram.com/DotProduct.html
 @note _to must be normalized.
*/// ------------------------------------------------------------------ 

static inline void ex_vec2f_perpendicular_to ( ex_vec2f_t *_r, const ex_vec2f_t *_from, const ex_vec2f_t *_to ) {
    ex_vec2f_t v;
    ex_assert ( ex_vec2f_is_normalized(_to), "vector _to must be normalized." );
    ex_vec2f_project_to ( &v, _from, _to );
    ex_vec2f_sub ( _r, _from, &v );
}

// TODO:
// ex_vec2f_reflect ( ex_vec2f_t *_r, ex_vec2f_t *_in, ex_vec2f_t *_normal )

//! @}

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 

// #################################################################################
#endif // END VEC2F_H_1289444900
// #################################################################################
