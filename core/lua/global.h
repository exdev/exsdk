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

extern struct lua_State *ex_lua_init ();
extern void ex_lua_deinit ( struct lua_State * );
extern bool ex_lua_initialized ();

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

// module
// add module will load table from lua stack, and add it by the modname you provide 
extern void ex_lua_add_module ( struct lua_State *_l, const char *_modname );

// init modules will execute __init__.lua under the os path
extern int ex_lua_init_modules ( struct lua_State *_l, const char *_path );

// init modules will execute __init__.lua under the os path
extern int ex_lua_init_modules ( struct lua_State *_l, const char *_path );

///////////////////////////////////////////////////////////////////////////////
// lua interpreter op
///////////////////////////////////////////////////////////////////////////////

extern int ex_lua_pcall ( struct lua_State *_l, int _nargs, int _nresults, int _errfunc );
extern int ex_lua_dostring ( struct lua_State *_l, const char *_fmt, ... );
extern void ex_lua_run_interpretor ( struct lua_State *_l );

extern int ex_lua_dofile ( struct lua_State *_l, const char *_filepath );
extern int ex_lua_dofile_2 ( struct lua_State *_l, const char *_filepath, int _idx );

extern int ex_lua_fsys_dofile ( struct lua_State *_l, const char *_fsys_filepath );
extern int ex_lua_fsys_dofile_2 ( struct lua_State *_l, const char *_fsys_filepath, int _idx );

///////////////////////////////////////////////////////////////////////////////
// lua checks
///////////////////////////////////////////////////////////////////////////////

#define ex_lua_check_nargs(_l,_num) \
    if ( lua_gettop(_l) != _num ) return luaL_error ( _l, "Invalid number of arguments, should be %d", _num );
  
///////////////////////////////////////////////////////////////////////////////
// lua debug op
///////////////////////////////////////////////////////////////////////////////

extern int ex_lua_trace_back ( struct lua_State *_l );
extern void ex_lua_alert ( struct lua_State *_l );
extern int ex_lua_dump_stack ( struct lua_State *_l );
extern int ex_lua_totoal_memory ( struct lua_State *_l );

// ######################### 
#ifdef __cplusplus
} // end extern C 
#endif
// ######################### 

// #################################################################################
#endif // END GLOBAL_H_1358749859
// #################################################################################


