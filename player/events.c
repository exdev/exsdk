// ======================================================================================
// File         : events.c
// Author       : Wu Jie 
// Last Change  : 04/22/2013 | 16:22:47 PM | Monday,April
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "allegro5/allegro.h"
#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
// defines
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

static int process_event ( ALLEGRO_EVENT _event ) {
    switch ( _event.type ) {
    case ALLEGRO_EVENT_DISPLAY_RESIZE:
        al_acknowledge_resize(_event.display.source);
        break;

    case ALLEGRO_EVENT_DISPLAY_EXPOSE:
        break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
        return 1;
        break;

    case ALLEGRO_EVENT_KEY_DOWN:
        if ( _event.keyboard.keycode == ALLEGRO_KEY_ESCAPE )
            return 1;
        break;
    }

    return 0;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void main_loop () {
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *queue;
    ALLEGRO_EVENT event;

    // init allegro keyboard
    al_install_keyboard();

    // init allegro display
    al_set_new_display_flags( ALLEGRO_OPENGL
                            | ALLEGRO_RESIZABLE
                            | ALLEGRO_GENERATE_EXPOSE_EVENTS
                            // | ALLEGRO_FRAMELESS
                            );
    display = al_create_display(640,480);
    if ( !display ) {
        ex_log ( "Could not create allegro display!" );
        exit(1);
    }

    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));

    // call app.on_init()
    ex_lua_app_on_init ( ex_lua_main_state() );

    // NOTE: there is two ways for update, using Timer or using Event-Poll, 
    // the timer is suitable for GUI tool, and Event-Poll is better for game

    // start main-loop
    while (1) {
        // call app.on_update()
        ex_lua_app_on_update ( ex_lua_main_state() );

        // handle events
        if ( !al_is_event_queue_empty(queue) ) {
            while ( al_get_next_event(queue, &event) ) {
                if ( process_event(event) ) {
                    goto done;
                }
            }
        }
        else {
            // draw one frame
            // call app.on_draw()
            ex_lua_app_on_draw ( ex_lua_main_state() );
        }
    }

    // finish
done:
    // call app.on_exit()
    ex_lua_app_on_exit ( ex_lua_main_state() );

    al_destroy_event_queue(queue);  
    al_destroy_display(display);
}
