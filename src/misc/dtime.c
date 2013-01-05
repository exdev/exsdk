// ======================================================================================
// File         : dtime.c
// Author       : Wu Jie 
// Last Change  : 12/31/2010 | 14:16:34 PM | Friday,December
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

#define __MSECS_PER_SEC  (1000)
#define __MSECS_PER_MIN  (60000)    /*60 * __MSECS_PER_SEC*/
#define __MSECS_PER_HOUR (3600000)  /*60 * __MSECS_PER_MIN*/
#define __MSECS_PER_DAY  (86400000) /*24 * __MSECS_PER_HOUR*/

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static uint __dtime_add_msecs ( dtime_t _dtime, int64 _ms ) 
{
    int64 msecs = ( _dtime + _ms ) % __MSECS_PER_DAY;
    msecs = msecs < 0 ? __MSECS_PER_DAY + msecs : msecs;
    return (uint)msecs;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static uint __dtime_add_secs ( dtime_t _dtime, int _secs ) 
{
    return __dtime_add_msecs( _dtime, _secs * 1000 );
}

///////////////////////////////////////////////////////////////////////////////
// functions
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_is_valid_dtime ( uint _hour, uint _min, uint _secs, uint _ms ) {
    return _hour < 24 && _min < 60 && _secs < 60 && _ms < 1000;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_is_valid_dtime2 ( uint _ms ) {
    return _ms < __MSECS_PER_DAY;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

dtime_t ex_dtime_from ( uint _hour, uint _min, uint _secs, uint _ms ) {
    if ( !ex_is_valid_dtime( _hour, _min, _secs, _ms ) ) {
        ex_warning ( "can't set time (%dh,%dm,%ds,%dms). the value is invalid!", _hour, _min, _secs, _ms );
        return EX_DTIME_INVALID;
    }
    return _hour*__MSECS_PER_HOUR 
        + _min*__MSECS_PER_MIN 
        + _secs*__MSECS_PER_SEC 
        + _ms;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint ex_dtime_hours ( dtime_t _dtime ) {
    return _dtime / __MSECS_PER_HOUR;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint ex_dtime_minutes ( dtime_t _dtime ) {
    uint mod_hour = _dtime % __MSECS_PER_HOUR;
    return mod_hour / __MSECS_PER_MIN;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint ex_dtime_seconds ( dtime_t _dtime ) {
    uint mod_hour = _dtime % __MSECS_PER_HOUR;
    uint mod_min = mod_hour % __MSECS_PER_MIN;
    return mod_min / __MSECS_PER_SEC;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint ex_dtime_mseconds ( dtime_t _dtime ) {
    uint mod_hour = _dtime % __MSECS_PER_HOUR;
    uint mod_min = mod_hour % __MSECS_PER_MIN;
    uint mod_sec = mod_min % __MSECS_PER_SEC;
    return mod_sec;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

uint64 ex_dtime_to_usecs ( dtime_t _dtime ) {
    return _dtime * 1000;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

dtime_t ex_dtime_add ( dtime_t _dtime, timespan_t _ts )
{
    return __dtime_add_msecs ( _dtime, ex_timespan_to_msecs(_ts) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

dtime_t ex_dtime_sub ( dtime_t _dtime, timespan_t _ts )
{
    return __dtime_add_msecs ( _dtime, -ex_timespan_to_msecs(_ts) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

timespan_t ex_dtime_timespan ( dtime_t _from, dtime_t _to ) 
{
    if ( _from > _to )
        return (int64)((_to + __MSECS_PER_DAY - _from) * 1000);
    else
        return (int64)((_to - _from) * 1000);
}
