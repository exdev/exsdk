// ======================================================================================
// File         : timespan.h
// Author       : Wu Jie 
// Last Change  : 12/30/2010 | 21:03:45 PM | Thursday,December
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef TIMESPAN_H_1293714226
#define TIMESPAN_H_1293714226
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" { 
#endif
// ######################### 

// ------------------------------------------------------------------ 
// Desc: timespan_t
// ------------------------------------------------------------------ 

// NOTE: why timespan is int64 instead of uint64 is because timespan could be minus when sub
#define EX_TIMESPAN_INFINITY EX_INT64_MAX 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern timespan_t ex_timespan_from ( int _seconds, int _milliseconds );
extern timespan_t ex_timespan_from2 ( int _days, int _hours, int _miniutes, int _seconds, int _milliseconds );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern timespan_t ex_timespan_from_secs_f32 ( float _s );
extern timespan_t ex_timespan_from_secs_f64 ( double _s );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern timespan_t ex_timespan_from_msecs_f32 ( float _ms );
extern timespan_t ex_timespan_from_msecs_f64 ( double _ms );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern double ex_timespan_total_days ( timespan_t _ts );
extern double ex_timespan_total_hours ( timespan_t _ts );
extern double ex_timespan_total_minutes ( timespan_t _ts );
extern double ex_timespan_total_seconds ( timespan_t _ts );
extern double ex_timespan_total_mseconds ( timespan_t _ts );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern int64 ex_timespan_to_secs ( timespan_t _ts );
extern int64 ex_timespan_to_msecs ( timespan_t _ts );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern void ex_timespan_to ( timespan_t _ts, 
                             int *_d, 
                             int *_h, 
                             int *_m, 
                             int *_s, 
                             int *_ms, 
                             int *_us );

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 

// #################################################################################
#endif // END TIMESPAN_H_1293714226
// #################################################################################
