// ======================================================================================
// File         : quatf.c
// Author       : Wu Jie 
// Last Change  : 11/12/2010 | 17:05:42 PM | Friday,November
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"
#include "mathop.h"
#include "mat33f.h"
#include "mat44f.h"
#include "quatf.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_quatf_inverse( ex_quatf_t *_r ) {
    float len_sqr;

    len_sqr = ex_quatf_lenSQR(_r);
    if ( len_sqr > 0.0f ) {
        float inv_len_sqr = 1.0f/len_sqr;
        ex_quatf_mul_scalar( _r, _r, inv_len_sqr );
        ex_quatf_conjugate(_r);
        return true;
    }

    return false;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

bool ex_quatf_get_inverse ( ex_quatf_t *_r, const ex_quatf_t *_q ) {
    float len_sqr;

    ex_assert ( _r != _q, "can't use self as return value." );

    len_sqr = ex_quatf_lenSQR(_q);
    if ( len_sqr > 0.0f ) {
        float inv_len_sqr = 1.0f/len_sqr;
        ex_quatf_mul_scalar( _r, _q, inv_len_sqr );
        ex_quatf_conjugate(_r);
        return true;
    }

    return false;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_quatf_to_mat33( const ex_quatf_t *_q, ex_mat33f_t *_m ) {
    float Tx, Ty, Tz; 
    float Twx, Twy, Twz; 
    float Txx, Txy, Txz;
    float Tyy, Tyz, Tzz;

    Tx  = 2.0f * _q->x;
    Ty  = 2.0f * _q->y;
    Tz  = 2.0f * _q->z;
    Twx = Tx * _q->w;
    Twy = Ty * _q->w;
    Twz = Tz * _q->w;
    Txx = Tx * _q->x;
    Txy = Ty * _q->x;
    Txz = Tz * _q->x;
    Tyy = Ty * _q->y;
    Tyz = Tz * _q->y;
    Tzz = Tz * _q->z;

    ex_mat33f_set ( _m,  
                    1.0f - ( Tyy + Tzz ), Txy + Twz,            Txz - Twy, 
                    Txy - Twz,            1.0f - ( Txx + Tzz ), Tyz + Twx,
                    Txz + Twy,            Tyz - Twx,            1.0f - ( Txx + Tyy ) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_quatf_to_mat44( const ex_quatf_t *_q, ex_mat44f_t *_m ) {
    float Tx, Ty, Tz; 
    float Twx, Twy, Twz; 
    float Txx, Txy, Txz;
    float Tyy, Tyz, Tzz;

    Tx  = 2.0f * _q->x;
    Ty  = 2.0f * _q->y;
    Tz  = 2.0f * _q->z;
    Twx = Tx * _q->w;
    Twy = Ty * _q->w;
    Twz = Tz * _q->w;
    Txx = Tx * _q->x;
    Txy = Ty * _q->x;
    Txz = Tz * _q->x;
    Tyy = Ty * _q->y;
    Tyz = Tz * _q->y;
    Tzz = Tz * _q->z;

    ex_mat44f_set ( _m,  
                    1.0f - ( Tyy + Tzz ), Txy + Twz,            Txz - Twy,            0.0f,
                    Txy - Twz,            1.0f - ( Txx + Tzz ), Tyz + Twx,            0.0f,
                    Txz + Twy,            Tyz - Twx,            1.0f - ( Txx + Tyy ), 0.0f,  
                    0.0f,                 0.0f,                 0.0f,                 1.0f );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_quatf_get_axis_x( ex_vec3f_t *_r, const ex_quatf_t *_q  ) {
    float Tx, Ty, Tz; 
    float Twx, Twy, Twz; 
    float Txx, Txy, Txz;
    float Tyy, Tyz, Tzz;

    //
    Tx  = 2.0f * _q->x;
    Ty  = 2.0f * _q->y;
    Tz  = 2.0f * _q->z;
    Twx = Tx * _q->w;
    Twy = Ty * _q->w;
    Twz = Tz * _q->w;
    Txx = Tx * _q->x;
    Txy = Ty * _q->x;
    Txz = Tz * _q->x;
    Tyy = Ty * _q->y;
    Tyz = Tz * _q->y;
    Tzz = Tz * _q->z;

    ex_vec3f_set ( _r, 1.0f - ( Tyy + Tzz ), Txy + Twz, Txz - Twy );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void ex_quatf_get_axis_y( ex_vec3f_t *_r, const ex_quatf_t *_q  ) {
    float Tx, Ty, Tz; 
    float Twx, Twy, Twz; 
    float Txx, Txy, Txz;
    float Tyy, Tyz, Tzz;

    //
    Tx  = 2.0f * _q->x;
    Ty  = 2.0f * _q->y;
    Tz  = 2.0f * _q->z;
    Twx = Tx * _q->w;
    Twy = Ty * _q->w;
    Twz = Tz * _q->w;
    Txx = Tx * _q->x;
    Txy = Ty * _q->x;
    Txz = Tz * _q->x;
    Tyy = Ty * _q->y;
    Tyz = Tz * _q->y;
    Tzz = Tz * _q->z;

    ex_vec3f_set ( _r, Txy - Twz, 1.0f - ( Txx + Tzz ), Tyz + Twx );
}

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

void ex_quatf_get_axis_z( ex_vec3f_t *_r, const ex_quatf_t *_q  ) {
    float Tx, Ty, Tz; 
    float Twx, Twy, Twz; 
    float Txx, Txy, Txz;
    float Tyy, Tyz, Tzz;

    //
    Tx  = 2.0f * _q->x;
    Ty  = 2.0f * _q->y;
    Tz  = 2.0f * _q->z;
    Twx = Tx * _q->w;
    Twy = Ty * _q->w;
    Twz = Tz * _q->w;
    Txx = Tx * _q->x;
    Txy = Ty * _q->x;
    Txz = Tz * _q->x;
    Tyy = Ty * _q->y;
    Tyz = Tz * _q->y;
    Tzz = Tz * _q->z;

    ex_vec3f_set ( _r, Txz + Twy, Tyz - Twx, 1.0f - ( Txx + Tyy ) );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void ex_quatf_to_axis_xyz( const ex_quatf_t *_q, ex_vec3f_t *_x, ex_vec3f_t *_y, ex_vec3f_t *_z ) {
    float Tx, Ty, Tz; 
    float Twx, Twy, Twz; 
    float Txx, Txy, Txz;
    float Tyy, Tyz, Tzz;

    //
    Tx  = 2.0f * _q->x;
    Ty  = 2.0f * _q->y;
    Tz  = 2.0f * _q->z;
    Twx = Tx * _q->w;
    Twy = Ty * _q->w;
    Twz = Tz * _q->w;
    Txx = Tx * _q->x;
    Txy = Ty * _q->x;
    Txz = Tz * _q->x;
    Tyy = Ty * _q->y;
    Tyz = Tz * _q->y;
    Tzz = Tz * _q->z;

    ex_vec3f_set ( _x, 1.0f - ( Tyy + Tzz ), Txy + Twz, Txz - Twy );
    ex_vec3f_set ( _y, Txy - Twz, 1.0f - ( Txx + Tzz ), Tyz + Twx );
    ex_vec3f_set ( _z, Txz + Twy, Tyz - Twx, 1.0f - ( Txx + Tyy ) );
}
