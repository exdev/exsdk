// ======================================================================================
// File         : exsdk.h
// Author       : Wu Jie 
// Last Change  : 06/26/2010 | 21:00:31 PM | Saturday,June
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef EXSDK_H_1277557232
#define EXSDK_H_1277557232
// #################################################################################

// low-level system
#include "defs/defs_inc.h"
#include "memory/memory_inc.h"
#include "misc/misc_inc.h"

// data structure and algorithm
#include "container/container_inc.h"
#include "math/math_inc.h"

// fsys
#include "fsys/fsys_inc.h"

// lua
#include "lua/lua_inc.h"

// renderer
#include "render/render_inc.h"

///////////////////////////////////////////////////////////////////////////////
// functions
///////////////////////////////////////////////////////////////////////////////

extern const char *ex_sdk_ver ();
extern int ex_sdk_init ();
extern void ex_sdk_deinit ();
extern bool ex_sdk_initialized ();

extern int ex_sdk_open_project ( const char *_path );
extern void ex_sdk_close_project ();

// #################################################################################
#endif // END EXSDK_H_1277557232
// #################################################################################


