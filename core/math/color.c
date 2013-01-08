// ======================================================================================
// File         : color.c
// Author       : Wu Jie 
// Last Change  : 01/10/2011 | 10:53:24 AM | Monday,January
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exsdk.h"
#include "color.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: ex_color3u_t
// ------------------------------------------------------------------ 

const ex_color3u_t ex_color3u_red     = { 255,    0,      0   }; 
const ex_color3u_t ex_color3u_green   = { 0,      255,    0   }; 
const ex_color3u_t ex_color3u_blue    = { 0,      0,      255 }; 
const ex_color3u_t ex_color3u_black   = { 0,      0,      0   }; 
const ex_color3u_t ex_color3u_white   = { 255,    255,    255 }; 
const ex_color3u_t ex_color3u_yellow  = { 255,    255,    0   }; 
const ex_color3u_t ex_color3u_cyan    = { 0,      255,    255 }; 
const ex_color3u_t ex_color3u_magenta = { 255,    0,      255 }; 
const ex_color3u_t ex_color3u_gray    = { 128,    128,    128 }; 

// ------------------------------------------------------------------ 
// Desc: ex_color4u_t
// ------------------------------------------------------------------ 

const ex_color4u_t ex_color4u_red     = { 255,    0,      0,      255 }; 
const ex_color4u_t ex_color4u_green   = { 0,      255,    0,      255 }; 
const ex_color4u_t ex_color4u_blue    = { 0,      0,      255,    255 }; 
const ex_color4u_t ex_color4u_black   = { 0,      0,      0,      255 }; 
const ex_color4u_t ex_color4u_white   = { 255,    255,    255,    255 }; 
const ex_color4u_t ex_color4u_yellow  = { 255,    255,    0,      255 }; 
const ex_color4u_t ex_color4u_cyan    = { 0,      255,    255,    255 }; 
const ex_color4u_t ex_color4u_magenta = { 255,    0,      255,    255 }; 
const ex_color4u_t ex_color4u_gray    = { 128,    128,    128,    255 }; 

// ------------------------------------------------------------------ 
// Desc: ex_color3f_t
// ------------------------------------------------------------------ 

const ex_color3f_t ex_color3f_red     = { 1.0f,   0.0f,   0.0f }; 
const ex_color3f_t ex_color3f_green   = { 0.0f,   1.0f,   0.0f }; 
const ex_color3f_t ex_color3f_blue    = { 0.0f,   0.0f,   1.0f }; 
const ex_color3f_t ex_color3f_black   = { 0.0f,   0.0f,   0.0f }; 
const ex_color3f_t ex_color3f_white   = { 1.0f,   1.0f,   1.0f }; 
const ex_color3f_t ex_color3f_yellow  = { 1.0f,   1.0f,   0.0f }; 
const ex_color3f_t ex_color3f_cyan    = { 0.0f,   1.0f,   1.0f }; 
const ex_color3f_t ex_color3f_magenta = { 1.0f,   0.0f,   1.0f }; 
const ex_color3f_t ex_color3f_gray    = { 0.5f,   0.5f,   0.5f }; 

// ------------------------------------------------------------------ 
// Desc: ex_color4f_t
// ------------------------------------------------------------------ 

const ex_color4f_t ex_color4f_red     = { 1.0f,   0.0f,   0.0f,   1.0f }; 
const ex_color4f_t ex_color4f_green   = { 0.0f,   1.0f,   0.0f,   1.0f }; 
const ex_color4f_t ex_color4f_blue    = { 0.0f,   0.0f,   1.0f,   1.0f }; 
const ex_color4f_t ex_color4f_black   = { 0.0f,   0.0f,   0.0f,   1.0f }; 
const ex_color4f_t ex_color4f_white   = { 1.0f,   1.0f,   1.0f,   1.0f }; 
const ex_color4f_t ex_color4f_yellow  = { 1.0f,   1.0f,   0.0f,   1.0f }; 
const ex_color4f_t ex_color4f_cyan    = { 0.0f,   1.0f,   1.0f,   1.0f }; 
const ex_color4f_t ex_color4f_magenta = { 1.0f,   0.0f,   1.0f,   1.0f }; 
const ex_color4f_t ex_color4f_gray    = { 0.5f,   0.5f,   0.5f,   1.0f }; 

