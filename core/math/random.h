// ======================================================================================
// File         : random.h
// Author       : Wu Jie 
// Last Change  : 11/24/2010 | 10:38:46 AM | Wednesday,November
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef RANDOM_H_1290566332
#define RANDOM_H_1290566332
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" { 
#endif
// ######################### 

//! @defgroup random api to generate random values
//! @ingroup Math
//! @{

///////////////////////////////////////////////////////////////////////////////
// function defines
///////////////////////////////////////////////////////////////////////////////


// ------------------------------------------------------------------ 
/*! 
 @fn static inline void ex_srand( uint _seed )
 @param _seed 
 @details 
 This function establishes _seed as the seed for a new series of 
 pseudo-random numbers. 
 @note 
 To produce a different pseudo-random series each time program starts, 
 do: srand (time (0))
*/// ------------------------------------------------------------------ 

static inline void ex_srand( uint _seed ) { srand(_seed); }

// ------------------------------------------------------------------ 
/*! 
 @fn static inline float ex_unit_randf()
 @return the random value
 @details 
 get random value in range of [0,1], the return type is float.

 @fn static inline double ex_unit_rand()
 @return the random value
 @details 
 get random value in range of [0,1], the return type is double.
*/// ------------------------------------------------------------------ 

static inline float ex_unit_randf() { return (float)rand()/(float)RAND_MAX; }
static inline double ex_unit_rand() { return rand()/RAND_MAX; }

// ------------------------------------------------------------------ 
/*! 
 @fn static inline ex_unit2_randf ()
 @return the random value
 @details 
 get random value in range of [-1,1], the return type is float.

 @fn static inline double ex_unit2_rand ()
 @return the random value
 @details 
 get random value in range of [-1,1], the return type is double.
*/// ------------------------------------------------------------------ 

static inline float ex_unit2_randf() { return ( 2.0f * ex_unit_randf() ) - 1.0f; }
static inline double ex_unit2_rand() { return ( 2.0 * ex_unit_randf() ) - 1.0; }

// ------------------------------------------------------------------ 
/*! 
 @fn static inline float ex_range_randf( float _low_bound, float _high_bound )
 @param _low_bound low bound
 @param _high_bound high bound
 @return the random value
 @details 
 get random value in range of [_low_bound,_high_bound], the return type is float.

 @fn static inline double ex_range_rand( double _low_bound, double _high_bound )
 @return the random value
 @details 
 get random value in range of [_low_bound,_high_bound], the return type is double.
*/// ------------------------------------------------------------------ 

static inline float ex_range_randf( float _low_bound, float _high_bound ) { 
    ex_assert( _low_bound < _high_bound, "low bound should less than high bound" );
    return ( ( _high_bound - _low_bound ) * ex_unit_randf() ) + _low_bound;
}
static inline double ex_range_rand( double _low_bound, double _high_bound ) {
    ex_assert( _low_bound < _high_bound, "low bound should less than high bound" );
    return ( ( _high_bound - _low_bound ) * ex_unit_randf() ) + _low_bound;
}

// TODO:

// ex_range_randi	 Returns randome integer in range of [_low_bound,_high_bound)
// insideUnitSphere	 Returns a random point inside a sphere with radius 1 (Read Only).
// insideUnitCircle	 Returns a random point inside a circle with radius 1 (Read Only).
// onUnitSphere	 Returns a random point on the surface of a sphere with radius 1 (Read Only).
// rotation Returns a random rotation, Quaternion (Read Only).

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 

//! @}

// #################################################################################
#endif // END RANDOM_H_1290566332
// #################################################################################
