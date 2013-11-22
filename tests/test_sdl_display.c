// ======================================================================================
// File         : test_sdl_display.c
// Author       : Wu Jie 
// Last Change  : 11/22/2013 | 15:14:19 PM | Friday,November
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "SDL.h"
#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

SDL_Window *sdl_win;
SDL_Renderer *sdl_renderer;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int main ( int argc, char* argv[] ) {
    int done;
    SDL_Event event;

    // ======================================================== 
    // init 
    // ======================================================== 

    // init sdl video
    // NOTE: it will also init mouse, keyboard, touch and events
    if ( SDL_VideoInit(0) < 0 ) {
        fprintf ( stderr, "Couldn't initialize video driver: %s\n", SDL_GetError() );
        return 1;
    }

    sdl_win = SDL_CreateWindow( "Test", 
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                800, 600, 
                                SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN /*| SDL_WINDOW_BORDERLESS*/ 
                                );
    if ( sdl_win == NULL ) {
        fprintf ( stderr, "Couldn't create window: %s\n", SDL_GetError() );
        return 1;
    }

    sdl_renderer = SDL_CreateRenderer( sdl_win, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if ( sdl_renderer == NULL ) {
        fprintf ( stderr, "Couldn't create sdl_renderer: %s\n", SDL_GetError() );
        return 1;
    }

    // ======================================================== 
    // loop 
    // ======================================================== 

    done = 0;
    while ( !done ) {
        /* Check for events */
        while ( SDL_PollEvent(&event) ) {
            switch (event.type) {
            case SDL_WINDOWEVENT:
                switch (event.window.event) {
                case SDL_WINDOWEVENT_CLOSE:
                    {
                        SDL_Window *window = SDL_GetWindowFromID(event.window.windowID);
                        if (window) {
                            SDL_DestroyWindow(window);
                        }
                    }
                    break;
                }
                break;

            case SDL_QUIT:
                done = 1;
                break;
            }
        }

        // draw
        SDL_SetRenderDrawColor(sdl_renderer, 0xA0, 0xA0, 0xA0, 0xFF);
        SDL_RenderClear(sdl_renderer);

        // DrawRects(sdl_renderer);
        // DrawLines(sdl_renderer);
        // DrawPoints(sdl_renderer);

        SDL_RenderPresent(sdl_renderer);
    }

    // ======================================================== 
    // deinit 
    // ======================================================== 

    SDL_DestroyRenderer(sdl_renderer);
    SDL_VideoQuit();

    return 0;
}

