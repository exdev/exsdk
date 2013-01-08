// ======================================================================================
// File         : color.h
// Author       : Wu Jie 
// Last Change  : 01/09/2011 | 10:49:34 AM | Sunday,January
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef COLOR_H_1294541375
#define COLOR_H_1294541375
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" { 
#endif
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// color structure declarations
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// color3u function defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color3u_set ( ex_vec3u_t *_c, uint8 _r, uint8 _g, uint8 _b ) {
    _c->r = EX_MIN (_r, 255);
    _c->g = EX_MIN (_g, 255);
    _c->b = EX_MIN (_b, 255);
} 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color3u_add ( ex_vec3u_t *_c, const ex_vec3u_t *_lhs, const ex_vec3u_t *_rhs ) { 
    _c->r = EX_MIN (_lhs->r+_rhs->r, 255);
    _c->g = EX_MIN (_lhs->g+_rhs->g, 255);
    _c->b = EX_MIN (_lhs->b+_rhs->b, 255);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color3u_sub ( ex_vec3u_t *_c, const ex_vec3u_t *_lhs, const ex_vec3u_t *_rhs ) { 
    _c->r = _lhs->r > _rhs->r ? _lhs->r - _rhs->r : 0; 
    _c->g = _lhs->g > _rhs->g ? _lhs->g - _rhs->g : 0; 
    _c->b = _lhs->b > _rhs->b ? _lhs->b - _rhs->b : 0; 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color3u_mul ( ex_vec3u_t *_c, const ex_vec3u_t *_lhs, const ex_vec3u_t *_rhs ) { 
    _c->r = EX_MIN (_lhs->r*_rhs->r, 255);
    _c->g = EX_MIN (_lhs->g*_rhs->g, 255);
    _c->b = EX_MIN (_lhs->b*_rhs->b, 255);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color3u_mul_scalar ( ex_vec3u_t *_c, const ex_vec3u_t *_lhs, float _scalar ) { 
    _c->r = EX_MIN ((uint8)((float)_lhs->r*_scalar), 255);
    _c->g = EX_MIN ((uint8)((float)_lhs->g*_scalar), 255);
    _c->b = EX_MIN ((uint8)((float)_lhs->b*_scalar), 255);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color3u_div ( ex_vec3u_t *_c, const ex_vec3u_t *_lhs, const ex_vec3u_t *_rhs ) { 
    _c->r = EX_MIN (_lhs->r/_rhs->r, 255);
    _c->g = EX_MIN (_lhs->g/_rhs->g, 255);
    _c->b = EX_MIN (_lhs->b/_rhs->b, 255);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color3u_div_scalar ( ex_vec3u_t *_c, const ex_vec3u_t *_lhs, float _scalar ) { 
    _c->r = EX_MIN ((uint8)((float)_lhs->r/_scalar), 255);
    _c->g = EX_MIN ((uint8)((float)_lhs->g/_scalar), 255);
    _c->b = EX_MIN ((uint8)((float)_lhs->b/_scalar), 255);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline bool ex_color3u_is_equal ( const ex_vec3u_t *_lhs, const ex_vec3u_t *_rhs ) { 
    return (_lhs->r == _rhs->r)
        && (_lhs->g == _rhs->g)
        && (_lhs->b == _rhs->b);
}

///////////////////////////////////////////////////////////////////////////////
// color4u function defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color4u_set ( ex_vec4u_t *_c, uint8 _r, uint8 _g, uint8 _b, uint8 _a ) {
    _c->r = EX_MIN (_r, 255);
    _c->g = EX_MIN (_g, 255);
    _c->b = EX_MIN (_b, 255);
    _c->a = EX_MIN (_a, 255);
} 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color4u_add ( ex_vec4u_t *_c, const ex_vec4u_t *_lhs, const ex_vec4u_t *_rhs ) { 
    _c->r = EX_MIN (_lhs->r+_rhs->r, 255);
    _c->g = EX_MIN (_lhs->g+_rhs->g, 255);
    _c->b = EX_MIN (_lhs->b+_rhs->b, 255);
    _c->a = EX_MIN (_lhs->a+_rhs->a, 255);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color4u_sub ( ex_vec4u_t *_c, const ex_vec4u_t *_lhs, const ex_vec4u_t *_rhs ) { 
    _c->r = _lhs->r > _rhs->r ? _lhs->r - _rhs->r : 0; 
    _c->g = _lhs->g > _rhs->g ? _lhs->g - _rhs->g : 0; 
    _c->b = _lhs->b > _rhs->b ? _lhs->b - _rhs->b : 0; 
    _c->a = _lhs->a > _rhs->a ? _lhs->a - _rhs->a : 0; 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color4u_mul ( ex_vec4u_t *_c, const ex_vec4u_t *_lhs, const ex_vec4u_t *_rhs ) { 
    _c->r = EX_MIN (_lhs->r*_rhs->r, 255);
    _c->g = EX_MIN (_lhs->g*_rhs->g, 255);
    _c->b = EX_MIN (_lhs->b*_rhs->b, 255);
    _c->a = EX_MIN (_lhs->a*_rhs->a, 255);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color4u_mul_scalar ( ex_vec4u_t *_c, const ex_vec4u_t *_lhs, float _scalar ) { 
    _c->r = EX_MIN ((uint8)((float)_lhs->r*_scalar), 255);
    _c->g = EX_MIN ((uint8)((float)_lhs->g*_scalar), 255);
    _c->b = EX_MIN ((uint8)((float)_lhs->b*_scalar), 255);
    _c->a = EX_MIN ((uint8)((float)_lhs->a*_scalar), 255);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color4u_div ( ex_vec4u_t *_c, const ex_vec4u_t *_lhs, const ex_vec4u_t *_rhs ) { 
    _c->r = EX_MIN (_lhs->r/_rhs->r, 255);
    _c->g = EX_MIN (_lhs->g/_rhs->g, 255);
    _c->b = EX_MIN (_lhs->b/_rhs->b, 255);
    _c->a = EX_MIN (_lhs->a/_rhs->a, 255);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color4u_div_scalar ( ex_vec4u_t *_c, const ex_vec4u_t *_lhs, float _scalar ) { 
    _c->r = EX_MIN ((uint8)((float)_lhs->r/_scalar), 255);
    _c->g = EX_MIN ((uint8)((float)_lhs->g/_scalar), 255);
    _c->b = EX_MIN ((uint8)((float)_lhs->b/_scalar), 255);
    _c->a = EX_MIN ((uint8)((float)_lhs->a/_scalar), 255);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline bool ex_color4u_is_equal ( const ex_vec4u_t *_lhs, const ex_vec4u_t *_rhs ) { 
    return (_lhs->r == _rhs->r)
        && (_lhs->g == _rhs->g)
        && (_lhs->b == _rhs->b)
        && (_lhs->a == _rhs->a);
}

///////////////////////////////////////////////////////////////////////////////
// color3f
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color3f_set ( ex_vec3f_t *_c, float _r, float _g, float _b ) {
    _c->r = ex_clampf ( _r, 0.0f, 1.0f );
    _c->g = ex_clampf ( _g, 0.0f, 1.0f );
    _c->b = ex_clampf ( _b, 0.0f, 1.0f );
} 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color3f_add ( ex_vec3f_t *_c, const ex_vec3f_t *_lhs, const ex_vec3f_t *_rhs ) { 
    _c->r = EX_MIN (_lhs->r+_rhs->r, 1.0f);
    _c->g = EX_MIN (_lhs->g+_rhs->g, 1.0f);
    _c->b = EX_MIN (_lhs->b+_rhs->b, 1.0f);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color3f_sub ( ex_vec3f_t *_c, const ex_vec3f_t *_lhs, const ex_vec3f_t *_rhs ) { 
    _c->r = _lhs->r > _rhs->r ? _lhs->r - _rhs->r : 0.0f; 
    _c->g = _lhs->g > _rhs->g ? _lhs->g - _rhs->g : 0.0f; 
    _c->b = _lhs->b > _rhs->b ? _lhs->b - _rhs->b : 0.0f; 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color3f_mul ( ex_vec3f_t *_c, const ex_vec3f_t *_lhs, const ex_vec3f_t *_rhs ) { 
    _c->r = EX_MIN (_lhs->r*_rhs->r, 1.0f);
    _c->g = EX_MIN (_lhs->g*_rhs->g, 1.0f);
    _c->b = EX_MIN (_lhs->b*_rhs->b, 1.0f);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color3f_mul_scalar ( ex_vec3f_t *_c, const ex_vec3f_t *_lhs, float _scalar ) { 
    _c->r = EX_MIN (_lhs->r*_scalar, 1.0f);
    _c->g = EX_MIN (_lhs->g*_scalar, 1.0f);
    _c->b = EX_MIN (_lhs->b*_scalar, 1.0f);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color3f_div ( ex_vec3f_t *_c, const ex_vec3f_t *_lhs, const ex_vec3f_t *_rhs ) { 
    _c->r = EX_MIN (_lhs->r/_rhs->r, 1.0f);
    _c->g = EX_MIN (_lhs->g/_rhs->g, 1.0f);
    _c->b = EX_MIN (_lhs->b/_rhs->b, 1.0f);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color3f_div_scalar ( ex_vec3f_t *_c, const ex_vec3f_t *_lhs, float _scalar ) { 
    _c->r = EX_MIN (_lhs->r/_scalar, 1.0f);
    _c->g = EX_MIN (_lhs->g/_scalar, 1.0f);
    _c->b = EX_MIN (_lhs->b/_scalar, 1.0f);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline bool ex_color3f_is_equal ( const ex_vec3f_t *_lhs, const ex_vec3f_t *_rhs ) { 
    return ex_is_equalf(_lhs->r,_rhs->r,EX_FLOAT_EPS)
        && ex_is_equalf(_lhs->g,_rhs->g,EX_FLOAT_EPS)
        && ex_is_equalf(_lhs->b,_rhs->b,EX_FLOAT_EPS);
}

///////////////////////////////////////////////////////////////////////////////
// color4f
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color4f_set ( ex_vec4f_t *_c, float _r, float _g, float _b, float _a ) {
    _c->r = ex_clampf ( _r, 0.0f, 1.0f );
    _c->g = ex_clampf ( _g, 0.0f, 1.0f );
    _c->b = ex_clampf ( _b, 0.0f, 1.0f );
    _c->a = ex_clampf ( _a, 0.0f, 1.0f );
} 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color4f_add ( ex_vec4f_t *_c, const ex_vec4f_t *_lhs, const ex_vec4f_t *_rhs ) { 
    _c->r = EX_MIN (_lhs->r+_rhs->r, 1.0f);
    _c->g = EX_MIN (_lhs->g+_rhs->g, 1.0f);
    _c->b = EX_MIN (_lhs->b+_rhs->b, 1.0f);
    _c->a = EX_MIN (_lhs->a+_rhs->a, 1.0f);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color4f_sub ( ex_vec4f_t *_c, const ex_vec4f_t *_lhs, const ex_vec4f_t *_rhs ) { 
    _c->r = _lhs->r > _rhs->r ? _lhs->r - _rhs->r : 0.0f; 
    _c->g = _lhs->g > _rhs->g ? _lhs->g - _rhs->g : 0.0f; 
    _c->b = _lhs->b > _rhs->b ? _lhs->b - _rhs->b : 0.0f; 
    _c->a = _lhs->a > _rhs->a ? _lhs->a - _rhs->a : 0.0f; 
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color4f_mul ( ex_vec4f_t *_c, const ex_vec4f_t *_lhs, const ex_vec4f_t *_rhs ) { 
    _c->r = EX_MIN (_lhs->r*_rhs->r, 1.0f);
    _c->g = EX_MIN (_lhs->g*_rhs->g, 1.0f);
    _c->b = EX_MIN (_lhs->b*_rhs->b, 1.0f);
    _c->a = EX_MIN (_lhs->a*_rhs->a, 1.0f);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color4f_mul_scalar ( ex_vec4f_t *_c, const ex_vec4f_t *_lhs, float _scalar ) { 
    _c->r = EX_MIN (_lhs->r*_scalar, 1.0f);
    _c->g = EX_MIN (_lhs->g*_scalar, 1.0f);
    _c->b = EX_MIN (_lhs->b*_scalar, 1.0f);
    _c->a = EX_MIN (_lhs->a*_scalar, 1.0f);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color4f_div ( ex_vec4f_t *_c, const ex_vec4f_t *_lhs, const ex_vec4f_t *_rhs ) { 
    _c->r = EX_MIN (_lhs->r/_rhs->r, 1.0f);
    _c->g = EX_MIN (_lhs->g/_rhs->g, 1.0f);
    _c->b = EX_MIN (_lhs->b/_rhs->b, 1.0f);
    _c->a = EX_MIN (_lhs->a/_rhs->a, 1.0f);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color4f_div_scalar ( ex_vec4f_t *_c, const ex_vec4f_t *_lhs, float _scalar ) { 
    _c->r = EX_MIN (_lhs->r/_scalar, 1.0f);
    _c->g = EX_MIN (_lhs->g/_scalar, 1.0f);
    _c->b = EX_MIN (_lhs->b/_scalar, 1.0f);
    _c->a = EX_MIN (_lhs->a/_scalar, 1.0f);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline bool ex_color4f_is_equal ( const ex_vec4f_t *_lhs, const ex_vec4f_t *_rhs ) { 
    return ex_is_equalf(_lhs->r,_rhs->r,EX_FLOAT_EPS)
        && ex_is_equalf(_lhs->g,_rhs->g,EX_FLOAT_EPS)
        && ex_is_equalf(_lhs->b,_rhs->b,EX_FLOAT_EPS)
        && ex_is_equalf(_lhs->a,_rhs->a,EX_FLOAT_EPS);
}

///////////////////////////////////////////////////////////////////////////////
// converts
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline uint32 ex_color3u_to_ARGB ( const ex_vec3u_t *_c ) { 
    return ((uint32)( ((0xff)<<24) | ((_c->r&0xff)<<16) | ((_c->g&0xff)<<8) | (_c->b&0xff)) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline uint32 ex_color3u_to_RGBA ( const ex_vec3u_t *_c ) { 
    return ((uint32)( ((_c->r&0xff)<<24) | ((_c->g&0xff)<<16) | ((_c->b&0xff)<<8) | (0xff)) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color3u_to_color3f ( const ex_vec3u_t *_c, ex_vec3f_t *_cout ) { 
    ex_color3f_set ( _cout, 
                     (float)_c->r / 255.0f, 
                     (float)_c->g / 255.0f,
                     (float)_c->b / 255.0f );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline uint32 ex_color4u_to_ARGB ( const ex_vec4u_t *_c ) { 
    return ((uint32)( ((_c->a&0xff)<<24) | ((_c->r&0xff)<<16) | ((_c->g&0xff)<<8) | (_c->b&0xff)) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline uint32 ex_color4u_to_RGBA ( const ex_vec4u_t *_c ) { 
    return ((uint32)( ((_c->r&0xff)<<24) | ((_c->g&0xff)<<16) | ((_c->b&0xff)<<8) | (_c->a&0xff)) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color4u_to_color4f ( const ex_vec4u_t *_c, ex_vec4f_t *_cout ) { 
    ex_color4f_set ( _cout, 
                     (float)_c->r / 255.0f, 
                     (float)_c->g / 255.0f,
                     (float)_c->b / 255.0f,
                     (float)_c->a / 255.0f );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color3f_to_color3u ( const ex_vec3f_t *_c, ex_vec3u_t *_cout ) { 
    ex_color3u_set ( _cout, 
                     (uint8)(_c->r * 255.0f), 
                     (uint8)(_c->g * 255.0f),
                     (uint8)(_c->b * 255.0f) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline uint32 ex_color3f_to_ARGB ( const ex_vec3f_t *_c ) { 
    ex_vec3u_t cout;
    ex_color3f_to_color3u(_c,&cout);
    return ex_color3u_to_ARGB(&cout);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline uint32 ex_color3f_to_RGBA ( const ex_vec3f_t *_c ) { 
    ex_vec3u_t cout;
    ex_color3f_to_color3u(_c,&cout);
    return ex_color3u_to_RGBA(&cout);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline void ex_color4f_to_color4u ( const ex_vec4f_t *_c, ex_vec4u_t *_cout ) { 
    ex_color4u_set ( _cout, 
                     (uint8)(_c->r * 255.0f), 
                     (uint8)(_c->g * 255.0f),
                     (uint8)(_c->b * 255.0f),
                     (uint8)(_c->a * 255.0f) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline uint32 ex_color4f_to_ARGB ( const ex_vec4f_t *_c ) { 
    ex_vec4u_t cout;
    ex_color4f_to_color4u(_c,&cout);
    return ex_color4u_to_ARGB(&cout);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static inline uint32 ex_color4f_to_RGBA ( const ex_vec4f_t *_c ) { 
    ex_vec4u_t cout;
    ex_color4f_to_color4u(_c,&cout);
    return ex_color4u_to_RGBA(&cout);
}

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 

// #################################################################################
#endif // END COLOR_H_1294541375
// #################################################################################


