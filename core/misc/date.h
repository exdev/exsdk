// ======================================================================================
// File         : date.h
// Author       : Wu Jie 
// Last Change  : 12/30/2010 | 20:10:15 PM | Thursday,December
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef DATE_H_1293711048
#define DATE_H_1293711048
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// NOTE: you can directly compare date_t 
//       you can add/sub days directly in date_t
//       you can sub two date_t which will get days between them
//       you can't add two date_t
typedef uint date_t; // we use julian date
#define EX_DATE_INVALID -1

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern const char *ex_week_day_name ( uint _wday );
extern const char *ex_month_name ( uint _month );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern bool ex_is_valid_date ( uint _year, uint _month, uint _day );

// NOTE: to check date_t is leap, just use: ex_is_leap_year( ex_date_year(_date) )   
extern bool ex_is_leap_year ( uint _year );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern date_t ex_date_from ( uint _year, uint _month, uint _day );
// NOTE: if you don't need the out parameter, set it to NULL 
extern void ex_date_to ( date_t _date, int *_year, int *_month, int *_day );

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern uint ex_date_day_of_week ( date_t _date );
extern uint ex_date_day_of_year ( date_t _date );
extern uint ex_date_days_in_month ( date_t _date );

// #################################################################################
#endif // END DATE_H_1293711048
// #################################################################################


