// ======================================================================================
// File         : macro.h
// Author       : Wu Jie 
// Last Change  : 06/26/2010 | 22:02:42 PM | Saturday,June
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef MACRO_H_1277560964
#define MACRO_H_1277560964
// #################################################################################

// ------------------------------------------------------------------
// Desc: Expand Macro
//  Expand the macro for second scaned pre-process. 
//  Refer to Gcc-4.1.1\Manual\Cpp\Predefined-Macros.htm
// ------------------------------------------------------------------

#define EX_MACRO_EXPAND( macro_name, ... ) macro_name( __VA_ARGS__ )
#define EX_MACRO_EXPAND_SIMPLE( macro_name ) macro_name

// ------------------------------------------------------------------
// Desc: Macro String
// ------------------------------------------------------------------

#define EX_STRING(str) #str 
#define EX_STRING_EXPAND(str) EX_STRING(str)

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

#define EX_UNUSED(_param) (void)_param

// ------------------------------------------------------------------
// Desc: get bit number of a _value
// ------------------------------------------------------------------

#define EX_BIT_COUNT( _value ) sizeof(_value)*8

// ------------------------------------------------------------------
// Desc: rotate bit at _pos
// ------------------------------------------------------------------

#define EX_BIT_ROT( _val, _pos ) (((_val)<<(_pos)) | ((_val)>>(32-(_pos))))

// ------------------------------------------------------------------
// Desc: get va string
// ------------------------------------------------------------------

#define EX_GET_VA_STRING( _buffer, _count, _fmt )                                                   \
    {                                                                                               \
        va_list args;                                                                               \
        va_start( args, _fmt );                                                                     \
        vsnprintf ( _buffer, _count, _fmt, args );                                                  \
        va_end(args);                                                                               \
        ex_assert_slow( strlen(_buffer) <= _count, "extended string have over flow the buffer" );   \
    }

// ------------------------------------------------------------------
// Desc: get va string with result
// ------------------------------------------------------------------

#define EX_GET_VA_STRING_WITH_RESULT( _buffer, _count, _fmt, result )                                       \
    {                                                                                                       \
        va_list args;                                                                                       \
        va_start( args, _fmt );                                                                             \
        *result = vsnprintf( _buffer, _count, _fmt, args );                                                 \
        va_end(args);                                                                                       \
    }

// ------------------------------------------------------------------
// Desc: Floor Align
// Example: val = 19, align = 8. EX_ALIGN_FLOOR(19,8) = 16
// ------------------------------------------------------------------

#define EX_ALIGN_FLOOR(val, align)      ((val) & ~(align-1))

// ------------------------------------------------------------------
// Desc: Round Align
// Example: val = 19, align = 8. EX_ALIGN_ROUND(12,8) = 24
// ------------------------------------------------------------------

#define EX_ALIGN_ROUND(val, align)      (((val) + (align-1)) & ~(align-1))

// ------------------------------------------------------------------
// Desc: Get the array element count
//  The const value calculate should be optimaized by compiler, so this macro do not take any calculation in
//  runtime, all the result will be calculated in the pre-process.
// ------------------------------------------------------------------

#define EX_ARRAY_COUNT(arr)  (sizeof(arr)/sizeof(arr[0]))

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

#define EX_SIZEOF(_s,_m) ((size_t) sizeof(((_s *)0)->_m))

// ------------------------------------------------------------------
// Desc: Memory Allocate Size for sizeof(uint8) = 1BYTE
// ------------------------------------------------------------------

#define EX_KB(nb)   ((unsigned)(nb)*1024)   // KiloBytes = 2^10
#define EX_MB(nb)   EX_KB((nb)*1024)        // MegaBytes = 2^20
#define EX_GB(nb)   EX_MB((nb)*1024)        // GegaBytes = 2^30

// #################################################################################
#endif // END MACRO_H_1277560964
// #################################################################################


