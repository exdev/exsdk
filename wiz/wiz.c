// ======================================================================================
// File         : wiz.c
// Author       : Wu Jie 
// Last Change  : 12/12/2013 | 10:15:23 AM | Thursday,December
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

#include "SDL.h"
#include "SDL_main.h"

#include "wiz.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

typedef struct __window_info_t {
    int refID; // NOTE: this is luaL_ref return value, must use luaL_unref to release it.
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

    bool dirty;
    ex_vec3u_t bg_color;
} __window_info_t;

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

static ex_array_t *__window_list = NULL;
static __window_info_t *primary_win_info = NULL;
static SDL_Event event;

///////////////////////////////////////////////////////////////////////////////
// internal
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_wiz_init_arguments ( lua_State *_l, int _argc, char **_argv ) {
    int i = 1;

    // get wiz table
    lua_getglobal( _l, "wiz" );

        // get wiz.arguments
        lua_getfield( _l, -1, "arguments" );
            // push arguments
            // NOTE: the 0 argument is the fullpath of the wiz
            while ( i < _argc ) {
                lua_pushnumber(_l, i);
                lua_pushstring(_l, _argv[i]);
                lua_settable(_l, -3);
                ++i;
            }
        lua_pop(_l, 1); // pop wiz.arguments

    lua_pop(_l, 1); // pop wiz table
    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_wiz_on_exit ( lua_State *_l ) {
    int idx = -1;

    // push traceback function
    lua_pushcfunction( _l, ex_lua_trace_back );
    idx = lua_gettop(_l);

    // get wiz table
    lua_getglobal( _l, "wiz" );

    // get wiz.onExit
    lua_getfield( _l, -1, "onExit" );

    if ( lua_isnil(_l,-1) == false && lua_isfunction(_l,-1) ) {
        ex_lua_pcall(_l, 0, 0, idx);
        lua_pop(_l,1);
    }
    else {
        lua_pop(_l,2);
    }

    lua_pop(_l,1); // pop traceback function

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void __repaint_window ( __window_info_t *_win_info ) {
    _win_info->dirty = true;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static __window_info_t *__get_window_info ( SDL_Window *_sdl_window ) {
    size_t i = 0;
    __window_info_t *win_info;

    while ( i < ex_array_count(__window_list) ) {
        win_info = *(__window_info_t **)ex_array_get(__window_list, i);
        if ( win_info->sdl_window == _sdl_window ) {
            return win_info;
        }
        ++i;
    }

    return NULL;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __process_event ( lua_State *_l, SDL_Event *_event ) {
    int idx = -1;
    SDL_Window *sdl_window;
    __window_info_t *win_info;
    SDL_Rect viewportRect;

    //
    switch ( _event->type ) {

    // ======================================================== 
    // Window Events
    // ======================================================== 

    case SDL_WINDOWEVENT:
        sdl_window = SDL_GetWindowFromID(_event->window.windowID);
        win_info = __get_window_info (sdl_window);
        if ( win_info ) {
            switch (_event->window.event) {
            case SDL_WINDOWEVENT_CLOSE:
                wiz_destroy_window ( _l, win_info->refID );

                // if this is primary window, quit the application
                if ( win_info == primary_win_info ) {
                    return 1;
                }
                break;

            case SDL_WINDOWEVENT_RESIZED:
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                viewportRect.x = 0;  
                viewportRect.y = 0;  
                viewportRect.w = _event->window.data1;  
                viewportRect.h = _event->window.data2;  
                SDL_RenderSetViewport(win_info->sdl_renderer, &viewportRect);

                // push traceback function
                lua_pushcfunction( _l, ex_lua_trace_back );
                idx = lua_gettop(_l);

                // call window.onResize(w,h)
                lua_rawgeti( _l, LUA_REGISTRYINDEX, win_info->refID );
                lua_getfield( _l, -1, "onResize" );
                if ( lua_isnil(_l,-1) == 0 && lua_isfunction(_l,-1) ) {
                    lua_pushvalue(_l,-2);
                    lua_pushinteger(_l,_event->window.data1);
                    lua_pushinteger(_l,_event->window.data2);
                    ex_lua_pcall( _l, 3, 0, idx ); 
                    lua_pop ( _l, 1 ); // pop win_info.refID
                }
                else {
                    lua_pop ( _l, 2 );
                }
                lua_pop ( _l, 1 ); // pop traceback function

                //
                __repaint_window (win_info);
                break;

            case SDL_WINDOWEVENT_FOCUS_GAINED:
                // push traceback function
                lua_pushcfunction( _l, ex_lua_trace_back );
                idx = lua_gettop(_l);

                // call window.onFocus(w,h)
                lua_rawgeti( _l, LUA_REGISTRYINDEX, win_info->refID );
                lua_getfield( _l, -1, "onFocus" );
                if ( lua_isnil(_l,-1) == 0 && lua_isfunction(_l,-1) ) {
                    lua_pushvalue(_l,-2);
                    ex_lua_pcall( _l, 1, 0, idx ); 
                    lua_pop ( _l, 1 ); // pop win_info.refID
                }
                else {
                    lua_pop ( _l, 2 );
                }
                lua_pop ( _l, 1 ); // pop traceback function

                __repaint_window (win_info);
                break;

            case SDL_WINDOWEVENT_FOCUS_LOST:
                // push traceback function
                lua_pushcfunction( _l, ex_lua_trace_back );
                idx = lua_gettop(_l);

                // call window.onUnfocus(w,h)
                lua_rawgeti( _l, LUA_REGISTRYINDEX, win_info->refID );
                lua_getfield( _l, -1, "onUnfocus" );
                if ( lua_isnil(_l,-1) == 0 && lua_isfunction(_l,-1) ) {
                    lua_pushvalue(_l,-2);
                    ex_lua_pcall( _l, 1, 0, idx ); 
                    lua_pop ( _l, 1 ); // pop win_info.refID
                }
                else {
                    lua_pop ( _l, 2 );
                }
                lua_pop ( _l, 1 ); // pop traceback function

                __repaint_window (win_info);
                break;
            }
        }
        break;

    // ======================================================== 
    // Mouse Events
    // ======================================================== 

    case SDL_MOUSEMOTION:
        // SDL_MouseMotionEvent mouseMotionEvent = _event->motion;
        break;

    // ======================================================== 
    // Quit
    // ======================================================== 

    case SDL_QUIT:
        return 1;

    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////
// 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
extern int __wiz_lua_add_app ( lua_State * );
extern int __wiz_lua_add_window ( lua_State * );
// ------------------------------------------------------------------ 

static int __init ( lua_State *_l, int _argc, char **_argv ) {
    char path[MAX_PATH];
    const char *app_path = NULL;
    const char *usr_path = NULL;

    // mount the wiz path to __wiz__/ in fsys
#if (EX_PLATFORM == EX_IOS)
    app_path = ex_fsys_main_bundle_path();
#else
    app_path = ex_fsys_app_dir();
#endif
    usr_path = ex_fsys_user_dir();

    ex_log ( "[wiz] User Dir: %s", usr_path );
    ex_log ( "[wiz] Application Dir: %s", app_path );

    // mount wiz(.exe) process path to __wiz__/ primary
    if ( app_path ) {
        strncpy ( path, app_path, MAX_PATH );
        // strcat ( path, "builtin/" );

        // NOTE: set write dir doesn't means you mount it.
        if ( ex_fsys_set_write_dir(path) != 0 )
            return -1;
        ex_log ( "[wiz] Set default write dir: %s", path  );

        //
        if ( ex_fsys_mount( path, "__wiz__", true ) != 0 )
            return -1;
        ex_log ( "[wiz] Mount dir: %s to __wiz__/", path  );
    }

    // if ~/.wiz/ exists we mount it to __wiz__/ secondly
    if ( usr_path ) {
        strncpy ( path, usr_path, MAX_PATH );
        strcat ( path, ".wiz/" );

        //
        if ( ex_os_exists(path) && ex_os_isdir(path) ) {
            if ( ex_fsys_mount( path, "__wiz__", true ) != 0 )
                return -1;
            ex_log ("[wiz] Mount dir: %s to __wiz__/", path );
        }
    }

    // load builtin modules
    ex_log ( "[wiz] Loading builtin modules..." );
    if ( ex_lua_fsys_init_modules ( _l, "__wiz__/builtin/modules" ) ) {
        ex_log ( "Failed to load builtin modules" );
        return -1;
    }

    // create wiz_c table
    lua_newtable(_l);

        __wiz_lua_add_app (_l);
        __wiz_lua_add_window (_l);

        ex_lua_add_module ( _l, "wiz_c" );

    lua_pop(_l, 1);  /* remove wiz_c table */

    // push arguments to wiz.arguments in lua
    __lua_wiz_init_arguments ( _l, _argc, _argv );

    //
    __window_list = ex_array_alloc ( sizeof(__window_info_t *), 8 );

    return 0;
} 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void __deinit ( lua_State *_l ) {
    __window_info_t *win_info;

    // destroy all windows 
    while ( ex_array_count(__window_list) > 0 ) {
        win_info = *(__window_info_t **)ex_array_get(__window_list, 0);
        wiz_destroy_window ( _l, win_info->refID );
    }
    ex_array_free ( __window_list );

    // call wiz.onExit()
    __lua_wiz_on_exit (_l);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void __event_loop ( lua_State *_l ) {
    int idx = -1;

    // NOTE: there is two ways for update, using Timer or using Event-Poll, 
    // the timer is suitable for GUI tool, and Event-Poll is better for game

    // start main-loop
    while (1) {
        // handle events
        while ( SDL_PollEvent(&event) ) {
            if ( __process_event( _l, &event ) )
                return;
        }

        // push traceback function
        lua_pushcfunction( _l, ex_lua_trace_back );
        idx = lua_gettop(_l);

        // update windows [onUpdate]
        ex_array_each ( __window_list, __window_info_t *, win_info )
            lua_rawgeti( _l, LUA_REGISTRYINDEX, win_info->refID );
            lua_getfield( _l, -1, "onUpdate" );
            if ( lua_isnil(_l,-1) == 0 && lua_isfunction(_l,-1) ) {
                lua_pushvalue(_l,-2);
                ex_lua_pcall( _l, 1, 0, idx ); 
                lua_pop ( _l, 1 );
            }
            else {
                lua_pop ( _l, 2 );
            }
        ex_array_each_end

        // draw one frame [onRepaint]
        ex_array_each ( __window_list, __window_info_t *, win_info )
            if ( win_info->dirty ) {
                // clear background
                SDL_SetRenderDrawColor( win_info->sdl_renderer, 
                                        win_info->bg_color.r, 
                                        win_info->bg_color.g, 
                                        win_info->bg_color.b, 
                                        0xFF );
                SDL_RenderClear(win_info->sdl_renderer);

                // onRepaint
                lua_rawgeti( _l, LUA_REGISTRYINDEX, win_info->refID );
                lua_getfield( _l, -1, "onRepaint" );
                if ( lua_isnil(_l,-1) == 0 && lua_isfunction(_l,-1) ) {
                    lua_pushvalue(_l,-2);
                    ex_lua_pcall( _l, 1, 0, idx ); 
                    lua_pop ( _l, 1 );
                }
                else {
                    lua_pop ( _l, 2 );
                }

                // flush painter
                ex_painter_flush();

                // flush
                SDL_RenderPresent(win_info->sdl_renderer);
                win_info->dirty = false;
            }
        ex_array_each_end

        lua_pop ( _l, 1 ); // pop traceback function

        SDL_Delay(10);
    }
}

///////////////////////////////////////////////////////////////////////////////
// public interface
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void wiz_run ( lua_State *_l, int _argc, char **_argv ) {
    // init wiz
    if ( __init ( _l, _argc, _argv ) != 0 ) {
        ex_log ( "Failed to init wiz" );
        return;
    }

    // process argument
    if ( _argc >= 2 ) {
        size_t len;
        const char *p;
        const char *filepath;
        char result[512];

        filepath = _argv[1];

        // strip white space at last
        len = strlen(filepath);
        p = filepath + len - 1;
        while ( isspace(*p) ) {
            --p;
        }

        // copy the result
        len = p-filepath+1;
        if ( len > 511 ) len = 511;
        strncpy ( result, filepath, len );
        result[len] = '\0';

        // open the file
        if ( wiz_execute(_l,result) != 0 ) {
            return;
        }
    }

    // enter the event-loop if we create display(window) 
    if ( primary_win_info != NULL ) {
        __event_loop (_l);
    }

    // deinit wiz 
    __deinit(_l);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int wiz_execute ( lua_State *_l, const char *_path ) {
    size_t len;
    const char *end, *ptr;
    char dirpath[512];
    int idx_cwd;

    // initialize
    len = strlen(_path);
    end = _path + len - 1;
    ptr = end;

    // get dirpath
    while ( ptr != _path && *ptr != '/' ) {
        --ptr;
    }
    len = ptr-_path+1;
    if ( len > 511 ) len = 511;
    if ( len == 1 ) {
        strncpy ( dirpath, "./", 2 );
        dirpath[2] = '\0';
    }
    else {
        strncpy ( dirpath, _path, len );
        dirpath[len] = '\0';
    }

    // set os.cwd to the dirpath 
    lua_pushstring ( _l, ex_os_getcwd() ); idx_cwd = lua_gettop(_l); // store the old cwd
    ex_os_setcwd(dirpath);

    // if this is a lua file
    if ( strncmp( (end-3), ".lua", 4 ) == 0 ) {
        // NOTE: do not use ex_lua_fsys_dofile, because we are working with command line environment
        if ( ex_lua_dofile ( _l, _path ) != 0 ) {
            return -1;
        }
    }
    // if this is an xml file
    else if ( strncmp( (end-3), ".xml", 4 ) == 0 ) {
        // TODO:
    }
    else {
        ex_log ( "Invalid file: %s", _path );
    }

    // restore the old cwd
    ex_os_setcwd(lua_tostring(_l, idx_cwd));
    lua_remove(_l,idx_cwd); // remove cwd
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void wiz_create_window ( lua_State *_l, int _refID, int _w, int _h ) {
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;
    __window_info_t *win_info;

    // create SDL window
    sdl_window = SDL_CreateWindow( "Window", 
                                   SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                   _w, _h, 
                                   SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN /*| SDL_WINDOW_BORDERLESS*/ 
                                 );
    if ( !sdl_window ) {
        ex_log ( "[SDL] Error: Could not create window: %s", SDL_GetError() );
        return;
    }

    // create SDL renderer
    sdl_renderer = SDL_CreateRenderer( sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if ( !sdl_renderer ) {
        ex_log ( "[SDL] Error: Could not create renderer: %s", SDL_GetError() );
        return;
    }

    // add window info
    win_info = ex_malloc( sizeof(__window_info_t) );
    win_info->sdl_window = sdl_window;
    win_info->sdl_renderer = sdl_renderer;
    win_info->refID = _refID;
    win_info->dirty = true;
    ex_color3u_set ( &win_info->bg_color, 128, 128, 128 );

    // if this is the first window, create queue
    if ( ex_array_count(__window_list) == 0 ) {
        primary_win_info = win_info;
        ex_set_main_sdl_renderer(sdl_renderer);
    }
    ex_array_add ( __window_list, &win_info );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void wiz_destroy_window ( lua_State *_l, int _refID ) {
    int idx = -1;
    size_t i = 0;
    __window_info_t *win_info;

    // get window
    while ( i < ex_array_count(__window_list) ) {
        win_info = *(__window_info_t **)ex_array_get(__window_list, i);
        if ( win_info->refID == _refID ) {
            break;
        }
        ++i;
    }

    // call win_info.refID.onDestroy
    lua_pushcfunction( _l, ex_lua_trace_back ); // push traceback function
    idx = lua_gettop(_l);
    lua_rawgeti( _l, LUA_REGISTRYINDEX, win_info->refID );
    lua_getfield( _l, -1, "onDestroy" );
    if ( lua_isnil(_l,-1) == 0 && lua_isfunction(_l,-1) ) {
        lua_pushvalue(_l,-2);
        ex_lua_pcall( _l, 1, 0, idx ); 
        lua_pop ( _l, 1 ); // pop win_info.refID
    }
    else {
        lua_pop ( _l, 2 ); // pop win_info.refID
    }
    lua_pop ( _l, 1 ); // pop traceback function

    //
    ex_array_remove_at_fast ( __window_list, i );
    luaL_unref( _l, LUA_REGISTRYINDEX, win_info->refID );
    SDL_DestroyRenderer( win_info->sdl_renderer );
    SDL_DestroyWindow( win_info->sdl_window );
    ex_free(win_info);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void wiz_repaint_window ( int _refID ) {
    size_t i = 0;
    __window_info_t *win_info;

    while ( i < ex_array_count(__window_list) ) {
        win_info = *(__window_info_t **)ex_array_get(__window_list, i);
        if ( win_info->refID == _refID ) {
            __repaint_window(win_info);
            break;
        }
        ++i;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void wiz_get_window_size ( int _refID, int *_w, int *_h ) {
    size_t i = 0;
    __window_info_t *win_info;

    while ( i < ex_array_count(__window_list) ) {
        win_info = *(__window_info_t **)ex_array_get(__window_list, i);
        if ( win_info->refID == _refID ) {
            SDL_GetWindowSize( win_info->sdl_window, _w, _h );
            break;
        }
        ++i;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void wiz_set_window_background ( int _refID, int _r, int _g, int _b ) {
    size_t i = 0;
    __window_info_t *win_info;

    while ( i < ex_array_count(__window_list) ) {
        win_info = *(__window_info_t **)ex_array_get(__window_list, i);
        if ( win_info->refID == _refID ) {
            ex_color3u_set ( &win_info->bg_color, _r, _g, _b );
            win_info->dirty = true;
            break;
        }
        ++i;
    }
}

