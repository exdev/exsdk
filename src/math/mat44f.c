// ======================================================================================
// File         : mat44f.c
// Author       : Wu Jie 
// Last Change  : 11/12/2010 | 14:02:38 PM | Friday,November
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"
#include "mathop.h"
#include "vec4f.h"
#include "mat44f.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_mat44f_mul_vec4f ( ex_vec4f_t *_r, const ex_mat44f_t *_lhs, const ex_vec4f_t *_rhs ) {
    float x, y, z, w;
    ex_vec4f_t tmp;

    ex_mat44f_row( &tmp, _lhs, 0 );
    x = ex_vec4f_dot( _rhs, &tmp );
    ex_mat44f_row( &tmp, _lhs, 1 );
    y = ex_vec4f_dot( _rhs, &tmp );
    ex_mat44f_row( &tmp, _lhs, 2 );
    z = ex_vec4f_dot( _rhs, &tmp );
    ex_mat44f_row( &tmp, _lhs, 3 );
    w = ex_vec4f_dot( _rhs, &tmp );

    ex_vec4f_set( _r, x, y, z, w );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_vec4f_mul_mat44f ( ex_vec4f_t *_r, const ex_vec4f_t *_lhs, const ex_mat44f_t *_rhs ) {
    float x, y, z, w;
    ex_vec4f_t tmp;

    ex_mat44f_col( &tmp, _rhs, 0 );
    x = ex_vec4f_dot( _lhs, &tmp );
    ex_mat44f_col( &tmp, _rhs, 1 );
    y = ex_vec4f_dot( _lhs, &tmp );
    ex_mat44f_col( &tmp, _rhs, 2 );
    z = ex_vec4f_dot( _lhs, &tmp );
    ex_mat44f_col( &tmp, _rhs, 2 );
    w = ex_vec4f_dot( _lhs, &tmp );

    ex_vec4f_set( _r, x, y, z, w );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_mat44f_inverse ( ex_mat44f_t *_m ) {
    float t0, t1, t2, t3;
    float t4, t5, t6, t7;
    float t8, t9, t10, t11;
    float det, inv;
    ex_mat44f_t src;

    src = *_m;

    // calculate pairs for first 8 elements (cofactors)
    t0  = src.m22 * src.m33;
    t1  = src.m23 * src.m32;
    t2  = src.m21 * src.m33;
    t3  = src.m23 * src.m31;
    t4  = src.m21 * src.m32;
    t5  = src.m22 * src.m31;
    t6  = src.m20 * src.m33;
    t7  = src.m23 * src.m30;
    t8  = src.m20 * src.m32;
    t9  = src.m22 * src.m30;
    t10 = src.m20 * src.m31;
    t11 = src.m21 * src.m30;

    // calculate first 8 elements (cofactors)
    _m->m00 = t0*src.m11 + t3*src.m12 + t4 *src.m13;
    _m->m00-= t1*src.m11 + t2*src.m12 + t5 *src.m13;
    _m->m10 = t1*src.m10 + t6*src.m12 + t9 *src.m13;
    _m->m10-= t0*src.m10 + t7*src.m12 + t8 *src.m13;
    _m->m20 = t2*src.m10 + t7*src.m11 + t10*src.m13;
    _m->m20-= t3*src.m10 + t6*src.m11 + t11*src.m13;
    _m->m30 = t5*src.m10 + t8*src.m11 + t11*src.m12;
    _m->m30-= t4*src.m10 + t9*src.m11 + t10*src.m12;
    _m->m01 = t1*src.m01 + t2*src.m02 + t5 *src.m03;
    _m->m01-= t0*src.m01 + t3*src.m02 + t4 *src.m03;
    _m->m11 = t0*src.m00 + t7*src.m02 + t8 *src.m03;
    _m->m11-= t1*src.m00 + t6*src.m02 + t9 *src.m03;
    _m->m21 = t3*src.m00 + t6*src.m01 + t11*src.m03;
    _m->m21-= t2*src.m00 + t7*src.m01 + t10*src.m03;
    _m->m31 = t4*src.m00 + t9*src.m01 + t10*src.m02;
    _m->m31-= t5*src.m00 + t8*src.m01 + t11*src.m02;

    // calculate pairs for second 8 elements (cofactors)
    t0  = src.m02*src.m13;
    t1  = src.m03*src.m12;
    t2  = src.m01*src.m13;
    t3  = src.m03*src.m11;
    t4  = src.m01*src.m12;
    t5  = src.m02*src.m11;
    t6  = src.m00*src.m13;
    t7  = src.m03*src.m10;
    t8  = src.m00*src.m12;
    t9  = src.m02*src.m10;
    t10 = src.m00*src.m11;
    t11 = src.m01*src.m10;

    // calculate second 8 elements (cofactors)
    _m->m02 = t0 *src.m31 + t3 *src.m32 + t4 *src.m33;
    _m->m02-= t1 *src.m31 + t2 *src.m32 + t5 *src.m33;
    _m->m12 = t1 *src.m30 + t6 *src.m32 + t9 *src.m33;
    _m->m12-= t0 *src.m30 + t7 *src.m32 + t8 *src.m33;
    _m->m22 = t2 *src.m30 + t7 *src.m31 + t10*src.m33;
    _m->m22-= t3 *src.m30 + t6 *src.m31 + t11*src.m33;
    _m->m32 = t5 *src.m30 + t8 *src.m31 + t11*src.m32;
    _m->m32-= t4 *src.m30 + t9 *src.m31 + t10*src.m32;
    _m->m03 = t2 *src.m22 + t5 *src.m23 + t1 *src.m21;
    _m->m03-= t4 *src.m23 + t0 *src.m21 + t3 *src.m22;
    _m->m13 = t8 *src.m23 + t0 *src.m20 + t7 *src.m22;
    _m->m13-= t6 *src.m22 + t9 *src.m23 + t1 *src.m20;
    _m->m23 = t6 *src.m21 + t11*src.m23 + t3 *src.m20;
    _m->m23-= t10*src.m23 + t2 *src.m20 + t7 *src.m21;
    _m->m33 = t10*src.m22 + t4 *src.m20 + t9 *src.m21;
    _m->m33-= t8 *src.m21 + t11*src.m22 + t5 *src.m20;

    // calculate determinant
    det= src.m00*_m->m00 + src.m01*_m->m10 + src.m02*_m->m20 + src.m03*_m->m30 ;

    if ( ex_is_zerof(det, EX_FLOAT_EPS) )
        return false;

    // devide the cofactor-matrix by the determinat
    inv = 1.0f/det;
    _m->m00*=inv; _m->m10*=inv; _m->m20*=inv; _m->m30*=inv;
    _m->m01*=inv; _m->m11*=inv; _m->m21*=inv; _m->m31*=inv;
    _m->m02*=inv; _m->m12*=inv; _m->m22*=inv; _m->m32*=inv;
    _m->m03*=inv; _m->m13*=inv; _m->m23*=inv; _m->m33*=inv;

    return true;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_mat44f_get_inverse ( const ex_mat44f_t *_m, ex_mat44f_t *_r ) {
    float t0, t1, t2, t3;
    float t4, t5, t6, t7;
    float t8, t9, t10, t11;
    float det, inv;

    // calculate pairs for first 8 elements (cofactors)
    t0  = _m->m22 * _m->m33;
    t1  = _m->m23 * _m->m32;
    t2  = _m->m21 * _m->m33;
    t3  = _m->m23 * _m->m31;
    t4  = _m->m21 * _m->m32;
    t5  = _m->m22 * _m->m31;
    t6  = _m->m20 * _m->m33;
    t7  = _m->m23 * _m->m30;
    t8  = _m->m20 * _m->m32;
    t9  = _m->m22 * _m->m30;
    t10 = _m->m20 * _m->m31;
    t11 = _m->m21 * _m->m30;

    // calculate first 8 elements (cofactors)
    _r->m00 = t0*_m->m11 + t3*_m->m12 + t4 *_m->m13;
    _r->m00-= t1*_m->m11 + t2*_m->m12 + t5 *_m->m13;
    _r->m10 = t1*_m->m10 + t6*_m->m12 + t9 *_m->m13;
    _r->m10-= t0*_m->m10 + t7*_m->m12 + t8 *_m->m13;
    _r->m20 = t2*_m->m10 + t7*_m->m11 + t10*_m->m13;
    _r->m20-= t3*_m->m10 + t6*_m->m11 + t11*_m->m13;
    _r->m30 = t5*_m->m10 + t8*_m->m11 + t11*_m->m12;
    _r->m30-= t4*_m->m10 + t9*_m->m11 + t10*_m->m12;
    _r->m01 = t1*_m->m01 + t2*_m->m02 + t5 *_m->m03;
    _r->m01-= t0*_m->m01 + t3*_m->m02 + t4 *_m->m03;
    _r->m11 = t0*_m->m00 + t7*_m->m02 + t8 *_m->m03;
    _r->m11-= t1*_m->m00 + t6*_m->m02 + t9 *_m->m03;
    _r->m21 = t3*_m->m00 + t6*_m->m01 + t11*_m->m03;
    _r->m21-= t2*_m->m00 + t7*_m->m01 + t10*_m->m03;
    _r->m31 = t4*_m->m00 + t9*_m->m01 + t10*_m->m02;
    _r->m31-= t5*_m->m00 + t8*_m->m01 + t11*_m->m02;

    // calculate pairs for second 8 elements (cofactors)
    t0  = _m->m02*_m->m13;
    t1  = _m->m03*_m->m12;
    t2  = _m->m01*_m->m13;
    t3  = _m->m03*_m->m11;
    t4  = _m->m01*_m->m12;
    t5  = _m->m02*_m->m11;
    t6  = _m->m00*_m->m13;
    t7  = _m->m03*_m->m10;
    t8  = _m->m00*_m->m12;
    t9  = _m->m02*_m->m10;
    t10 = _m->m00*_m->m11;
    t11 = _m->m01*_m->m10;

    // calculate second 8 elements (cofactors)
    _r->m02 = t0 *_m->m31 + t3 *_m->m32 + t4 *_m->m33;
    _r->m02-= t1 *_m->m31 + t2 *_m->m32 + t5 *_m->m33;
    _r->m12 = t1 *_m->m30 + t6 *_m->m32 + t9 *_m->m33;
    _r->m12-= t0 *_m->m30 + t7 *_m->m32 + t8 *_m->m33;
    _r->m22 = t2 *_m->m30 + t7 *_m->m31 + t10*_m->m33;
    _r->m22-= t3 *_m->m30 + t6 *_m->m31 + t11*_m->m33;
    _r->m32 = t5 *_m->m30 + t8 *_m->m31 + t11*_m->m32;
    _r->m32-= t4 *_m->m30 + t9 *_m->m31 + t10*_m->m32;
    _r->m03 = t2 *_m->m22 + t5 *_m->m23 + t1 *_m->m21;
    _r->m03-= t4 *_m->m23 + t0 *_m->m21 + t3 *_m->m22;
    _r->m13 = t8 *_m->m23 + t0 *_m->m20 + t7 *_m->m22;
    _r->m13-= t6 *_m->m22 + t9 *_m->m23 + t1 *_m->m20;
    _r->m23 = t6 *_m->m21 + t11*_m->m23 + t3 *_m->m20;
    _r->m23-= t10*_m->m23 + t2 *_m->m20 + t7 *_m->m21;
    _r->m33 = t10*_m->m22 + t4 *_m->m20 + t9 *_m->m21;
    _r->m33-= t8 *_m->m21 + t11*_m->m22 + t5 *_m->m20;

    // calculate determinant
    det = _m->m00*_r->m00 + _m->m01*_r->m10 + _m->m02*_r->m20 + _m->m03*_r->m30 ;

    if ( ex_is_zerof(det, EX_FLOAT_EPS) )
        return false;

    //devide the cofactor-matrix by the determinat
    inv = 1.0f/det;
    _r->m00*=inv; _r->m10*=inv; _r->m20*=inv; _r->m30*=inv;
    _r->m01*=inv; _r->m11*=inv; _r->m21*=inv; _r->m31*=inv;
    _r->m02*=inv; _r->m12*=inv; _r->m22*=inv; _r->m32*=inv;
    _r->m03*=inv; _r->m13*=inv; _r->m23*=inv; _r->m33*=inv;

    return true;
}
