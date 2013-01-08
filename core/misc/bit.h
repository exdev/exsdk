// ======================================================================================
// File         : bit.h
// Author       : Wu Jie 
// Last Change  : 06/28/2010 | 10:53:23 AM | Monday,June
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef BIT_H_1277693605
#define BIT_H_1277693605
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" {
#endif
// ######################### 

// ------------------------------------------------------------------ 
// Desc: ex_pow2 
// ------------------------------------------------------------------ 

static inline uint32 ex_pow2 ( uint32 _count ) { return ((uint32)1<<_count); }

// ------------------------------------------------------------------
// Desc: Detect is power of 2 or not.
//  If the _value is power of 2, then it is aligned
// ------------------------------------------------------------------

static inline bool ex_is_pow_of_2 ( uint _value ) {
    return !((_value-1) & _value);
}

// ------------------------------------------------------------------
// Desc: Detect is aligned or not.
//  If the mod of the _value with _align is 0, then it is aligned
// ------------------------------------------------------------------

static inline bool ex_is_aligned ( uint _value, uint _align ) {
    ex_assert( ex_is_pow_of_2(_align), "_align must be pow of 2" );
    return ( (_value & (_align-1)) == 0 );
}

// ------------------------------------------------------------------
// Desc: ex_bitmask
// ------------------------------------------------------------------

static inline uint32 ex_bitmask( uint32 _count ) {
    return ex_pow2(_count)-1;
}

// ------------------------------------------------------------------
// Desc: use bits from 0 to _count.
// ------------------------------------------------------------------

static inline uint32 ex_usebits ( uint32 _value, uint32 _count )
{
    return (_value & ex_bitmask(_count));
}

// ------------------------------------------------------------------
// Desc: get bit at _bit_pos
// ------------------------------------------------------------------

static inline uint32 ex_getbit ( uint32 _value, uint32 _bit_pos )
{
    return (_value & ex_pow2(_bit_pos));
}

///////////////////////////////////////////////////////////////////////////////
// bit rotation
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline uint32 ex_bit_rotl ( uint32 _value, uint32 _rot_count ) {
    const uint size = sizeof(uint32) * 4;
    _rot_count %= size;
    return (_value << _rot_count) | (_value >> (size - _rot_count));
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline uint32 ex_bit_rotr ( uint32 _value, uint32 _rot_count ) {
    const uint size = sizeof(uint32) * 4;
    _rot_count %= size;
    return (_value >> _rot_count) | (_value << (size - _rot_count));
}

///////////////////////////////////////////////////////////////////////////////
// 64-bit op
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline uint64 ex_gen_uint64 ( uint32 _highVal, uint32 _lowVal ) {
    return (((uint64)_highVal)<<32ull) + (uint64)_lowVal;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline int64 ex_gen_int64 ( int32 _highVal, int32 _lowVal ) {
    return (((int64)_highVal)<<32ll) + (int64)_lowVal;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_split_uint64 ( uint64 _value, uint32 *_pHighVal, uint32 *_pLowVal ) {
    if ( _pLowVal )
    {
        (*_pLowVal) = (uint32)(_value & 0xffffffffull);
    }

    if ( _pHighVal )
    {
        (*_pHighVal) = (uint32)(_value>>32ull);
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_split_int64 ( int64 _value, int32 *_pHighVal, int32 *_pLowVal ) {
    if ( _pLowVal )
    {
        (*_pLowVal) = (int32)(_value & 0xffffffffull);
    }

    if ( _pHighVal )
    {
        (*_pHighVal) = (int32)(_value>>32ull);
    }
}

///////////////////////////////////////////////////////////////////////////////
// swap byte
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_swap_n_bytes ( int _n, void *_value ) {
    uint8 *p = (uint8 *)_value;
    uint32 i = 0;
    uint32 j = _n - 1;
    uint8  t;
    
    while(i < j)
    {
        t = p[i];

        p[i] = p[j];
        p[j] = t;

        i++;
        j--;
    }
}

// ------------------------------------------------------------------ 
// Desc: swap 1 byte. Does nothing (no swapping needed).
// ------------------------------------------------------------------ 

static inline void ex_swap_1_bytes ( void *_value ) {
    EX_UNUSED(_value);
}

// ------------------------------------------------------------------ 
// Desc: swap 2 bytes
// ------------------------------------------------------------------ 

static inline void ex_swap_2_bytes ( void *_value ) {
    uint16 *val = (uint16 *)_value;
    *val = (((*val) >> 8) & 0xff) | (((*val) & 0xff) << 8);
}

// ------------------------------------------------------------------ 
// Desc: swap 4 bytes
// ------------------------------------------------------------------ 

static inline void ex_swap_4_bytes ( void *_value ) {
#if ( EX_PLATFORM == EX_WIN32 ) && ( EX_COMPILER == EX_MSVC )
    __asm
    {
        mov     esi, _value
        mov		eax, [esi]
        bswap	eax
        mov     [esi], eax
    }
#else
    // TODO: other platform
#endif
}

// ------------------------------------------------------------------ 
// Desc: swap 8 bytes
// ------------------------------------------------------------------ 

static inline void ex_swap_8_bytes ( void *_value ) {
#if ( EX_PLATFORM == EX_WIN32 ) && ( EX_COMPILER == EX_MSVC )
    __asm
    {
        mov     esi, _value
        mov		eax, [esi]
        mov		ebx, [esi+4]
        bswap	eax
        bswap	ebx		
        mov     [esi], ebx
        mov     [esi+4], eax
    }
#else
    // TODO: other platform
#endif
}

// ######################### 
#ifdef __cplusplus
} // end extern "C"
#endif
// ######################### 

// #################################################################################
#endif // END BIT_H_1277693605
// #################################################################################
