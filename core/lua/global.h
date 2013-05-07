// ======================================================================================
// File         : global.h
// Author       : Wu Jie 
// Last Change  : 01/21/2013 | 14:30:58 PM | Monday,January
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef GLOBAL_H_1358749859
#define GLOBAL_H_1358749859
// #################################################################################

// ######################### 
#ifdef __cplusplus
extern "C" { 
#endif
// ######################### 

///////////////////////////////////////////////////////////////////////////////
// lua core
///////////////////////////////////////////////////////////////////////////////

extern int ex_lua_init ();
extern void ex_lua_deinit ();
extern bool ex_lua_initialized ();

extern struct lua_State *ex_lua_main_state ();

///////////////////////////////////////////////////////////////////////////////
// lua op
///////////////////////////////////////////////////////////////////////////////

// path
extern int ex_lua_clear_path ( struct lua_State *_l );
extern int ex_lua_set_path ( struct lua_State *_l, const char *_path );
extern int ex_lua_add_path ( struct lua_State *_l, const char *_path );

// cpath
extern int ex_lua_clear_cpath ( struct lua_State *_l );
extern int ex_lua_set_cpath ( struct lua_State *_l, const char *_path );
extern int ex_lua_add_cpath ( struct lua_State *_l, const char *_path );

///////////////////////////////////////////////////////////////////////////////
// lua interpreter op
///////////////////////////////////////////////////////////////////////////////

extern int ex_lua_dofile ( struct lua_State *_l, const char *_filepath );
extern int ex_lua_dostring ( struct lua_State *_l, const char *_fmt, ... );
extern void ex_lua_run_interpretor ( struct lua_State *_l );

///////////////////////////////////////////////////////////////////////////////
// lua checks
///////////////////////////////////////////////////////////////////////////////

#define ex_lua_check_nargs(_l,_num) \
    if ( lua_gettop(_l) != _num ) return luaL_error ( _l, "Invalid number of arguments, should be %d", _num );
  
///////////////////////////////////////////////////////////////////////////////
// lua debug op
///////////////////////////////////////////////////////////////////////////////

extern void ex_lua_alert ( struct lua_State *_l );
extern int ex_lua_dump_stack ( struct lua_State *_l );
extern int ex_lua_totoal_memory ( struct lua_State *_l );

#if 0
///////////////////////////////////////////////////////////////////////////////
// main.lua ( the main.lua interface )
///////////////////////////////////////////////////////////////////////////////

extern void ex_lua_parse_main ( struct lua_State *_l );
extern void ex_lua_main_init ( struct lua_State *_l );
extern void ex_lua_main_deinit ( struct lua_State *_l );
extern void ex_lua_main_update ( struct lua_State *_l );
extern void ex_lua_main_render ( struct lua_State *_l );
#endif

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 

// #################################################################################
#endif // END GLOBAL_H_1358749859
// #################################################################################


