// ======================================================================================
// File         : ease_curve._c
// Author       : Wu Jie 
// Last Change  : 11/25/2010 | 16:36:22 PM | Thursday,November
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"
#include "mathdef.h"
#include "mathop.h"
#include "ease_curve.h"

///////////////////////////////////////////////////////////////////////////////
// ease quad
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: in
// ------------------------------------------------------------------ 

// float
float ex_ease_in_quadf ( float _t ) { return _t*_t; }

// double
double ex_ease_in_quad ( double _t ) { return _t*_t; } 

// ------------------------------------------------------------------ 
// Desc: out
// ------------------------------------------------------------------ 

// float
float ex_ease_out_quadf ( float _t ) { return -_t*(_t-2); }

// double
double ex_ease_out_quad ( double _t ) { return -_t*(_t-2); }

// ------------------------------------------------------------------ 
// Desc: inout
// ------------------------------------------------------------------ 

// float
float ex_ease_inout_quadf ( float _t ) {
    _t*=2.0f;
    if (_t < 1) {
        return _t*_t/2.0f;
    } else {
        --_t;
        return -0.5f * (_t*(_t-2) - 1);
    }
}

// double
double ex_ease_inout_quad ( double _t ) {
    _t*=2.0;
    if (_t < 1) {
        return _t*_t/2.0;
    } else {
        --_t;
        return -0.5 * (_t*(_t-2) - 1);
    }
}
 
// ------------------------------------------------------------------ 
// Desc: outin
// ------------------------------------------------------------------ 

// float
float ex_ease_outin_quadf ( float _t ) {
    if (_t < 0.5f) return ex_ease_out_quadf (_t*2)/2;
    return ex_ease_in_quadf((2*_t)-1)/2 + 0.5f;
}
 
// double
double ex_ease_outin_quad ( double _t ) {
    if (_t < 0.5) return ex_ease_out_quad (_t*2)/2;
    return ex_ease_in_quad((2*_t)-1)/2 + 0.5;
}
 
///////////////////////////////////////////////////////////////////////////////
// ease cubic
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: in 
// ------------------------------------------------------------------ 

// float
float ex_ease_in_cubicf ( float _t ) { return _t*_t*_t; }

// double
double ex_ease_in_cubic ( double _t ) { return _t*_t*_t; }

// ------------------------------------------------------------------ 
// Desc: out
// ------------------------------------------------------------------ 

// float
float ex_ease_out_cubicf ( float _t ) {
    _t-=1.0f;
    return _t*_t*_t + 1;
}

// double
double ex_ease_out_cubic ( double _t ) {
    _t-=1.0;
    return _t*_t*_t + 1;
}

// ------------------------------------------------------------------ 
// Desc: inout 
// ------------------------------------------------------------------ 

// float
float ex_ease_inout_cubicf ( float _t ) {
    _t*=2.0f;
    if(_t < 1) {
        return 0.5f*_t*_t*_t;
    } else {
        _t -= 2.0f;
        return 0.5f*(_t*_t*_t + 2);
    }
}
 
// double
double ex_ease_inout_cubic ( double _t ) {
    _t*=2.0;
    if(_t < 1) {
        return 0.5*_t*_t*_t;
    } else {
        _t -= 2.0;
        return 0.5*(_t*_t*_t + 2);
    }
}
 
// ------------------------------------------------------------------ 
// Desc: outin 
// ------------------------------------------------------------------ 

// float
float ex_ease_outin_cubicf ( float _t ) {
    if (_t < 0.5f) return ex_ease_out_cubicf (2*_t)/2;
    return ex_ease_in_cubicf(2*_t - 1)/2 + 0.5f;
}
 
// double
double ex_ease_outin_cubic ( double _t ) {
    if (_t < 0.5) return ex_ease_out_cubic (2*_t)/2;
    return ex_ease_in_cubic(2*_t - 1)/2 + 0.5;
}

///////////////////////////////////////////////////////////////////////////////
// ease quart
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_in_quartf ( float _t ) { return _t*_t*_t*_t; }

// double
double ex_ease_in_quart ( double _t ) { return _t*_t*_t*_t; }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_out_quartf ( float _t ) {
    _t-= 1.0f;
    return - (_t*_t*_t*_t- 1);
}

// double
double ex_ease_out_quart ( double _t ) {
    _t-= 1.0;
    return - (_t*_t*_t*_t- 1);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_inout_quartf ( float _t ) {
    _t*=2;
    if (_t < 1) return 0.5f*_t*_t*_t*_t;
    else {
        _t -= 2.0f;
        return -0.5f * (_t*_t*_t*_t- 2);
    }
}
 
// double
double ex_ease_inout_quart ( double _t ) {
    _t*=2;
    if (_t < 1) return 0.5*_t*_t*_t*_t;
    else {
        _t -= 2.0;
        return -0.5 * (_t*_t*_t*_t- 2);
    }
}
 
// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_outin_quartf ( float _t ) {
    if (_t < 0.5f) return ex_ease_out_quartf (2*_t)/2;
    return ex_ease_in_quartf(2*_t-1)/2 + 0.5f;
}
 
// double
double ex_ease_outin_quart ( double _t ) {
    if (_t < 0.5) return ex_ease_out_quart (2*_t)/2;
    return ex_ease_in_quart(2*_t-1)/2 + 0.5;
}
 
///////////////////////////////////////////////////////////////////////////////
// ease quint
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_in_quintf ( float _t ) { return _t*_t*_t*_t*_t; }

// double
double ex_ease_in_quint ( double _t ) { return _t*_t*_t*_t*_t; }

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_out_quintf ( float _t ) {
    _t-=1.0f;
    return _t*_t*_t*_t*_t + 1;
}

// double
double ex_ease_out_quint ( double _t ) {
    _t-=1.0;
    return _t*_t*_t*_t*_t + 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_inout_quintf ( float _t ) {
    _t*=2.0f;
    if (_t < 1) return 0.5f*_t*_t*_t*_t*_t;
    else {
        _t -= 2.0f;
        return 0.5f*(_t*_t*_t*_t*_t + 2);
    }
}

// double
double ex_ease_inout_quint ( double _t ) {
    _t*=2.0;
    if (_t < 1) return 0.5*_t*_t*_t*_t*_t;
    else {
        _t -= 2.0;
        return 0.5*(_t*_t*_t*_t*_t + 2);
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_outin_quintf ( float _t ) {
    if (_t < 0.5f) return ex_ease_out_quintf (2*_t)/2;
    return ex_ease_in_quintf(2*_t - 1)/2 + 0.5f;
}

// double
double ex_ease_outin_quint ( double _t ) {
    if (_t < 0.5) return ex_ease_out_quint (2*_t)/2;
    return ex_ease_in_quint(2*_t - 1)/2 + 0.5;
}

///////////////////////////////////////////////////////////////////////////////
// ease sine
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_in_sinef ( float _t ) {
    return (_t == 1.0f) ? 1.0f : -cosf(_t * (float)EX_HALF_PI) + 1.0f;
}

// double
double ex_ease_in_sine ( double _t ) {
    return (_t == 1.0) ? 1.0 : -cos(_t * EX_HALF_PI) + 1.0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_out_sinef ( float _t ) {
    return sinf(_t* (float)EX_HALF_PI);
}

// double
double ex_ease_out_sine ( double _t ) {
    return sin(_t* EX_HALF_PI);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_inout_sinef ( float _t ) {
    return -0.5f * (cosf(EX_PI*_t) - 1);
}

// double
double ex_ease_inout_sine ( double _t ) {
    return -0.5 * (cos(EX_PI*_t) - 1);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_outin_sinef ( float _t ) {
    if (_t < 0.5f) return ex_ease_out_sinef (2*_t)/2;
    return ex_ease_in_sinef(2*_t - 1)/2 + 0.5f;
}
 
// double
double ex_ease_outin_sine ( double _t ) {
    if (_t < 0.5) return ex_ease_out_sine (2*_t)/2;
    return ex_ease_in_sine(2*_t - 1)/2 + 0.5;
}

///////////////////////////////////////////////////////////////////////////////
// ease expo
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_in_expof ( float _t ) {
    return (_t==0 || _t == 1.0f) ? _t : powf(2.0f, 10 * (_t - 1)) - 0.001f;
}

// double
double ex_ease_in_expo ( double _t ) {
    return (_t==0 || _t == 1.0) ? _t : pow(2.0, 10 * (_t - 1)) - 0.001;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_out_expof ( float _t ) {
    return (_t==1.0f) ? 1.0f : 1.001f * (-powf(2.0f, -10 * _t) + 1);
}

// double
double ex_ease_out_expo ( double _t ) {
    return (_t==1.0) ? 1.0 : 1.001 * (-pow(2.0, -10 * _t) + 1);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_inout_expof ( float _t ) {
    if (_t==0.0f) return 0.0f;
    if (_t==1.0f) return 1.0f;
    _t*=2.0f;
    if (_t < 1) return 0.5f * powf(2.0f, 10 * (_t - 1)) - 0.0005f;
    return 0.5f * 1.0005f * (-powf(2.0f, -10 * (_t - 1)) + 2);
}

// double
double ex_ease_inout_expo ( double _t ) {
    if (_t==0.0) return 0.0;
    if (_t==1.0) return 1.0;
    _t*=2.0;
    if (_t < 1) return 0.5 * pow(2.0, 10 * (_t - 1)) - 0.0005;
    return 0.5 * 1.0005 * (-pow(2.0, -10 * (_t - 1)) + 2);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_outin_expof ( float _t ) {
    if (_t < 0.5f) return ex_ease_out_expof (2*_t)/2;
    return ex_ease_in_expof(2*_t - 1)/2 + 0.5f;
}

// double
double ex_ease_outin_expo ( double _t ) {
    if (_t < 0.5) return ex_ease_out_expo (2*_t)/2;
    return ex_ease_in_expo(2*_t - 1)/2 + 0.5;
}

///////////////////////////////////////////////////////////////////////////////
// ease circ
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_in_circf ( float _t ) {
    return -(sqrtf(1 - _t*_t) - 1);
}

// double
double ex_ease_in_circ ( double _t ) {
    return -(sqrt(1 - _t*_t) - 1);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_out_circf ( float _t ) {
    _t-= 1.0f;
    return sqrtf(1 - _t* _t);
}

// double
double ex_ease_out_circ ( double _t ) {
    _t-= 1.0;
    return sqrt(1 - _t* _t);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_inout_circf ( float _t ) {
    _t*=2.0f;
    if (_t < 1) {
        return -0.5f * (sqrtf(1 - _t*_t) - 1);
    } else {
        _t -= 2.0f;
        return 0.5f * (sqrtf(1 - _t*_t) + 1);
    }
}
 
// double
double ex_ease_inout_circ ( double _t ) {
    _t*=2.0;
    if (_t < 1) {
        return -0.5 * (sqrt(1 - _t*_t) - 1);
    } else {
        _t -= 2.0;
        return 0.5 * (sqrt(1 - _t*_t) + 1);
    }
}
 
// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_outin_circf ( float _t ) {
    if (_t < 0.5f) return ex_ease_out_circf (2*_t)/2;
    return ex_ease_in_circf(2*_t - 1)/2 + 0.5f;
}

// double
double ex_ease_outin_circ ( double _t ) {
    if (_t < 0.5) return ex_ease_out_circ (2*_t)/2;
    return ex_ease_in_circ(2*_t - 1)/2 + 0.5;
}

///////////////////////////////////////////////////////////////////////////////
// ease elastic
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// in helper float
static float __ease_in_elasticf_helper ( float _t, 
                                         float _b, 
                                         float _c, 
                                         float _d, 
                                         float _a, 
                                         float _p )
{
    float t_adj,_s;

    if (_t==0) return _b;
    t_adj = _t/_d;
    if (t_adj==1) return _b+_c;

    if ( _a < fabsf(_c) ) {
        _a = _c;
        _s = _p / 4.0f;
    } else {
        _s = _p / (float)EX_TWO_PI * asinf(_c/_a);
    }

    t_adj -= 1.0f;
    return -(_a*powf(2.0f,10*t_adj) * sinf( (t_adj*_d-_s)*(float)EX_TWO_PI/_p )) + _b;

}

// in helper double
static double __ease_in_elastic_helper ( double _t, 
                                         double _b, 
                                         double _c, 
                                         double _d, 
                                         double _a, 
                                         double _p )
{
    double t_adj,_s;

    if (_t==0) return _b;
    t_adj = _t/_d;
    if (t_adj==1) return _b+_c;

    if ( _a < fabsf(_c) ) {
        _a = _c;
        _s = _p / 4.0;
    } else {
        _s = _p / EX_TWO_PI * asin(_c/_a);
    }

    t_adj -= 1.0;
    return -(_a*pow(2.0,10*t_adj) * sin( (t_adj*_d-_s)*EX_TWO_PI/_p )) + _b;

}

// float
float ex_ease_in_elasticf ( float _t, float _a, float _p ) {
    return __ease_in_elasticf_helper(_t, 0, 1, 1, _a, _p);
}

// double
double ex_ease_in_elastic ( double _t, double _a, double _p ) {
    return __ease_in_elastic_helper(_t, 0, 1, 1, _a, _p);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// out helper float
static float __ease_out_elasticf_helper ( float _t, 
                                          float _b /*dummy*/, 
                                          float _c, 
                                          float _d /*dummy*/, 
                                          float _a, 
                                          float _p )
{
    float _s;

    if (_t==0) return 0;
    if (_t==1) return _c;

    if(_a < _c) {
        _a = _c;
        _s = _p / 4.0f;
    } else {
        _s = _p / (float)EX_TWO_PI * asinf(_c / _a);
    }

    return (_a*powf(2.0f,-10*_t) * sinf( (_t-_s)*(float)EX_TWO_PI/_p ) + _c);
}

// out helper double
static double __ease_out_elastic_helper ( double _t, 
                                          double _b /*dummy*/, 
                                          double _c, 
                                          double _d /*dummy*/, 
                                          double _a, 
                                          double _p )
{
    double _s;

    if (_t==0) return 0;
    if (_t==1) return _c;

    if(_a < _c) {
        _a = _c;
        _s = _p / 4.0;
    } else {
        _s = _p / EX_TWO_PI * asin(_c / _a);
    }

    return (_a*pow(2.0,-10*_t) * sin( (_t-_s)*EX_TWO_PI/_p ) + _c);
}

// float
float ex_ease_out_elasticf ( float _t, float _a, float _p ) {
    return __ease_out_elasticf_helper(_t, 0, 1, 1, _a, _p);
}

// double
double ex_ease_out_elastic ( double _t, double _a, double _p ) {
    return __ease_out_elastic_helper(_t, 0, 1, 1, _a, _p);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_inout_elasticf ( float _t, float _a, float _p ) {
    float _s;

    if (_t==0) return 0.0f;
    _t*=2.0f;
    if (_t==2) return 1.0f;

    if(_a < 1.0f) {
        _a = 1.0f;
        _s = _p / 4.0f;
    } else {
        _s = _p / (float)EX_TWO_PI * asinf(1.0f / _a);
    }

    if (_t < 1) return -.5f*(_a*powf(2.0f,10*(_t-1)) * sinf( (_t-1-_s)*(float)EX_TWO_PI/_p ));
    return _a*powf(2.0f,-10*(_t-1)) * sinf( (_t-1-_s)*(float)EX_TWO_PI/_p )*.5f + 1.0f;
}
 
// double
double ex_ease_inout_elastic ( double _t, double _a, double _p ) {
    double _s;

    if (_t==0) return 0.0;
    _t*=2.0;
    if (_t==2) return 1.0;

    if(_a < 1.0) {
        _a = 1.0;
        _s = _p / 4.0;
    } else {
        _s = _p / EX_TWO_PI * asin(1.0 / _a);
    }

    if (_t < 1) return -.5*(_a*pow(2.0,10*(_t-1)) * sin( (_t-1-_s)*EX_TWO_PI/_p ));
    return _a*pow(2.0,-10*(_t-1)) * sin( (_t-1-_s)*EX_TWO_PI/_p )*.5 + 1.0;
}
 
// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_outin_elasticf ( float _t, float _a, float _p ) {
    if (_t < 0.5f) return __ease_out_elasticf_helper(_t*2, 0, 0.5f, 1.0f, _a, _p);
    return __ease_in_elasticf_helper(2*_t - 1.0f, 0.5f, 0.5f, 1.0f, _a, _p);
}
 
// double
double ex_ease_outin_elastic ( double _t, double _a, double _p ) {
    if (_t < 0.5) return __ease_out_elastic_helper(_t*2, 0, 0.5, 1.0, _a, _p);
    return __ease_in_elastic_helper(2*_t - 1.0, 0.5, 0.5, 1.0, _a, _p);
}

///////////////////////////////////////////////////////////////////////////////
// ease back
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_in_backf ( float _t, float _s ) {
    return _t*_t*((_s+1)*_t - _s);
}

// double
double ex_ease_in_back ( double _t, double _s ) {
    return _t*_t*((_s+1)*_t - _s);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_out_backf ( float _t, float _s ) {
    _t-= 1.0f;
    return _t*_t*((_s+1)*_t+ _s) + 1;
}

// double
double ex_ease_out_back ( double _t, double _s ) {
    _t-= 1.0;
    return _t*_t*((_s+1)*_t+ _s) + 1;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_inout_backf ( float _t, float _s ) {
    _t *= 2.0f;
    if (_t < 1) {
        _s *= 1.525f;
        return 0.5f*(_t*_t*((_s+1)*_t - _s));
    } else {
        _t -= 2;
        _s *= 1.525f;
        return 0.5f*(_t*_t*((_s+1)*_t+ _s) + 2);
    }
}
 
// double
double ex_ease_inout_back ( double _t, double _s ) {
    _t *= 2.0;
    if (_t < 1) {
        _s *= 1.525;
        return 0.5*(_t*_t*((_s+1)*_t - _s));
    } else {
        _t -= 2;
        _s *= 1.525;
        return 0.5*(_t*_t*((_s+1)*_t+ _s) + 2);
    }
}
 
// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_outin_backf ( float _t, float _s ) {
    if (_t < 0.5f) return ex_ease_out_backf (2*_t, _s)/2;
    return ex_ease_in_backf(2*_t - 1, _s)/2 + 0.5f;
}
 
// double
double ex_ease_outin_back ( double _t, double _s ) {
    if (_t < 0.5) return ex_ease_out_back (2*_t, _s)/2;
    return ex_ease_in_back(2*_t - 1, _s)/2 + 0.5;
}

///////////////////////////////////////////////////////////////////////////////
// ease bounce
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
static float __ease_out_bouncef_helper ( float _t, 
                                         float _c, 
                                         float _a )
{
    if (_t == 1.0f) return _c;
    if (_t < (4/11.0f)) {
        return _c*(7.5625f*_t*_t);
    } else if (_t < (8/11.0f)) {
        _t -= (6/11.0f);
        return -_a * (1.f - (7.5625f*_t*_t + .75f)) + _c;
    } else if (_t < (10/11.0f)) {
        _t -= (9/11.0f);
        return -_a * (1.f - (7.5625f*_t*_t + .9375f)) + _c;
    } else {
        _t -= (21/22.0f);
        return -_a * (1.f - (7.5625f*_t*_t + .984375f)) + _c;
    }
}

// double
static double __ease_out_bounce_helper ( double _t, 
                                         double _c, 
                                         double _a )
{
    if (_t == 1.0) return _c;
    if (_t < (4/11.0)) {
        return _c*(7.5625*_t*_t);
    } else if (_t < (8/11.0)) {
        _t -= (6/11.0);
        return -_a * (1. - (7.5625*_t*_t + .75)) + _c;
    } else if (_t < (10/11.0)) {
        _t -= (9/11.0);
        return -_a * (1. - (7.5625*_t*_t + .9375)) + _c;
    } else {
        _t -= (21/22.0);
        return -_a * (1. - (7.5625*_t*_t + .984375)) + _c;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_in_bouncef ( float _t, float _a ) {
    return 1.0f - __ease_out_bouncef_helper(1.0f-_t, 1.0f, _a);
}

// double
double ex_ease_in_bounce ( double _t, double _a ) {
    return 1.0 - __ease_out_bounce_helper(1.0-_t, 1.0, _a);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_out_bouncef ( float _t, float _a ) {
    return __ease_out_bouncef_helper(_t, 1, _a);
}

// double
double ex_ease_out_bounce ( double _t, double _a ) {
    return __ease_out_bounce_helper(_t, 1, _a);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_inout_bouncef ( float _t, float _a ) {
    if (_t < 0.5f) return ex_ease_in_bouncef (2*_t, _a)/2;
    else return (_t == 1.0f) ? 1.0f : ex_ease_out_bouncef (2*_t - 1, _a)/2 + 0.5f;
}
 
// double
double ex_ease_inout_bounce ( double _t, double _a ) {
    if (_t < 0.5) return ex_ease_in_bounce (2*_t, _a)/2;
    else return (_t == 1.0) ? 1.0 : ex_ease_out_bounce (2*_t - 1, _a)/2 + 0.5;
}
 
// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_outin_bouncef ( float _t, float _a ) {
    if (_t < 0.5f) return __ease_out_bouncef_helper(_t*2, 0.5f, _a);
    return 1.0f - __ease_out_bouncef_helper (2.0f-2*_t, 0.5f, _a);
}
 
// double
double ex_ease_outin_bounce ( double _t, double _a ) {
    if (_t < 0.5) return __ease_out_bounce_helper(_t*2, 0.5, _a);
    return 1.0 - __ease_out_bounce_helper (2.0-2*_t, 0.5, _a);
}
 

///////////////////////////////////////////////////////////////////////////////
// ease smooth
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_smoothf ( float _t ) {
    if ( _t <= 0.0f ) return 0.0f;
    if ( _t >= 1.0f ) return 1.0f;
    return _t*_t*(3.0f - 2.0f*_t);
}

// double
double ex_ease_smooth ( double _t ) {
    if ( _t <= 0.0 ) return 0.0;
    if ( _t >= 1.0 ) return 1.0;
    return _t*_t*(3.0 - 2.0*_t);
}


///////////////////////////////////////////////////////////////////////////////
// ease fade
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_fadef ( float _t ) {
    if ( _t <= 0.0f ) return 0.0f;
    if ( _t >= 1.0f ) return 1.0f;
    return _t*_t*_t*(_t*(_t*6.0f-15.0f)+10.0f);
}

// double
double ex_ease_fade ( double _t ) {
    if ( _t <= 0.0 ) return 0.0;
    if ( _t >= 1.0 ) return 1.0;
    return _t*_t*_t*(_t*(_t*6.0-15.0)+10.0);
}


///////////////////////////////////////////////////////////////////////////////
// ease curve
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: __sin_progress
// ------------------------------------------------------------------ 

// float
static float __sin_progress_f ( float _v ) {
    return sinf((_v * EX_PI) - (float)EX_HALF_PI) / 2.0f + 0.5f;
}

// double
static double __sin_progress ( double _v ) {
    return sin((_v * EX_PI) - (float)EX_HALF_PI) / 2.0 + 0.5;
}

// ------------------------------------------------------------------ 
// Desc: __smooth_begin_end_mix_factor
// ------------------------------------------------------------------ 

// float
static float __smooth_begin_end_mix_factor_f ( float _v ) { 
    return EX_MIN( EX_MAX( 1.0f - _v * 2.0f + 0.3f, 0.0f ), 1.0f );
}

// double
static double __smooth_begin_end_mix_factor ( double _v ) { 
    return EX_MIN( EX_MAX( 1.0 - _v * 2.0 + 0.3, 0.0 ), 1.0 );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_in_curvef ( float _t ) {
    const float sinProgress = __sin_progress_f(_t);
    const float mix = __smooth_begin_end_mix_factor_f(_t);
    return sinProgress * mix + _t * (1 - mix);
}

// double
double ex_ease_in_curve ( double _t ) {
    const double sinProgress = __sin_progress(_t);
    const double mix = __smooth_begin_end_mix_factor(_t);
    return sinProgress * mix + _t * (1 - mix);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_out_curvef ( float _t ) {
    const float sinProgress = __sin_progress_f(_t);
    const float mix = __smooth_begin_end_mix_factor_f(1 - _t);
    return sinProgress * mix + _t * (1 - mix);
}

// double
double ex_ease_out_curve ( double _t ) {
    const double sinProgress = __sin_progress(_t);
    const double mix = __smooth_begin_end_mix_factor(1 - _t);
    return sinProgress * mix + _t * (1 - mix);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_curve_sinef ( float _t ) {
    return (sinf(((_t * (float)EX_TWO_PI)) - (float)EX_HALF_PI) + 1) / 2;
}
 
// double
double ex_ease_curve_sine ( double _t ) {
    return (sin(((_t * EX_TWO_PI)) - EX_HALF_PI) + 1) / 2;
}
 
// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// float
float ex_ease_curve_cosinef ( float _t ) {
    return (cosf(((_t * (float)EX_TWO_PI)) - (float)EX_HALF_PI) + 1) / 2;
}
 
// double
double ex_ease_curve_cosine ( double _t ) {
    return (cos(((_t * EX_TWO_PI)) - EX_HALF_PI) + 1) / 2;
}
