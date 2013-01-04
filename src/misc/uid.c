// ======================================================================================
// File         : uid.c
// Author       : Wu Jie 
// Last Change  : 01/27/2011 | 01:04:10 AM | Thursday,January
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
// macro
///////////////////////////////////////////////////////////////////////////////

#define __MSECS_PER_DAY  (86400000) /*24 * __MSECS_PER_HOUR*/

static date_t __start_date;
static date_t __last_date;
static dtime_t __last_dtime;

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_uid_init () {
    __start_date = ex_date_from( 2010, 1, 1 ); 
    __last_date = __start_date;
    __last_dtime = ex_dtime_from(0,0,0,0);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ex_uid_t ex_generate_uid () {
    static int __offset = 0;

    date_t cur_date;
    dtime_t cur_dtime;
    int64 delta_day, delta_ms;
    timespan_t ts;
    uint64 serverID, offset, days, msecs; 

#if (EX_PLATFORM == EX_WIN32)
    SYSTEMTIME time;
    GetLocalTime(&time);
    cur_date = ex_date_from( time.wYear, time.wMonth, time.wDay );
    cur_dtime = ex_dtime_from( time.wHour, time.wMinute, time.wSecond, time.wMilliseconds );
#else
    time_t now = time(NULL);
    struct tm *now_ts = localtime(&now);
    struct timeval now_ms;
    gettimeofday(&now_ms, NULL);

    cur_date = ex_date_from( 1900+now_ts->tm_year, now_ts->tm_mon+1, now_ts->tm_mday );
    cur_dtime = ex_dtime_from( now_ts->tm_hour, now_ts->tm_min, now_ts->tm_sec, now_ms.tv_usec/1000 );
#endif

    // if we have time conflict, increase offset to avoid same ID.
    if ( __last_date == cur_date && __last_dtime == cur_dtime )
        ++__offset;
    else // else, we need reset the offset.
        __offset = 0;

    // if the offset over 1024, we will have same uid fatal error!!
    if ( __offset >= 1024 ) {
        ex_error ("uid generate error, generate over 1024 uid in 1-ms.");
        return EX_UID_INVALID;
    }
    __last_date = cur_date;
    __last_dtime = cur_dtime;

    // get time ts from uid_start time to current time.
    delta_day = (int64)(cur_date - __start_date);
    delta_ms = (int64)(cur_dtime - 0/*start_dtime*/);
    ts = (delta_day * __MSECS_PER_DAY + delta_ms) * 1000;

    // TODO: 6-bits for server ID. (0~63). which means we support maximum 63 servers.
    serverID = 0;
    offset = __offset;
    days = (uint64)ex_timespan_total_days(ts); // get how many days.
    msecs = cur_dtime;

    //
    return ( serverID   & 0xff )       << 58 
         | ( offset     & 0xffff )     << 48 
         | ( days       & 0x0fffffff ) << 32 
         | ( msecs      & 0xffffffff ); 
}

