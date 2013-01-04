// ======================================================================================
// File         : hash.h
// Author       : Wu Jie 
// Last Change  : 06/28/2010 | 11:13:56 AM | Monday,June
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef HASH_H_1277694838
#define HASH_H_1277694838
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" {
#endif
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "CRC.h"

///////////////////////////////////////////////////////////////////////////////
// config
///////////////////////////////////////////////////////////////////////////////

#define EX_HASH_PAUL 0x01
#define EX_HASH_BOB2 0x02
#define EX_HASH_BOB3 0x03
#define EX_HASH_CRC  0x04

// setup as you wish
#define EX_HASH_METHOD EX_HASH_BOB3
#define EX_HASH_SEED    0xFF

///////////////////////////////////////////////////////////////////////////////
// Conclusion
///////////////////////////////////////////////////////////////////////////////

/// This library offers many different hashing function with different collision efficiency & execution speed. 
// - CRC   : Classic Cyclic Redundancy check
// - CRC4  : Same as CRC, but process 4 bytes at a time and is faster (while giving the same value than CRC)
// - Bob2  : Algorithm from Doctor Dobb's web site (http://burtleburtle.net/bob/hash/doobs.html)
// - Bob3  : Algorithm from Doctor Dobb's web site (http://burtleburtle.net/bob/hash/doobs.html)
// - Paul  : Written by Paul Hsieh (http://www.azillionmonkeys.com/qed/hash.html)

// Speed (vs CRC):
// - CRC   : 1.00 (reference speed)
// - CRC4  : 2.08 times faster than CRC
// - Bob2  : 1.81 times faster than CRC
// - Bob3  : 3.00 times faster than CRC TODO: not test
// - Paul  : 2.85 times faster than CRC

// Average Collisions generated when parsing 'Iliad' by Homer & 'The Holy Bible'
// - CRC   : 0% collision on an average dictionary of around 30000 words
// - CRC4  : Same as CRC
// - Bob2  : 0% collision on an average dictionary of around 30000 words
// - Bob3  : 0% collision on an average dictionary of around 30000 words TODO: not test
// - Paul  : 0.02% collision on an average dictionary of around 30000 words

///////////////////////////////////////////////////////////////////////////////
//  Bob Jenkins' Hash 2
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern uint32 ex_hashbob2( const uint8 *_data, uint32 _len, uint32 _seed );

///////////////////////////////////////////////////////////////////////////////
//  Bob Jenkins' Hash 3
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: ex_hashword 
// ------------------------------------------------------------------

extern uint32 ex_hashword ( const uint32 *_data, uint32 _len, uint32 _seed );
extern void ex_hashword2 ( const uint32 *_data, uint32 _len, uint32 *_seed1, uint32 *_seed2 );

// ------------------------------------------------------------------
// Desc: ex_hashlittle
// ------------------------------------------------------------------

extern uint32 ex_hashlittle ( const void *_data, uint32 _len, uint32 _seed );
extern void ex_hashlittle2 ( const void *_data, uint32 _len, uint32 *_seed1, uint32 *_seed2 ); 

// ------------------------------------------------------------------
// Desc: ex_hashbig
// ------------------------------------------------------------------

extern uint32 ex_hashbig ( const void *_data, uint32 _len, uint32 _seed );
extern void ex_hashbig2 ( const void *_data, uint32 _len, uint32 *_seed1, uint32 *_seed2 );

// ------------------------------------------------------------------
// Desc: ex_hashbob3 ( 1 seed )
// ------------------------------------------------------------------

// uint32
static inline uint32 ex_hashbob3( const uint32 *_data, uint32 _len, uint32 _seed ) { return ex_hashword( _data, _len, _seed ); }

// void * 
static inline uint32 ex_hashbob3_ptr( const void *_data, uint32 _len, uint32 _seed )
{
#if (EX_BYTEORDER == EX_LIL_ENDIAN)
    return ex_hashlittle( _data, _len, _seed );
#else
    return ex_hashbig( _data, _len, _seed );
#endif
}

// ------------------------------------------------------------------
// Desc: hashbob3_2seed ( 2 seed )
// ------------------------------------------------------------------

// uint32
static inline void ex_hashbob3_2( const uint32 *_data, uint32 _len, uint32 *_seed1, uint32 *_seed2 ) { ex_hashword2( _data, _len, _seed1, _seed2 ); }

// void * 
static inline void ex_hashbob3_ptr2 ( const uint32 *_data, uint32 _len, uint32 *_seed1, uint32 *_seed2 )
{
#if (EX_BYTEORDER == EX_LIL_ENDIAN)
    ex_hashlittle2( _data, _len, _seed1, _seed2 );
#else
    ex_hashbig2( _data, _len, _seed1, _seed2 );
#endif
}

///////////////////////////////////////////////////////////////////////////////
//  Paul Hsieh's Hash
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

extern uint32 ex_hashpaul ( const uint8 *_data, uint32 _len );

///////////////////////////////////////////////////////////////////////////////
// CRC Hash
///////////////////////////////////////////////////////////////////////////////

// uint32 
static inline uint32 ex_hashcrc ( int _crcSize, const uint8 *_data, uint32 _len )
{
    return ex_calc_CRC ( _crcSize, _data, _len );
}

// string
static inline uint32 ex_hashcrc_str ( int _crcSize, const char *_str )
{
    return ex_calc_CRC_str ( _crcSize, _str );
}

///////////////////////////////////////////////////////////////////////////////
//  General Hash Method
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: EX_HASH user configure
// ------------------------------------------------------------------

#define EX_HASH_METHOD  EX_HASH_BOB3

// ------------------------------------------------------------------
// Desc: string with length 
// ------------------------------------------------------------------

// private
static inline uint32 __ex_hashstr ( const void *_str, uint32 _bytes )
{
#if (EX_HASH_METHOD == EX_HASH_PAUL)
    return ex_hashpaul( (uint8 *)_str, _bytes );
#elif (EX_HASH_METHOD == EX_HASH_BOB2)
    return ex_hashbob2( (uint8 *)_str, _bytes, EX_HASH_SEED );
#elif (EX_HASH_METHOD == EX_HASH_BOB3)
    return ex_hashbob3_ptr( (void *)_str, _bytes, EX_HASH_SEED );
#elif (EX_HASH_METHOD == EX_HASH_CRC)
    return ex_hashcrc_str( 32, _str );
#endif
}

// ------------------------------------------------------------------
// Desc: string without length
// ------------------------------------------------------------------

// const char * 
static inline uint32 ex_hashstr( const char *_str ) { return __ex_hashstr ( _str, strlen(_str) ); }

// const wchar * 
static inline uint32 ex_hashstr_w( const wchar_t *_str ) { return __ex_hashstr( _str, wcslen(_str) * 2 ); }

// ------------------------------------------------------------------
// Desc: hashuse string
// ------------------------------------------------------------------

static inline uint32 _hashuse( int _method, const void *_str, uint32 _bytes ) {
    switch( _method ) {
    case EX_HASH_PAUL:
        return ex_hashpaul( (uint8 *)_str, _bytes );

    case EX_HASH_BOB2:
        return ex_hashbob2( (uint8 *)_str, _bytes, EX_HASH_SEED );

    case EX_HASH_BOB3:
        return ex_hashbob3_ptr( (void *)_str, _bytes, EX_HASH_SEED );

    case EX_HASH_CRC:
        return ex_hashcrc ( 32, (uint8 *)_str, _bytes );

    default:
        ex_assert( false, "hash method not found!" ); // NOTE: can't use ex_warning at header define before Debug/Log.h
        return 0;
    }
}

// ------------------------------------------------------------------
// Desc: hashuse void *
// ------------------------------------------------------------------

// const char *
static inline uint32 ex_hashuse( int _method, const char *_str )
{
    return _hashuse( _method, _str, strlen(_str) );
}

// const wchar * 
static inline uint32 ex_hashuse_w( int _method, const wchar_t *_str )
{
    return _hashuse( _method, _str, wcslen(_str) * 2 );
}

// ######################### 
#ifdef __cplusplus
} // end extern "C"
#endif
// ######################### 

// #################################################################################
#endif // END HASH_H_1277694838
// #################################################################################
