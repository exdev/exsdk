// ======================================================================================
// File         : ease_curve.h
// Author       : Wu Jie 
// Last Change  : 11/25/2010 | 10:39:44 AM | Thursday,November
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef EASE_CURVE_H_1290652786
#define EASE_CURVE_H_1290652786
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" { 
#endif
// ######################### 

//! @defgroup ease_curve easing curve
//! @ingroup Math
//! @{

// ------------------------------------------------------------------ 
/*! 
 @fn static inline float ex_ease_linearf ( float _t )
 @param _t ratio range in [0,1]
 @return the ease result

 @fn static inline double ex_ease_linear ( double _t )
 @param _t ratio range in [0,1]
 @return the ease result
*/// ------------------------------------------------------------------ 

static inline float ex_ease_linearf ( float _t ) { return _t; }
static inline double ex_ease_linear ( double _t ) { return _t; }

// ------------------------------------------------------------------ 
/*! 
 @fn float ex_ease_in_quadf ( float _t )
 @param _t ratio range in [0,1]
 @return the ease result
 @details Easing equation function for a quadratic (_t^2)

 @fn double ex_ease_in_quad ( double _t )
 @sa ex_ease_in_quadf

 @fn float ex_ease_out_quadf ( float _t )
 @sa ex_ease_in_quadf

 @fn double ex_ease_out_quad ( double _t )
 @sa ex_ease_in_quadf

 @fn float ex_ease_inout_quadf ( float _t ) 
 @sa ex_ease_in_quadf

 @fn double ex_ease_inout_quad ( double _t ) 
 @sa ex_ease_in_quadf

 @fn float ex_ease_outin_quadf ( float _t ) 
 @sa ex_ease_in_quadf

 @fn double ex_ease_outin_quad ( double _t ) 
 @sa ex_ease_in_quadf
*/// ------------------------------------------------------------------ 

extern float ex_ease_in_quadf ( float _t );
extern double ex_ease_in_quad ( double _t );

extern float ex_ease_out_quadf ( float _t );
extern double ex_ease_out_quad ( double _t );

extern float ex_ease_inout_quadf ( float _t ); 
extern double ex_ease_inout_quad ( double _t ); 

extern float ex_ease_outin_quadf ( float _t ); 
extern double ex_ease_outin_quad ( double _t ); 

// ------------------------------------------------------------------ 
/*! 
 @fn float ex_ease_in_cubicf ( float _t )
 @param _t ratio range in [0,1]
 @return the ease result
 @details Easing equation function for a cubic (_t^3)

 @fn double ex_ease_in_cubic ( double _t )
 @sa ex_ease_in_cubicf
 
 @fn float ex_ease_out_cubicf ( float _t )
 @sa ex_ease_in_cubicf

 @fn double ex_ease_out_cubic ( double _t )
 @sa ex_ease_in_cubicf

 @fn float ex_ease_inout_cubicf ( float _t ) 
 @sa ex_ease_in_cubicf

 @fn double ex_ease_inout_cubic ( double _t ) 
 @sa ex_ease_in_cubicf
 
 @fn float ex_ease_outin_cubicf ( float _t ) 
 @sa ex_ease_in_cubicf

 @fn double ex_ease_outin_cubic ( double _t ) 
 @sa ex_ease_in_cubicf
*/// ------------------------------------------------------------------ 

extern float ex_ease_in_cubicf ( float _t );
extern double ex_ease_in_cubic ( double _t );

extern float ex_ease_out_cubicf ( float _t );
extern double ex_ease_out_cubic ( double _t );

extern float ex_ease_inout_cubicf ( float _t ); 
extern double ex_ease_inout_cubic ( double _t ); 

extern float ex_ease_outin_cubicf ( float _t ); 
extern double ex_ease_outin_cubic ( double _t ); 

// ------------------------------------------------------------------ 
/*! 
 @fn float ex_ease_in_quartf ( float _t )
 @param _t ratio range in [0,1]
 @return the ease result
 @details Easing equation function for a quartic (_t^4)

 @fn double ex_ease_in_quart ( double _t )
 @sa ex_ease_in_quartf
 
 @fn float ex_ease_out_quartf ( float _t )
 @sa ex_ease_in_quartf

 @fn double ex_ease_out_quart ( double _t )
 @sa ex_ease_in_quartf
 
 @fn float ex_ease_inout_quartf ( float _t ) 
 @sa ex_ease_in_quartf

 @fn double ex_ease_inout_quart ( double _t ) 
 @sa ex_ease_in_quartf

 @fn float ex_ease_outin_quartf ( float _t ) 
 @sa ex_ease_in_quartf

 @fn double ex_ease_outin_quart ( double _t ) 
 @sa ex_ease_in_quartf
*/// ------------------------------------------------------------------ 

extern float ex_ease_in_quartf ( float _t );
extern double ex_ease_in_quart ( double _t );

extern float ex_ease_out_quartf ( float _t );
extern double ex_ease_out_quart ( double _t );

extern float ex_ease_inout_quartf ( float _t ); 
extern double ex_ease_inout_quart ( double _t ); 

extern float ex_ease_outin_quartf ( float _t ); 
extern double ex_ease_outin_quart ( double _t ); 

// ------------------------------------------------------------------ 
/*! 
 @fn float ex_ease_in_quintf ( float _t )
 @param _t ratio range in [0,1]
 @return the ease result
 @details Easing equation function for a quintic (_t^5)

 @fn double ex_ease_in_quint ( double _t )
 @sa ex_ease_in_quintf

 @fn float ex_ease_out_quintf ( float _t )
 @sa ex_ease_in_quintf

 @fn double ex_ease_out_quint ( double _t )
 @sa ex_ease_in_quintf

 @fn float ex_ease_inout_quintf ( float _t )
 @sa ex_ease_in_quintf

 @fn double ex_ease_inout_quint ( double _t )
 @sa ex_ease_in_quintf

 @fn float ex_ease_outin_quintf ( float _t )
 @sa ex_ease_in_quintf

 @fn double ex_ease_outin_quint ( double _t )
 @sa ex_ease_in_quintf
*/// ------------------------------------------------------------------ 

extern float ex_ease_in_quintf ( float _t );
extern double ex_ease_in_quint ( double _t );

extern float ex_ease_out_quintf ( float _t );
extern double ex_ease_out_quint ( double _t );

extern float ex_ease_inout_quintf ( float _t );
extern double ex_ease_inout_quint ( double _t );

extern float ex_ease_outin_quintf ( float _t );
extern double ex_ease_outin_quint ( double _t );

// ------------------------------------------------------------------ 
/*! 
 @fn float ex_ease_in_sinef ( float _t )
 @param _t ratio range in [0,1]
 @return the ease result
 @details Easing equation function for a sinusoidal (sin(_t))

 @fn double ex_ease_in_sine ( double _t )
 @sa ex_ease_in_sinef

 @fn float ex_ease_out_sinef ( float _t )
 @sa ex_ease_in_sinef

 @fn double ex_ease_out_sine ( double _t )
 @sa ex_ease_in_sinef

 @fn float ex_ease_inout_sinef ( float _t )
 @sa ex_ease_in_sinef

 @fn double ex_ease_inout_sine ( double _t )
 @sa ex_ease_in_sinef

 @fn float ex_ease_outin_sinef ( float _t ) 
 @sa ex_ease_in_sinef

 @fn double ex_ease_outin_sine ( double _t ) 
 @sa ex_ease_in_sinef
*/// ------------------------------------------------------------------ 

extern float ex_ease_in_sinef ( float _t );
extern double ex_ease_in_sine ( double _t );

extern float ex_ease_out_sinef ( float _t );
extern double ex_ease_out_sine ( double _t );

extern float ex_ease_inout_sinef ( float _t );
extern double ex_ease_inout_sine ( double _t );

extern float ex_ease_outin_sinef ( float _t ); 
extern double ex_ease_outin_sine ( double _t ); 

// ------------------------------------------------------------------ 
/*! 
 @fn float ex_ease_in_expof ( float _t )
 @param _t ratio range in [0,1]
 @return the ease result
 @details Easing equation function for an exponential (2^_t)

 @fn double ex_ease_in_expo ( double _t )
 @sa ex_ease_in_expof

 @fn float ex_ease_out_expof ( float _t )
 @sa ex_ease_in_expof

 @fn double ex_ease_out_expo ( double _t )
 @sa ex_ease_in_expof

 @fn float ex_ease_inout_expof ( float _t )
 @sa ex_ease_in_expof

 @fn double ex_ease_inout_expo ( double _t )
 @sa ex_ease_in_expof

 @fn float ex_ease_outin_expof ( float _t )
 @sa ex_ease_in_expof

 @fn double ex_ease_outin_expo ( double _t )
 @sa ex_ease_in_expof
*/// ------------------------------------------------------------------ 

extern float ex_ease_in_expof ( float _t );
extern double ex_ease_in_expo ( double _t );

extern float ex_ease_out_expof ( float _t );
extern double ex_ease_out_expo ( double _t );

extern float ex_ease_inout_expof ( float _t );
extern double ex_ease_inout_expo ( double _t );

extern float ex_ease_outin_expof ( float _t );
extern double ex_ease_outin_expo ( double _t );

// ------------------------------------------------------------------ 
/*!
 @fn float ex_ease_in_circf ( float _t )
 @param _t ratio range in [0,1]
 @return the ease result
 @details Easing equation function for a circular (sqrt(1-_t^2))

 @fn double ex_ease_in_circ ( double _t )
 @sa ex_ease_in_circf

 @fn float ex_ease_out_circf ( float _t )
 @sa ex_ease_in_circf

 @fn double ex_ease_out_circ ( double _t )
 @sa ex_ease_in_circf

 @fn float ex_ease_inout_circf ( float _t ) 
 @sa ex_ease_in_circf

 @fn double ex_ease_inout_circ ( double _t ) 
 @sa ex_ease_in_circf

 @fn float ex_ease_outin_circf ( float _t )
 @sa ex_ease_in_circf

 @fn double ex_ease_outin_circ ( double _t )
 @sa ex_ease_in_circf
*/// ------------------------------------------------------------------ 

extern float ex_ease_in_circf ( float _t );
extern double ex_ease_in_circ ( double _t );

extern float ex_ease_out_circf ( float _t );
extern double ex_ease_out_circ ( double _t );

extern float ex_ease_inout_circf ( float _t ); 
extern double ex_ease_inout_circ ( double _t ); 

extern float ex_ease_outin_circf ( float _t );
extern double ex_ease_outin_circ ( double _t );

// ------------------------------------------------------------------ 
/*!
 @fn float ex_ease_in_elasticf ( float _t, float _a, float _p )
 @param _t ratio range in [0,1]
 @param a Amplitude.
 @param p Period.
 @return the ease result
 @details 
 Easing equation function for an elastic (exponentially decaying sine wave)
 recommand value: elastic (t, 0.1, 0.05)

 @fn double ex_ease_in_elastic ( double _t, double _a, double _p );
 @sa ex_ease_in_elasticf

 @fn float ex_ease_out_elasticf ( float _t, float _a, float _p );
 @sa ex_ease_in_elasticf

 @fn double ex_ease_out_elastic ( double _t, double _a, double _p );
 @sa ex_ease_in_elasticf

 @fn float ex_ease_inout_elasticf ( float _t, float _a, float _p ); 
 @sa ex_ease_in_elasticf

 @fn double ex_ease_inout_elastic ( double _t, double _a, double _p ); 
 @sa ex_ease_in_elasticf

 @fn float ex_ease_outin_elasticf ( float _t, float _a, float _p ); 
 @sa ex_ease_in_elasticf

 @fn double ex_ease_outin_elastic ( double _t, double _a, double _p ); 
 @sa ex_ease_in_elasticf
*/// ------------------------------------------------------------------ 

extern float ex_ease_in_elasticf ( float _t, float _a, float _p );
extern double ex_ease_in_elastic ( double _t, double _a, double _p );

extern float ex_ease_out_elasticf ( float _t, float _a, float _p );
extern double ex_ease_out_elastic ( double _t, double _a, double _p );

extern float ex_ease_inout_elasticf ( float _t, float _a, float _p ); 
extern double ex_ease_inout_elastic ( double _t, double _a, double _p ); 

extern float ex_ease_outin_elasticf ( float _t, float _a, float _p ); 
extern double ex_ease_outin_elastic ( double _t, double _a, double _p ); 

// ------------------------------------------------------------------ 
/*!
 @fn float ex_ease_in_backf ( float _t, float _s )
 @param _t ratio range in [0,1]
 @param s: Overshoot ammount: higher s means greater overshoot (0 produces cubic easing with no overshoot, and the default value of 1.70158 produces an overshoot of 10 percent).
 @return the ease result
 @details Easing equation function for a back (overshooting cubic easing: (s+1)*_t^3 - s*_t^2)

 @fn double ex_ease_in_back ( double _t, double _s );
 @sa ex_ease_in_backf

 @fn float ex_ease_out_backf ( float _t, float _s );
 @sa ex_ease_in_backf

 @fn double ex_ease_out_back ( double _t, double _s );
 @sa ex_ease_in_backf

 @fn float ex_ease_inout_backf ( float _t, float _s ); 
 @sa ex_ease_in_backf

 @fn double ex_ease_inout_back ( double _t, double _s ); 
 @sa ex_ease_in_backf

 @fn float ex_ease_outin_backf ( float _t, float _s ); 
 @sa ex_ease_in_backf

 @fn double ex_ease_outin_back ( double _t, double _s ); 
 @sa ex_ease_in_backf
*/// ------------------------------------------------------------------ 

extern float ex_ease_in_backf ( float _t, float _s );
extern double ex_ease_in_back ( double _t, double _s );

extern float ex_ease_out_backf ( float _t, float _s );
extern double ex_ease_out_back ( double _t, double _s );

extern float ex_ease_inout_backf ( float _t, float _s ); 
extern double ex_ease_inout_back ( double _t, double _s ); 

extern float ex_ease_outin_backf ( float _t, float _s ); 
extern double ex_ease_outin_back ( double _t, double _s ); 

// ------------------------------------------------------------------ 
/*!
 @fn float ex_ease_in_bouncef ( float _t, float _a )
 @param _t ratio range in [0,1]
 @param a Amplitude.
 @return the ease result
 @details Easing equation function for a bounce (exponentially decaying parabolic bounce)

 @fn double ex_ease_in_bounce ( double _t, double _a );
 @sa ex_ease_in_bouncef

 @fn float ex_ease_out_bouncef ( float _t, float _a );
 @sa ex_ease_in_bouncef

 @fn double ex_ease_out_bounce ( double _t, double _a );
 @sa ex_ease_in_bouncef

 @fn float ex_ease_inout_bouncef ( float _t, float _a ); 
 @sa ex_ease_in_bouncef

 @fn double ex_ease_inout_bounce ( double _t, double _a ); 
 @sa ex_ease_in_bouncef

 @fn float ex_ease_outin_bouncef ( float _t, float _a ); 
 @sa ex_ease_in_bouncef

 @fn double ex_ease_outin_bounce ( double _t, double _a ); 
 @sa ex_ease_in_bouncef
*/// ------------------------------------------------------------------ 

extern float ex_ease_in_bouncef ( float _t, float _a );
extern double ex_ease_in_bounce ( double _t, double _a );

extern float ex_ease_out_bouncef ( float _t, float _a );
extern double ex_ease_out_bounce ( double _t, double _a );

extern float ex_ease_inout_bouncef ( float _t, float _a ); 
extern double ex_ease_inout_bounce ( double _t, double _a ); 

extern float ex_ease_outin_bouncef ( float _t, float _a ); 
extern double ex_ease_outin_bounce ( double _t, double _a ); 

// ------------------------------------------------------------------ 
/*!
 @fn float ex_ease_smoothf ( float _t );
 @param _t ratio range in [0,1]
 @return the ease result
 @details _t<=0: 0 | 0<_t<1: 3*_t^2 - 2*t^3 | _t>=1: 1

 @fn double ex_ease_smooth ( double _t );
 @sa ex_ease_smoothf
*/// ------------------------------------------------------------------ 

extern float ex_ease_smoothf ( float _t );
extern double ex_ease_smooth ( double _t );

// ------------------------------------------------------------------ 
/*!
 @fn float ex_ease_fadef ( float _t );
 @param _t ratio range in [0,1]
 @return the ease result
 @details _t<=0: 0 | 0<_t<1: 6*_t^5 - 15*_t^4 + 10*_t^3 | _t>=1: 1

 @fn double ex_ease_fade ( double _t );
 @sa ex_ease_fadef
*/// ------------------------------------------------------------------ 

extern float ex_ease_fadef ( float _t );
extern double ex_ease_fade ( double _t );

// ------------------------------------------------------------------ 
/*!
 @fn float ex_ease_in_curvef ( float _t )
 @param _t ratio range in [0,1]
 @return the ease result
 @details 
 Easing function that starts growing slowly, then increases in speed. At the end of the curve the speed will be constant.
 SmoothBegin blends Smooth and Linear Interpolation.
 Progress 0 - 0.3      : Smooth only
 Progress 0.3 - ~ 0.5  : Mix of Smooth and Linear
 Progress ~ 0.5  - 1   : Linear only

 @fn double ex_ease_in_curve ( double _t )
 @sa ex_ease_in_curvef

 @fn float ex_ease_out_curvef ( float _t )
 @details Easing function that starts growing steadily, then ends slowly. 
 The speed will be constant at the beginning of the curve.
 @sa ex_ease_in_curvef

 @fn double ex_ease_out_curve ( double _t )
 @details Easing function that starts growing steadily, then ends slowly. 
 The speed will be constant at the beginning of the curve.
 @sa ex_ease_in_curvef

 @fn float ex_ease_curve_sinef ( float _t ); 
 @details Easing function where the value grows sinusoidally. 
 @note that the calculated  end value will be 0 rather than 1.
 @sa ex_ease_in_curvef

 @fn double ex_ease_curve_sine ( double _t ); 
 @details Easing function where the value grows sinusoidally. 
 @note that the calculated  end value will be 0 rather than 1.
 @sa ex_ease_in_curvef

 @fn float ex_ease_curve_cosinef ( float _t ); 
 @details Easing function where the value grows cosinusoidally. 
 @note that the calculated start value will be 0.5 and the end value will be 0.5 contrary to the usual 0 to 1 easing curve.
 @sa ex_ease_in_curvef

 @fn double ex_ease_curve_cosine ( double _t ); 
 @details Easing function where the value grows cosinusoidally. 
 @note that the calculated start value will be 0.5 and the end value will be 0.5 contrary to the usual 0 to 1 easing curve.
 @sa ex_ease_in_curvef

*/// ------------------------------------------------------------------ 

extern float ex_ease_in_curvef ( float _t );
extern double ex_ease_in_curve ( double _t );

extern float ex_ease_out_curvef ( float _t );
extern double ex_ease_out_curve ( double _t );

extern float ex_ease_curve_sinef ( float _t ); 
extern double ex_ease_curve_sine ( double _t ); 

extern float ex_ease_curve_cosinef ( float _t ); 
extern double ex_ease_curve_cosine ( double _t ); 

//! @}

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 

// #################################################################################
#endif // END EASE_CURVE_H_1290652786
// #################################################################################


