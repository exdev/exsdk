// ======================================================================================
// File         : timespan.c
// Author       : Wu Jie 
// Last Change  : 12/30/2010 | 21:03:56 PM | Thursday,December
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

#define __USECS_PER_MSEC (1000)
#define __USECS_PER_SEC  (1000000)      /*__USECS_PER_MSEC * 1000*/
#define __USECS_PER_MIN  (60000000)     /*__USECS_PER_SEC  * 60*/
#define __USECS_PER_HOUR (360000000)    /*__USECS_PER_MIN  * 60*/
#define __USECS_PER_DAY  (8640000000)   /*__USECS_PER_HOUR * 24*/

///////////////////////////////////////////////////////////////////////////////
// function defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

timespan_t ex_timespan_from ( int _seconds, int _milliseconds )
{
    return _seconds * __USECS_PER_SEC + _milliseconds * __USECS_PER_MSEC;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

timespan_t ex_timespan_from2 ( int _days, 
                               int _hours, 
                               int _miniutes, 
                               int _seconds, 
                               int _milliseconds ) 
{
    return _days * __USECS_PER_DAY
        + _hours * __USECS_PER_HOUR
        + _miniutes * __USECS_PER_MIN
        + _seconds * __USECS_PER_SEC
        + _milliseconds * __USECS_PER_MSEC;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

timespan_t ex_timespan_from_secs_f32 ( float _s ) {
    int64 int_sec = (int64)ex_truncf(_s);
    float f_ms = (_s - int_sec) * 1000.0f;
    int64 int_ms = (int64)ex_truncf(f_ms);
    int64 int_us = (int64)ex_roundf((f_ms - int_ms) * 1000.0f);

    return int_sec * __USECS_PER_SEC
        + int_ms  * __USECS_PER_MSEC
        + int_us;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

timespan_t ex_timespan_from_secs_f64 ( double _s ) {
    int64 int_sec = (int64)ex_trunc(_s);
    float f_ms = (_s - int_sec) * 1000.0;
    int64 int_ms = (int64)ex_trunc(f_ms);
    int64 int_us = (int64)ex_round((f_ms - int_ms) * 1000.0);

    return int_sec * __USECS_PER_SEC
        + int_ms  * __USECS_PER_MSEC
        + int_us;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

timespan_t ex_timespan_from_msecs_f32 ( float _ms ) {
    int64 int_ms = (int64)ex_truncf(_ms);
    return int_ms * __USECS_PER_MSEC + (int64)ex_roundf((_ms - int_ms) * 1000.0f) ;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

timespan_t ex_timespan_from_msecs_f64 ( double _ms ) {
    int64 int_ms = (int64)ex_trunc(_ms);
    return int_ms * __USECS_PER_MSEC + (int64)ex_round((_ms - int_ms) * 1000.0) ;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

double ex_timespan_total_days ( timespan_t _ts ) {
    return (double)_ts / (double)__USECS_PER_DAY;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

double ex_timespan_total_hours ( timespan_t _ts ) {
    return (double)_ts / (double)__USECS_PER_HOUR;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

double ex_timespan_total_minutes ( timespan_t _ts ) {
    return (double)_ts / (double)__USECS_PER_MIN;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

double ex_timespan_total_seconds ( timespan_t _ts ) {
    return (double)_ts / (double)__USECS_PER_SEC;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

double ex_timespan_total_mseconds ( timespan_t _ts ) {
    return (double)_ts / (double)__USECS_PER_MSEC;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int64 ex_timespan_to_secs ( timespan_t _ts ) {
    return (int64)ex_round( ex_timespan_total_seconds(_ts) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int64 ex_timespan_to_msecs ( timespan_t _ts ) {
    return (int64)ex_round( ex_timespan_total_mseconds(_ts) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_timespan_to ( timespan_t _ts, 
                      int *_d, 
                      int *_h, 
                      int *_m, 
                      int *_s, 
                      int *_ms, 
                      int *_us ) {
    int64 mod_day = _ts % __USECS_PER_DAY;
    int64 mod_hour = mod_day % __USECS_PER_HOUR;
    int64 mod_min = mod_hour % __USECS_PER_MIN;
    int64 mod_sec = mod_min % __USECS_PER_SEC;
    int64 mod_msec = mod_sec % __USECS_PER_MSEC;

    if ( _d ) *_d = (int)(_ts / __USECS_PER_DAY); 
    if ( _h ) *_h = (int)(mod_day / __USECS_PER_HOUR); 
    if ( _m ) *_m = (int)(mod_hour / __USECS_PER_MIN); 
    if ( _s ) *_s = (int)(mod_min / __USECS_PER_SEC); 
    if ( _ms ) *_ms = (int)(mod_sec / __USECS_PER_MSEC); 
    if ( _us ) *_us = (int)mod_msec;
}
