// ======================================================================================
// File         : mat33f.c
// Author       : Wu Jie 
// Last Change  : 11/12/2010 | 11:30:33 AM | Friday,November
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"
#include "mathop.h"
#include "vec3f.h"
#include "mat33f.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_mat33f_mul_vec3f ( ex_vec3f_t *_r, const ex_mat33f_t *_lhs, const ex_vec3f_t *_rhs ) {
    float x, y, z;
    ex_vec3f_t tmp;

    ex_mat33f_row( &tmp, _lhs, 0 );
    x = ex_vec3f_dot( _rhs, &tmp );
    ex_mat33f_row( &tmp, _lhs, 1 );
    y = ex_vec3f_dot( _rhs, &tmp );
    ex_mat33f_row( &tmp, _lhs, 2 );
    z = ex_vec3f_dot( _rhs, &tmp );

    ex_vec3f_set( _r, x, y, z );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_vec3f_mul_mat33f ( ex_vec3f_t *_r, const ex_vec3f_t *_lhs, const ex_mat33f_t *_rhs ) {
    float x, y, z;
    ex_vec3f_t tmp;

    ex_mat33f_col( &tmp, _rhs, 0 );
    x = ex_vec3f_dot( _lhs, &tmp );
    ex_mat33f_col( &tmp, _rhs, 1 );
    y = ex_vec3f_dot( _lhs, &tmp );
    ex_mat33f_col( &tmp, _rhs, 2 );
    z = ex_vec3f_dot( _lhs, &tmp );

    ex_vec3f_set( _r, x, y, z );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_mat33f_inverse ( ex_mat33f_t *_m ) {
    float det, inv;
    float m00, m01, m02, m10, m11, m12, m20, m21, m22; 

    m00 = _m->m11 * _m->m22 - _m->m12 * _m->m21;
    m01 = _m->m02 * _m->m21 - _m->m01 * _m->m22;
    m02 = _m->m01 * _m->m12 - _m->m02 * _m->m11;
    m10 = _m->m12 * _m->m20 - _m->m10 * _m->m22;
    m11 = _m->m00 * _m->m22 - _m->m02 * _m->m20;
    m12 = _m->m02 * _m->m10 - _m->m00 * _m->m12;
    m20 = _m->m10 * _m->m21 - _m->m11 * _m->m20;
    m21 = _m->m01 * _m->m20 - _m->m00 * _m->m21;
    m22 = _m->m00 * _m->m11 - _m->m01 * _m->m10;

    det = _m->m00 * m00 + _m->m01 * m10 + _m->m02 * m20;

    if ( ex_is_zerof(det, EX_FLOAT_EPS) )
        return false;

    inv = 1.0f / det;
    ex_mat33f_set ( _m, 
                 m00 * inv, m01 * inv, m02 * inv,
                 m10 * inv, m11 * inv, m12 * inv,
                 m20 * inv, m21 * inv, m22 * inv );
    return true;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_mat33f_get_inverse ( const ex_mat33f_t *_m, ex_mat33f_t *_r ) {
    float det, inv;

    _r->m00 = _m->m11 * _m->m22 - _m->m12 * _m->m21;
    _r->m01 = _m->m02 * _m->m21 - _m->m01 * _m->m22;
    _r->m02 = _m->m01 * _m->m12 - _m->m02 * _m->m11;
    _r->m10 = _m->m12 * _m->m20 - _m->m10 * _m->m22;
    _r->m11 = _m->m00 * _m->m22 - _m->m02 * _m->m20;
    _r->m12 = _m->m02 * _m->m10 - _m->m00 * _m->m12;
    _r->m20 = _m->m10 * _m->m21 - _m->m11 * _m->m20;
    _r->m21 = _m->m01 * _m->m20 - _m->m00 * _m->m21;
    _r->m22 = _m->m00 * _m->m11 - _m->m01 * _m->m10;

    det = _m->m00 * _r->m00 + _m->m01 * _r->m10 + _m->m02 * _r->m20;
    if ( ex_is_zerof(det, EX_FLOAT_EPS) )
        return false;

    inv = 1.0f/det;
    ex_mat33f_mul_scalar( _r, _r, inv );

    return true;
}
