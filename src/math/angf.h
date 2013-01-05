// ======================================================================================
// File         : angf.h
// Author       : Wu Jie 
// Last Change  : 11/25/2010 | 17:41:11 PM | Thursday,November
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef ANGF_H_1290678097
#define ANGF_H_1290678097
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
/*!
 @struct ex_angf_t
 @details
 the angle is store in radians, the range is from [0,2pi]
*/// ------------------------------------------------------------------ 

typedef struct ex_angf_t {
    float rad;
} ex_angf_t;

///////////////////////////////////////////////////////////////////////////////
// functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
/*!
 @fn static inline void ex_angf_set_by_radians_nosafe ( ex_angf_t *_a, float _radians ) 
 @param _a the in angle
 @param _radians the in radians must in range [0,2pi]
 @details
 set the angle by radians, the function will not check the if the radians 
 exceed the range. That make it nosafe but faster.
*/// ------------------------------------------------------------------ 

static inline void ex_angf_set_by_radians_nosafe ( ex_angf_t *_a, float _radians ) { 
    _a->rad = _radians;
}

// ------------------------------------------------------------------ 
/*!
 @fn static inline void ex_angf_set_by_radians ( ex_angf_t *_a, float _radians ) 
 @param _a the in angle
 @param _radians the in radians
 @details
 set the angle by radians
*/// ------------------------------------------------------------------ 

static inline void ex_angf_set_by_radians ( ex_angf_t *_a, float _radians ) { 
    if ( _radians > (float)EX_TWO_PI )
        _a->rad = fmodf(_radians,(float)EX_TWO_PI); 
    else if ( _radians < 0.0f )
        _a->rad = (float)EX_TWO_PI + fmodf(_radians,(float)EX_TWO_PI); 
    else
        _a->rad = _radians;
    ex_assert( !EX_IS_NAN(_a->rad), "error: NaN value" );
}

// ------------------------------------------------------------------ 
/*!
 @fn static inline void ex_angf_set_by_degrees ( ex_angf_t *_a, float _degrees ) 
 @param _a the in angle
 @param _degrees the in degrees
 @details
 set the angle by degrees
*/// ------------------------------------------------------------------ 

static inline void ex_angf_set_by_degrees ( ex_angf_t *_a, float _degrees ) {
    ex_angf_set_by_radians ( _a, ex_deg2rad_f(_degrees) );
} 

// ------------------------------------------------------------------ 
/*!
 @fn static inline float ex_angf_to_degrees_180 ( const ex_angf_t *_a ) 
 @param _a the in angle
 @return the result degrees
 @details
 convert angle to degrees in [-180,180]
*/// ------------------------------------------------------------------ 

static inline float ex_angf_to_degrees_180 ( const ex_angf_t *_a ) {
    float degrees = ex_rad2deg_f(_a->rad);
    return _a->rad >= (float)EX_PI ? degrees - 360.0f : degrees;
}

// ------------------------------------------------------------------ 
/*!
 @fn static inline float ex_angf_to_degrees_360 ( const ex_angf_t *_a ) 
 @param _a the in angle
 @return the result degrees
 @details
 convert angle to degrees in [0,360]
*/// ------------------------------------------------------------------ 

static inline float ex_angf_to_degrees_360 ( const ex_angf_t *_a ) { 
    return ex_rad2deg_f(_a->rad);
} 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_angf_to_rot22 ( const ex_angf_t *_a, ex_mat22f_t *_m ) {
    float cos_theta = cosf( _a->rad );
    float sin_theta = sinf( _a->rad );

    _m->m00 =  cos_theta, _m->m01 = sin_theta; 
    _m->m10 = -sin_theta, _m->m11 = cos_theta; 
} 

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_angf_neg ( ex_angf_t *_a )
 @retval _a the result angle
 @param _a the in angle
 @details get the negtive value from angle _a, set and override it.
 @sa ex_angf_get_neg
*/// ------------------------------------------------------------------ 

static inline void ex_angf_neg ( ex_angf_t *_a ) { 
    ex_angf_set_by_radians_nosafe( _a, (float)EX_TWO_PI - _a->rad );
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_angf_get_neg ( ex_angf_t *_r, const ex_angf_t *_a )
 @retval _r the result angle
 @param _v the in angle
 @details get the negtive value from angle _a, set and return it to angle _r
 @sa ex_angf_neg
*/// ------------------------------------------------------------------ 

static inline void ex_angf_get_neg ( ex_angf_t *_r, const ex_angf_t *_a ) { 
    ex_angf_set_by_radians_nosafe( _r, (float)EX_TWO_PI - _a->rad );
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_angf_mul ( ex_angf_t *_r, const ex_angf_t *_lhs, const ex_angf_t *_rhs )
 @retval _r the result angle
 @param _lhs left hand side angle 
 @param _rhs right hand side angle 
 @details multiply two angles
*/// ------------------------------------------------------------------ 

static inline void ex_angf_mul ( ex_angf_t *_r, const ex_angf_t *_lhs, const ex_angf_t *_rhs ) { 
    ex_angf_set_by_radians( _r, _lhs->rad * _rhs->rad );
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_angf_mul_scalar ( ex_angf_t *_r, const ex_angf_t *_lhs, float _scalar )
 @retval _r the result angle
 @param _lhs left hand side angle 
 @param _rhs right hand scalar
 @details multiply angle with scalar
*/// ------------------------------------------------------------------ 

static inline void ex_angf_mul_scalar ( ex_angf_t *_r, const ex_angf_t *_lhs, float _scalar ) { 
    ex_angf_set_by_radians( _r, _lhs->rad * _scalar );
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_angf_div ( ex_angf_t *_r, const ex_angf_t *_lhs, ex_angf_t *_rhs )
 @retval _r the result angle
 @param _lhs left hand side angle 
 @param _rhs right hand side angle 
 @details divide two angles
*/// ------------------------------------------------------------------ 

static inline void ex_angf_div ( ex_angf_t *_r, const ex_angf_t *_lhs, ex_angf_t *_rhs ) { 
    ex_angf_set_by_radians( _r, _lhs->rad / _rhs->rad );
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_angf_div_scalar ( ex_angf_t *_r, const ex_angf_t *_lhs, float _scalar )
 @retval _r the result angle
 @param _lhs left hand side angle 
 @param _rhs right hand scalar
 @details divide angle with scalar
*/// ------------------------------------------------------------------ 

static inline void ex_angf_div_scalar ( ex_angf_t *_r, const ex_angf_t *_lhs, float _scalar ) { 
    ex_angf_set_by_radians( _r, _lhs->rad / _scalar );
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_scalar_div_angf ( ex_angf_t *_r, float _scalar, const ex_angf_t *_rhs )
 @retval _r the result angle
 @param _lhs left hand scalar
 @param _rhs right hand side angle 
 @details divide scalar with angle
*/// ------------------------------------------------------------------ 

static inline void ex_scalar_div_angf ( ex_angf_t *_r, float _scalar, const ex_angf_t *_rhs ) { 
    ex_angf_set_by_radians( _r, _scalar / _rhs->rad );
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_angf_add ( ex_angf_t *_r, const ex_angf_t *_lhs, const ex_angf_t *_rhs )
 @retval _r the result angle
 @param _lhs left hand side angle 
 @param _rhs right hand side angle
 @details add two angles
*/// ------------------------------------------------------------------ 

static inline void ex_angf_add ( ex_angf_t *_r, const ex_angf_t *_lhs, const ex_angf_t *_rhs ) { 
    ex_angf_set_by_radians( _r, _lhs->rad + _rhs->rad );
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_angf_sub ( ex_angf_t *_r, const ex_angf_t *_lhs, const ex_angf_t *_rhs )
 @retval _r the result angle
 @param _lhs left hand side angle 
 @param _rhs right hand side angle
 @details sub two angles
*/// ------------------------------------------------------------------ 

static inline void ex_angf_sub ( ex_angf_t *_r, const ex_angf_t *_lhs, const ex_angf_t *_rhs ) { 
    ex_angf_set_by_radians( _r, _lhs->rad - _rhs->rad );
}

// ------------------------------------------------------------------ 
/*! 
 @fn static inline bool ex_angf_is_equal ( const ex_angf_t *_lhs, const ex_angf_t *_rhs )
 @param _lhs the left hand side angle
 @param _rhs the right hand side angle
 @return the result of the comparation
 @details compare if the two angles is equal to each other
*/// ------------------------------------------------------------------ 

static inline bool ex_angf_is_equal ( const ex_angf_t *_lhs, const ex_angf_t *_rhs ) { 
    return ex_is_equalf(_lhs->rad,_rhs->rad,EX_FLOAT_EPS);
}

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 


// #################################################################################
#endif // END ANGF_H_1290678097
// #################################################################################


