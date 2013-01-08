// ======================================================================================
// File         : probability.h
// Author       : Wu Jie 
// Last Change  : 02/09/2011 | 19:45:06 PM | Wednesday,February
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef PROBABILITY_H_1297251909
#define PROBABILITY_H_1297251909
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" { 
#endif
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// _weights         // relative weights of each class
// _num_weights     // number of weights
// _samples         // sample as an array of class indices
// _num_samples     // number of samples
//
// Usage:
//   int samples[2000];
//   float weights[]     = { 0.12,    0.4,     0.4,      0.07,  0.9      };
//   const char *items[] = { "sword", "knife", "kanata", "axe", "shield" };
//   ex_walkers_alias( weights, EX_ARRAY_COUNT(weights), 
//                     samples, EX_ARRAY_COUNT(samples) );
//   int i = (int)ex_range_randf(0.0f,2000.0f);
//   const char *drop_item = items[i];
// ------------------------------------------------------------------ 

void ex_walkers_alias( const float *_weights, int _num_weights,
                       int *_samples, int _num_samples );

// ------------------------------------------------------------------ 
// Desc: 
// Usage:
//   float weights[]     = { 0.12,    0.4,     0.4,      0.07,  0.9      };
//   const char *items[] = { "sword", "knife", "kanata", "axe", "shield" };
//   float cdf[5];
//   ex_weights_to_cdf( cdf, weights, EX_ARRAY_COUNT(weights) );
//   int i = ex_cdf_gen_index(cdf,EX_ARRAY_COUNT(cdf));
//   const char *drop_item = items[i];
// ------------------------------------------------------------------ 

// NOTE: you must garantee cdf length equals or larger than _num_weights
// NOTE: it is strongly recommended you sort the _weights by deccending order, which can make average search faster.
void ex_weights_to_cdf( float *_cdf, const float *_weights, int _num_weights );
int ex_cdf_gen_index( float *_cdf, int _num_cdf );

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 

// #################################################################################
#endif // END PROBABILITY_H_1297251909
// #################################################################################


