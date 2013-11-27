// ======================================================================================
// File         : main.c
// Author       : Wu Jie 
// Last Change  : 05/07/2013 | 14:48:30 PM | Tuesday,May
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

#include "SDL.h"
#include "SDL_main.h"

#include "exsdk.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

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
// public
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void create_window ( int _refID, int _w, int _h ) {
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

void destroy_window ( lua_State *_l, int _refID ) {
    int idx = -1;
    size_t i = 0;
    __window_info_t *win_info;

    // error func
    lua_pushcfunction( _l, ex_lua_trace_back );
    idx = lua_gettop(_l);

    // get window
    while ( i < ex_array_count(__window_list) ) {
        win_info = *(__window_info_t **)ex_array_get(__window_list, i);
        if ( win_info->refID == _refID ) {
            break;
        }
        ++i;
    }

    // call win_info.refID.on_destroy { 
    lua_rawgeti( _l, LUA_REGISTRYINDEX, win_info->refID );
    lua_getfield( _l, -1, "on_destroy" );
    if ( lua_isnil(_l,-1) == 0 && lua_isfunction(_l,-1) ) {
        lua_pushvalue(_l,-2);
        ex_lua_pcall( _l, 1, 0, idx ); 
        lua_pop ( _l, 1 ); // pop win_info.refID
    }
    else {
        lua_pop ( _l, 2 ); // pop win_info.refID
    }
    lua_pop ( _l, 1 ); // pop error func

    //
    ex_array_remove_at_fast ( __window_list, i );
    luaL_unref( _l, LUA_REGISTRYINDEX, win_info->refID );
    SDL_DestroyRenderer( win_info->sdl_renderer );
    SDL_DestroyWindow( win_info->sdl_window );
    ex_free(win_info);
}

// ------------------------------------------------------------------ 
// Desc: 
static void __repaint_window ( __window_info_t * );
// ------------------------------------------------------------------ 

void repaint_window ( int _refID ) {
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

void get_window_size ( int _refID, int *_w, int *_h ) {
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

void set_window_background ( int _refID, int _r, int _g, int _b ) {
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

///////////////////////////////////////////////////////////////////////////////
// internal
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int __lua_wiz_init ( lua_State *_l, int _argc, char **_argv ) {
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

    // error func
    lua_pushcfunction( _l, ex_lua_trace_back );
    idx = lua_gettop(_l);

    // get wiz table
    lua_getglobal( _l, "wiz" );

    // get wiz.on_exit
    lua_getfield( _l, -1, "on_exit" );

    if ( lua_isnil(_l,-1) == false && lua_isfunction(_l,-1) ) {
        ex_lua_pcall(_l, 0, 0, idx);
        lua_pop(_l,1);
    }
    else {
        lua_pop(_l,2);
    }

    lua_pop(_l,1); // pop error func

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
    // windows event
    // ======================================================== 

    case SDL_WINDOWEVENT:
        sdl_window = SDL_GetWindowFromID(_event->window.windowID);
        win_info = __get_window_info (sdl_window);
        if ( win_info ) {
            switch (_event->window.event) {
            case SDL_WINDOWEVENT_CLOSE:
                destroy_window ( _l, win_info->refID );

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

                // error func
                lua_pushcfunction( _l, ex_lua_trace_back );
                idx = lua_gettop(_l);

                // call window.on_resize(w,h)
                lua_rawgeti( _l, LUA_REGISTRYINDEX, win_info->refID );
                lua_getfield( _l, -1, "on_resize" );
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
                lua_pop ( _l, 1 ); // pop error func

                //
                __repaint_window (win_info);
                break;

            case SDL_WINDOWEVENT_FOCUS_GAINED:
                // error func
                lua_pushcfunction( _l, ex_lua_trace_back );
                idx = lua_gettop(_l);

                // call window.on_resize(w,h)
                lua_rawgeti( _l, LUA_REGISTRYINDEX, win_info->refID );
                lua_getfield( _l, -1, "on_focus" );
                if ( lua_isnil(_l,-1) == 0 && lua_isfunction(_l,-1) ) {
                    lua_pushvalue(_l,-2);
                    ex_lua_pcall( _l, 1, 0, idx ); 
                    lua_pop ( _l, 1 ); // pop win_info.refID
                }
                else {
                    lua_pop ( _l, 2 );
                }
                lua_pop ( _l, 1 ); // pop error func

                __repaint_window (win_info);
                break;

            case SDL_WINDOWEVENT_FOCUS_LOST:
                // error func
                lua_pushcfunction( _l, ex_lua_trace_back );
                idx = lua_gettop(_l);

                // call window.on_resize(w,h)
                lua_rawgeti( _l, LUA_REGISTRYINDEX, win_info->refID );
                lua_getfield( _l, -1, "on_unfocus" );
                if ( lua_isnil(_l,-1) == 0 && lua_isfunction(_l,-1) ) {
                    lua_pushvalue(_l,-2);
                    ex_lua_pcall( _l, 1, 0, idx ); 
                    lua_pop ( _l, 1 ); // pop win_info.refID
                }
                else {
                    lua_pop ( _l, 2 );
                }
                lua_pop ( _l, 1 ); // pop error func

                __repaint_window (win_info);
                break;
            }
        }
        break;

    // ======================================================== 
    // quit event
    // ======================================================== 

    case SDL_QUIT:
        return 1;

    }

    return 0;
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

        // push error func
        lua_pushcfunction( _l, ex_lua_trace_back );
        idx = lua_gettop(_l);

        // update windows [on_update]
        ex_array_each ( __window_list, __window_info_t *, win_info )
            lua_rawgeti( _l, LUA_REGISTRYINDEX, win_info->refID );
            lua_getfield( _l, -1, "on_update" );
            if ( lua_isnil(_l,-1) == 0 && lua_isfunction(_l,-1) ) {
                lua_pushvalue(_l,-2);
                ex_lua_pcall( _l, 1, 0, idx ); 
                lua_pop ( _l, 1 );
            }
            else {
                lua_pop ( _l, 2 );
            }
        ex_array_each_end

        // draw one frame [on_repaint]
        ex_array_each ( __window_list, __window_info_t *, win_info )
            if ( win_info->dirty ) {
                // clear background
                SDL_SetRenderDrawColor( win_info->sdl_renderer, 
                                        win_info->bg_color.r, 
                                        win_info->bg_color.g, 
                                        win_info->bg_color.b, 
                                        0xFF );
                SDL_RenderClear(win_info->sdl_renderer);

                // on_repaint
                lua_rawgeti( _l, LUA_REGISTRYINDEX, win_info->refID );
                lua_getfield( _l, -1, "on_repaint" );
                if ( lua_isnil(_l,-1) == 0 && lua_isfunction(_l,-1) ) {
                    lua_pushvalue(_l,-2);
                    ex_lua_pcall( _l, 1, 0, idx ); 
                    lua_pop ( _l, 1 );
                }
                else {
                    lua_pop ( _l, 2 );
                }

                // flush
                SDL_RenderPresent(win_info->sdl_renderer);
                win_info->dirty = false;
            }
        ex_array_each_end

        lua_pop ( _l, 1 ); // pop error func

        SDL_Delay(10);
    }
}

// ------------------------------------------------------------------ 
// Desc: 
extern int __ex_lua_add_app ( lua_State * );
extern int __ex_lua_add_window ( lua_State * );
// ------------------------------------------------------------------ 

static void __wiz_init ( lua_State *_l, int _argc, char **_argv ) {
    //
    __window_list = ex_array_alloc ( sizeof(__window_info_t *), 8 );

    // push arguments to wiz.arguments in lua
    __lua_wiz_init ( _l, _argc, _argv );

    // create wiz_c table
    lua_newtable(_l);

        __ex_lua_add_app (_l);
        __ex_lua_add_window (_l);

        ex_lua_add_module ( _l, "wiz_c" );

    lua_pop(_l, 1);  /* remove wiz_c table */

    // execute main.lua if exists  
    if ( ex_fsys_exists ("main.lua") )
        ex_lua_dofile ( _l, "main.lua" );
} 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void __wiz_deinit ( lua_State *_l ) {
    __window_info_t *win_info;

    // destroy all windows 
    while ( ex_array_count(__window_list) > 0 ) {
        win_info = *(__window_info_t **)ex_array_get(__window_list, 0);
        destroy_window ( _l, win_info->refID );
    }
    ex_array_free ( __window_list );

    // call wiz.on_exit()
    __lua_wiz_on_exit (_l);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int main ( int _argc, char **_argv ) {
    lua_State *l;

    // ======================================================== 
    // init 
    // ======================================================== 

    // init SDL
    SDL_SetHint ( SDL_HINT_RENDER_DRIVER, "opengl" );
    // NOTE: it will also init mouse, keyboard, touch and events
    if ( SDL_VideoInit(0) < 0 ) {
        ex_log ( "[SDL] Error: Could not initialize SDL video driver: %s", SDL_GetError() );
        return 1;
    }
    SDL_GL_SetAttribute( SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1 );

    // init exsdk ( including allegro ) 
    if ( ex_sdk_init() != 0 ) {
        ex_log ( "Could not init exsdk!" );
        return 1;
    }

    // get the lua main state
    l = ex_lua_main_state();

    // load builtin modules
    ex_log ( "[exSDK] Loading builtin modules" );
    ex_lua_dofile ( l, "builtin/modules/init.lua" );

    // init wiz
    __wiz_init ( l, _argc, _argv );

    // ======================================================== 
    // loop 
    // ======================================================== 

    // enter the event-loop if we create display(window) 
    __event_loop (l);

    // ======================================================== 
    // de-init 
    // ======================================================== 

    // deinit wiz 
    __wiz_deinit(l);

    // deinit exsdk 
    ex_sdk_deinit ();

    // deinit SDL
    SDL_VideoQuit();

    return 0;
}

