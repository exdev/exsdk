// ======================================================================================
// File         : main.c
// Author       : Wu Jie 
// Last Change  : 01/05/2013 | 17:44:08 PM | Saturday,January
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

#include "allegro5/allegro.h"
#include "exsdk.h"

#if ( EX_PLATFORM == EX_MACOSX )
    #define main _al_mangled_main
#endif

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static void main_loop () {
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_EVENT event;

    // init allegro keyboard
    al_install_keyboard();

    // init allegro display
    al_set_new_display_flags( ALLEGRO_OPENGL
                            | ALLEGRO_RESIZABLE
                            | ALLEGRO_GENERATE_EXPOSE_EVENTS );
    display = al_create_display(640,480);
    if ( !display ) {
        ex_log ( "Could not create allegro display!" );
        exit(1);
    }

    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));

    // parsing main.lua
    // ex_lua_run_interpretor ( ex_lua_main_state() );
    ex_lua_parse_main ( ex_lua_main_state() );
    ex_lua_main_init ( ex_lua_main_state() );

    // NOTE: there is two ways for update, using Timer or using Event-Poll, 
    // the timer is suitable for GUI tool, and Event-Poll is better for game

    // start main-loop
    while (1) {
        //
        ex_lua_main_update ( ex_lua_main_state() );

        // draw one frame
        if ( al_is_event_queue_empty(queue) ) {
            // al_clear_to_color( al_map_rgb(0,128,255) );
            al_clear_to_color( al_map_rgb(0,0,0) );
            ex_lua_main_render( ex_lua_main_state() );
            al_flip_display();
        }

        // handle events
        if ( !al_is_event_queue_empty(queue) ) {
            while ( al_get_next_event(queue, &event) ) {
                switch ( event.type ) {
                case ALLEGRO_EVENT_DISPLAY_RESIZE:
                    al_acknowledge_resize(event.display.source);
                    break;

                case ALLEGRO_EVENT_DISPLAY_EXPOSE:
                    break;

                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    goto done;
                    break;

                case ALLEGRO_EVENT_KEY_DOWN:
                    if ( event.keyboard.keycode == ALLEGRO_KEY_ESCAPE )
                        goto done;
                    break;
                }
            }
        }
    }

    // deinit
done:
    ex_lua_main_deinit ( ex_lua_main_state() );
    al_destroy_display(display);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int main (void) {
    char path[MAX_PATH];

    // ======================================================== 
    // init 
    // ======================================================== 

    // init exsdk ( including allegro ) 
    if ( ex_sdk_init() != 0 ) {
        ex_log ( "Could not init exsdk!" );
        return 1;
    }

    // load project
    strncpy ( path, ex_fsys_app_dir(), MAX_PATH );
    strcat ( path, "Main/" );
    ex_unix_path(path);
    ex_sdk_open_project ( path );

    // ======================================================== 
    // main-loop 
    // ======================================================== 

    main_loop ();

    // ======================================================== 
    // de-init 
    // ======================================================== 

    // deinits 
    ex_sdk_deinit ();

    return 0;
}

