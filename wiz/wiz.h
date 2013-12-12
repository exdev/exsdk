// ======================================================================================
// File         : wiz.h
// Author       : Wu Jie 
// Last Change  : 12/12/2013 | 10:21:35 AM | Thursday,December
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef WIZ_H_1386814934
#define WIZ_H_1386814934
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" { 
#endif
// ######################### 

#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
// wiz
///////////////////////////////////////////////////////////////////////////////

void wiz_run ( struct lua_State *_l, int _argc, char **_argv );

///////////////////////////////////////////////////////////////////////////////
// window op
///////////////////////////////////////////////////////////////////////////////

void wiz_create_window ( struct lua_State *_l, int _refID, int _w, int _h );
void wiz_destroy_window ( struct lua_State *_l, int _refID );
void wiz_repaint_window ( int _refID );
void wiz_get_window_size ( int _refID, int *_w, int *_h );
void wiz_set_window_background ( int _refID, int _r, int _g, int _b );

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 


// #################################################################################
#endif // END WIZ_H_1386814934
// #################################################################################
   
