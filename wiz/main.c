// ======================================================================================
// File         : main.c
// Author       : Wu Jie 
// Last Change  : 05/07/2013 | 14:48:30 PM | Tuesday,May
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

#include "allegro5/allegro.h"
#include "exsdk.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#if ( EX_PLATFORM == EX_MACOSX )
    #define main _al_mangled_main
#endif

typedef struct __window_info_t {
    ALLEGRO_DISPLAY *display;
    int refID; // NOTE: this is luaL_ref return value, must use luaL_unref to release it.
    bool dirty;
    ALLEGRO_COLOR bg_color;
} __window_info_t;

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

ALLEGRO_DISPLAY *primary_display = NULL;
static ex_array_t *__window_list = NULL;
ALLEGRO_EVENT_QUEUE *queue = NULL;

///////////////////////////////////////////////////////////////////////////////
// defines
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

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void create_window ( int _id, int _w, int _h ) {
    ALLEGRO_DISPLAY *display;
    __window_info_t *win_info;

    // init allegro display
    al_set_new_display_flags( ALLEGRO_OPENGL
                            | ALLEGRO_RESIZABLE
                            | ALLEGRO_GENERATE_EXPOSE_EVENTS
                            // | ALLEGRO_FRAMELESS
                            );
    display = al_create_display( _w, _h );
    if ( !display ) {
        ex_log ( "Could not create allegro display!" );
        exit(1);
    }

    // if this is the first window, create queue
    if ( ex_array_count(__window_list) == 0 ) {
        queue = al_create_event_queue();
        primary_display = display;
    }

    // add window info
    win_info = ex_malloc( sizeof(__window_info_t) );
    win_info->display = display;
    win_info->refID = _id;
    win_info->dirty = true;
    ex_array_add ( __window_list, &win_info );

    al_register_event_source(queue, al_get_display_event_source(display));
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void destroy_window ( int _id ) {
    int idx = -1;
    size_t i = 0;
    lua_State *l;
    __window_info_t *win_info;

    //
    l = ex_lua_main_state();

    // error func
    lua_pushcfunction( l, ex_lua_trace_back );
    idx = lua_gettop(l);

    // get window
    while ( i < ex_array_count(__window_list) ) {
        win_info = *(__window_info_t **)ex_array_get(__window_list, i);
        if ( win_info->refID == _id ) {
            break;
        }
        ++i;
    }

    // call win_info.refID.on_destroy { 
    lua_rawgeti( l, LUA_REGISTRYINDEX, win_info->refID );
    lua_getfield( l, -1, "on_destroy" );
    if ( lua_isnil(l,-1) == 0 && lua_isfunction(l,-1) ) {
        lua_pushvalue(l,-2);
        ex_lua_pcall( l, 1, 0, idx ); 
        lua_pop ( l, 1 ); // pop win_info.refID
    }
    else {
        lua_pop ( l, 2 ); // pop win_info.refID
    }
    lua_pop ( l, 1 ); // pop error func

    //
    ex_array_remove_at_fast ( __window_list, i );
    luaL_unref( l, LUA_REGISTRYINDEX, win_info->refID );
    al_destroy_display(win_info->display);
    ex_free(win_info);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void repaint_window ( int _id ) {
    size_t i = 0;
    __window_info_t *win_info;

    while ( i < ex_array_count(__window_list) ) {
        win_info = *(__window_info_t **)ex_array_get(__window_list, i);
        if ( win_info->refID == _id ) {
            win_info->dirty = true;
            break;
        }
        ++i;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

ALLEGRO_DISPLAY *get_display ( int _id ) {
    size_t i = 0;
    __window_info_t *win_info;

    while ( i < ex_array_count(__window_list) ) {
        win_info = *(__window_info_t **)ex_array_get(__window_list, i);
        if ( win_info->refID == _id ) {
            return win_info->display;
        }
        ++i;
    }

    return NULL;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int get_window_ref_id ( ALLEGRO_DISPLAY * _display ) {
    size_t i = 0;
    __window_info_t *win_info;

    while ( i < ex_array_count(__window_list) ) {
        win_info = *(__window_info_t **)ex_array_get(__window_list, i);
        if ( win_info->display == _display ) {
            return win_info->refID;
        }
        ++i;
    }

    return LUA_REFNIL;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void set_window_background ( int _id, int _r, int _g, int _b ) {
    size_t i = 0;
    __window_info_t *win_info;

    while ( i < ex_array_count(__window_list) ) {
        win_info = *(__window_info_t **)ex_array_get(__window_list, i);
        if ( win_info->refID == _id ) {
            win_info->bg_color = al_map_rgb( _r, _g, _b );
            win_info->dirty = true;
            break;
        }
        ++i;
    }
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int process_event ( ALLEGRO_EVENT _event ) {
    lua_State *l;
    int refID;
    int idx = -1;

    l = ex_lua_main_state();

    //
    switch ( _event.type ) {
    case ALLEGRO_EVENT_DISPLAY_RESIZE:
        al_acknowledge_resize(_event.display.source);

        // error func
        lua_pushcfunction( l, ex_lua_trace_back );
        idx = lua_gettop(l);

        // call window.on_resize(w,h)
        refID = get_window_ref_id(_event.display.source);
        lua_rawgeti( l, LUA_REGISTRYINDEX, refID );
        lua_getfield( l, -1, "on_resize" );
        if ( lua_isnil(l,-1) == 0 && lua_isfunction(l,-1) ) {
            lua_pushvalue(l,-2);
            lua_pushinteger(l,_event.display.width);
            lua_pushinteger(l,_event.display.height);
            ex_lua_pcall( l, 3, 0, idx ); 
            lua_pop ( l, 1 ); // pop win_info.refID
        }
        else {
            lua_pop ( l, 2 );
        }
        lua_pop ( l, 1 ); // pop error func

        //
        repaint_window (refID);

        break;

    case ALLEGRO_EVENT_DISPLAY_EXPOSE:
        break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        // if we are close the primary display, quit the wiz
        if ( _event.display.source == primary_display )
            return 1;

        refID = get_window_ref_id(_event.display.source);
        destroy_window (refID);

        if ( ex_array_count (__window_list) == 0 )
            return 1;
        break;

    case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
        refID = get_window_ref_id(_event.display.source);

        // error func
        lua_pushcfunction( l, ex_lua_trace_back );
        idx = lua_gettop(l);

        // call window.on_resize(w,h)
        refID = get_window_ref_id(_event.display.source);
        lua_rawgeti( l, LUA_REGISTRYINDEX, refID );
        lua_getfield( l, -1, "on_focus" );
        if ( lua_isnil(l,-1) == 0 && lua_isfunction(l,-1) ) {
            lua_pushvalue(l,-2);
            ex_lua_pcall( l, 1, 0, idx ); 
            lua_pop ( l, 1 ); // pop win_info.refID
        }
        else {
            lua_pop ( l, 2 );
        }
        lua_pop ( l, 1 ); // pop error func

        repaint_window (refID);
        break;

    case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
        refID = get_window_ref_id(_event.display.source);

        // error func
        lua_pushcfunction( l, ex_lua_trace_back );
        idx = lua_gettop(l);

        // call window.on_resize(w,h)
        refID = get_window_ref_id(_event.display.source);
        lua_rawgeti( l, LUA_REGISTRYINDEX, refID );
        lua_getfield( l, -1, "on_unfocus" );
        if ( lua_isnil(l,-1) == 0 && lua_isfunction(l,-1) ) {
            lua_pushvalue(l,-2);
            ex_lua_pcall( l, 1, 0, idx ); 
            lua_pop ( l, 1 ); // pop win_info.refID
        }
        else {
            lua_pop ( l, 2 );
        }
        lua_pop ( l, 1 ); // pop error func

        repaint_window (refID);
        break;

    case ALLEGRO_EVENT_KEY_DOWN:
        // lua_getglobal( l, "wiz" );
        // lua_getfield( l, -1, "event" );

        //     // set event_type.type
        //     lua_getglobal( l, "event_type" );
        //     lua_getfield( l, -1, "key_down" );
        //     lua_setfield( l, -3, "type" );
        //     lua_pop (l,1);

        //     // set event_type.display
        //     lua_pushlightuserdata( l, _event.keyboard.display );
        //     lua_setfield( l, -2, "display" );

        //     // set event_type.keycode
        //     lua_pushinteger( l, _event.keyboard.keycode );
        //     lua_setfield( l, -2, "keycode" );

        // lua_pop (l,2);
        break;

    case ALLEGRO_EVENT_KEY_UP:
        // lua_getglobal( l, "wiz" );
        // lua_getfield( l, -1, "event" );

        //     // set event_type.type
        //     lua_getglobal( l, "event_type" );
        //     lua_getfield( l, -1, "key_up" );
        //     lua_setfield( l, -3, "type" );
        //     lua_pop (l,1);

        //     // set event_type.display
        //     lua_pushlightuserdata( l, _event.keyboard.display );
        //     lua_setfield( l, -2, "display" );

        //     // set event_type.keycode
        //     lua_pushinteger( l, _event.keyboard.keycode );
        //     lua_setfield( l, -2, "keycode" );

        // lua_pop (l,2);
        break;

    case ALLEGRO_EVENT_MOUSE_AXES:
        // lua_getglobal( l, "wiz" );
        // lua_getfield( l, -1, "event" );

        //     // set event_type.type
        //     lua_getglobal( l, "event_type" );
        //     lua_getfield( l, -1, "mouse_move" );
        //     lua_setfield( l, -3, "type" );
        //     lua_pop (l,1);

        //     // set event_type.display
        //     lua_pushlightuserdata( l, _event.keyboard.display );
        //     lua_setfield( l, -2, "display" );

        //     // set event_type.mouse_pos_x,y
        //     lua_pushinteger( l, _event.mouse.x );
        //     lua_setfield( l, -2, "mouse_pos_x" );
        //     lua_pushinteger( l, _event.mouse.y );
        //     lua_setfield( l, -2, "mouse_pos_y" );

        //     // set event_type.mouse_delta_x,y
        //     lua_pushinteger( l, _event.mouse.dx );
        //     lua_setfield( l, -2, "mouse_delta_x" );
        //     lua_pushinteger( l, _event.mouse.dy );
        //     lua_setfield( l, -2, "mouse_delta_y" );

        // lua_pop (l,2);
        break;
    }

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void event_loop () {
    ALLEGRO_EVENT event;
    lua_State *l;
    ALLEGRO_BITMAP *target;
    int idx = -1;

    l = ex_lua_main_state();

    // init allegro keyboard
    al_install_keyboard();
    al_register_event_source(queue, al_get_keyboard_event_source());

    // NOTE: there is two ways for update, using Timer or using Event-Poll, 
    // the timer is suitable for GUI tool, and Event-Poll is better for game

    // start main-loop
    while (1) {
        // error func
        lua_pushcfunction( l, ex_lua_trace_back );
        idx = lua_gettop(l);

        // call window.on_update in lua
        ex_array_each ( __window_list, __window_info_t *, win_info )
            lua_rawgeti( l, LUA_REGISTRYINDEX, win_info->refID );
            lua_getfield( l, -1, "on_update" );
            if ( lua_isnil(l,-1) == 0 && lua_isfunction(l,-1) ) {
                lua_pushvalue(l,-2);
                ex_lua_pcall( l, 1, 0, idx ); 
                lua_pop ( l, 1 );
            }
            else {
                lua_pop ( l, 2 );
            }
        ex_array_each_end

        // handle events
        while ( !al_is_event_queue_empty(queue) ) {
            al_get_next_event(queue, &event);
            if ( process_event(event) ) {
                goto done;
            }
        }

        // draw one frame
        // call window.on_repaint in lua
        ex_array_each ( __window_list, __window_info_t *, win_info )
            if ( win_info->dirty ) {
                // set target bitmap
                target = al_get_backbuffer(win_info->display);
                al_set_target_bitmap(target);

                // clear background
                al_clear_to_color( win_info->bg_color );
                al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

                // on_repaint
                lua_rawgeti( l, LUA_REGISTRYINDEX, win_info->refID );
                lua_getfield( l, -1, "on_repaint" );
                if ( lua_isnil(l,-1) == 0 && lua_isfunction(l,-1) ) {
                    lua_pushvalue(l,-2);
                    ex_lua_pcall( l, 1, 0, idx ); 
                    lua_pop ( l, 1 );
                }
                else {
                    lua_pop ( l, 2 );
                }

                // flush
                al_flip_display();
                win_info->dirty = false;
            }
        ex_array_each_end

        lua_pop ( l, 1 ); // pop error func

        //
        al_rest(0.001);
    }

    // finish
done:
    al_destroy_event_queue(queue);  
}

// ------------------------------------------------------------------ 
// Desc: 
extern int __ex_lua_add_app ( lua_State * );
extern int __ex_lua_add_window ( lua_State * );
// ------------------------------------------------------------------ 

static void __wiz_init ( int _argc, char **_argv ) {
    lua_State *l = ex_lua_main_state();

    // push arguments to wiz.arguments in lua
    __lua_wiz_init ( l, _argc, _argv );

    //
    __window_list = ex_array_alloc ( sizeof(__window_info_t *), 8 );

    // create wiz_c table
    lua_newtable(l);

        __ex_lua_add_app (l);
        __ex_lua_add_window (l);

        ex_lua_add_module ( l, "wiz_c" );

    lua_pop(l, 1);  /* remove wiz_c table */

    // execute main.lua if exists  
    if ( ex_fsys_exists ("main.lua") )
        ex_lua_dofile ( l, "main.lua" );
} 

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void __wiz_deinit () {
    ex_array_free ( __window_list );
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int main ( int _argc, char **_argv ) {
    lua_State *l;
    __window_info_t *win_info;

    // ======================================================== 
    // init 
    // ======================================================== 

    // init exsdk ( including allegro ) 
    if ( ex_sdk_init() != 0 ) {
        ex_log ( "Could not init exsdk!" );
        return 1;
    }

    l = ex_lua_main_state();

    // load builtin modules
    ex_log ( "[exSDK] Loading builtin modules" );
    ex_lua_dofile ( l, "builtin/modules/init.lua" );

    // init wiz
    __wiz_init ( _argc, _argv );

    // ======================================================== 
    // loop 
    // ======================================================== 

    // enter the event-loop if we create display(window) 
    if ( ex_array_count (__window_list) > 0 ) {
        event_loop ();
    }

    // ======================================================== 
    // de-init 
    // ======================================================== 

    // destroy all windows 
    while ( ex_array_count(__window_list) > 0 ) {
        win_info = *(__window_info_t **)ex_array_get(__window_list, 0);
        destroy_window (win_info->refID);
    }

    // call wiz.on_exit()
    __lua_wiz_on_exit (l);

    // deinit wiz 
    __wiz_deinit();

    // deinit exsdk 
    ex_sdk_deinit ();

    return 0;
}

