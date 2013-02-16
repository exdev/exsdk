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
    bool redraw, abort;

    // init allegro keyboard
    al_install_keyboard();

    // init allegro display
    al_set_new_display_flags( ALLEGRO_RESIZABLE|ALLEGRO_GENERATE_EXPOSE_EVENTS );
    display = al_create_display(640,480);
    if ( !display ) {
        ex_log ( "Could not create allegro display!" );
        exit(1);
    }

    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));

    // start main-loop
    // ex_lua_run_interpretor ( ex_lua_main_state() );
    ex_lua_dofile ( ex_lua_main_state(), "main.lua" );
    redraw = true;
    abort = false;
    while (1) {
        // draw one frame
        if ( redraw && al_is_event_queue_empty(queue) ) {
            al_clear_to_color( al_map_rgb(0,128,255) );
            al_flip_display();
        }

        // handle events
        al_wait_for_event(queue, &event);
        switch ( event.type ) {
        case ALLEGRO_EVENT_DISPLAY_RESIZE:
            al_acknowledge_resize(event.display.source);
            redraw = true;
            break;

        case ALLEGRO_EVENT_DISPLAY_EXPOSE:
            redraw = true;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            abort = true;
            break;

        case ALLEGRO_EVENT_KEY_DOWN:
            if ( event.keyboard.keycode == ALLEGRO_KEY_ESCAPE )
                abort = true;
            break;
        }

        //
        if ( abort ) 
            break;
    }

    //
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

