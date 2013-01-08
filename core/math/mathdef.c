// ======================================================================================
// File         : mathdef.c
// Author       : Wu Jie 
// Last Change  : 01/25/2011 | 01:31:14 AM | Tuesday,January
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

const ex_vec2f_t ex_vec2f_zero = { 0.0f, 0.0f };
const ex_vec2f_t ex_vec2f_one = { 1.0f, 1.0f };

const ex_vec3f_t ex_vec3f_zero = { 0.0f, 0.0f, 0.0f };
const ex_vec3f_t ex_vec3f_one = { 1.0f, 1.0f, 1.0f };

const ex_vec4f_t ex_vec4f_zero = { 0.0f, 0.0f, 0.0f, 0.0f };
const ex_vec4f_t ex_vec4f_one = { 1.0f, 1.0f, 1.0f, 1.0f };

const ex_mat22f_t ex_mat22f_zero = {
    0.0f, 0.0f,
    0.0f, 0.0f
};
const ex_mat22f_t ex_mat22f_identity = {
    1.0f, 0.0f,
    0.0f, 1.0f
};

const ex_mat33f_t ex_mat33f_zero = {
    0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f
};
const ex_mat33f_t ex_mat33f_identity = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

const ex_mat44f_t ex_mat44f_zero = {
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f
};
const ex_mat44f_t ex_mat44f_identity = {
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
};

const ex_quatf_t ex_quatf_zero = { 0.0f, 0.0f, 0.0f, 0.0f };
const ex_quatf_t ex_quatf_identity = { 0.0f, 0.0f, 0.0f, 1.0f };

const ex_angf_t ex_angf_zero = { 0.0f };
