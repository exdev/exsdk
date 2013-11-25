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
#include "SDL_image.h"
#include "SDL_main.h"
#include "exsdk.h"

///////////////////////////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////////////////////////

SDL_Window *window_1st;
SDL_Renderer *renderer_1st;

SDL_Window *window_2nd;
SDL_Renderer *renderer_2nd;

SDL_Texture *texture;

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

void LoadTexture ( const char *_file ) {
    SDL_Surface *temp;

    /* Load the sprite image */
    temp = IMG_Load(_file);
    if ( temp == NULL ) {
        fprintf ( stderr, "Couldn't load %s: %s", _file, SDL_GetError() );
        return;
    }

    /* Set transparent pixel as the pixel at (0,0) */
    if (temp->format->palette) {
        SDL_SetColorKey(temp, 1, *(Uint8 *) temp->pixels);
    } else {
        switch (temp->format->BitsPerPixel) {
        case 15:
            SDL_SetColorKey(temp, 1, (*(Uint16 *) temp->pixels) & 0x00007FFF);
            break;
        case 16:
            SDL_SetColorKey(temp, 1, *(Uint16 *) temp->pixels);
            break;
        case 24:
            SDL_SetColorKey(temp, 1, (*(Uint32 *) temp->pixels) & 0x00FFFFFF);
            break;
        case 32:
            SDL_SetColorKey(temp, 1, *(Uint32 *) temp->pixels);
            break;
        }
    }

    /* Create textures from the image */
    texture = SDL_CreateTextureFromSurface(renderer_1st, temp);
    if ( !texture ) {
        fprintf( stderr, "Couldn't create texture: %s\n", SDL_GetError() );
        SDL_FreeSurface(temp);
        return;
    }
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_FreeSurface(temp);

    /* We're ready to roll. :) */
    return;
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

int main ( int argc, char* argv[] ) {
    int done;
    SDL_Event event;
    SDL_Rect rect;

    // ======================================================== 
    // init 
    // ======================================================== 

    // init sdl video
    // NOTE: it will also init mouse, keyboard, touch and events
    if ( SDL_VideoInit(0) < 0 ) {
        fprintf ( stderr, "Couldn't initialize video driver: %s\n", SDL_GetError() );
        return 1;
    }

    SDL_GL_SetAttribute( SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1 );
    window_1st = SDL_CreateWindow( "Test", 
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                800, 600, 
                                SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN /*| SDL_WINDOW_BORDERLESS*/ 
                                );
    if ( window_1st == NULL ) {
        fprintf ( stderr, "Couldn't create window: %s\n", SDL_GetError() );
        return 1;
    }

    renderer_1st = SDL_CreateRenderer( window_1st, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if ( renderer_1st == NULL ) {
        fprintf ( stderr, "Couldn't create renderer_1st: %s\n", SDL_GetError() );
        return 1;
    }

    SDL_CreateWindowAndRenderer( 200, 200, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN, &window_2nd, &renderer_2nd );

    LoadTexture("../../../../../examples/test_graphics/assets/grossini_dance_09.png");

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

                        if (window == window_1st ) {
                            done = 1;
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

        // draw 1st
        SDL_SetRenderDrawColor(renderer_1st, 0xA0, 0xA0, 0xA0, 0xFF);
        SDL_RenderClear(renderer_1st);
        // DO DRAW HERE
        rect.x = 1;
        rect.y = 1;
        rect.w = 85;
        rect.h = 121;
        SDL_RenderCopy(renderer_1st, texture, NULL, &rect);
        SDL_RenderPresent(renderer_1st);

        // draw 2nd
        SDL_SetRenderDrawColor(renderer_2nd, 0xA0, 0xA0, 0xA0, 0xFF);
        SDL_RenderClear(renderer_2nd);
        // DO DRAW HERE FIXME: SDL don't allow user in multi-window share the same texture...
        rect.x = 1;
        rect.y = 1;
        rect.w = 85;
        rect.h = 121;
        if ( SDL_RenderCopy(renderer_2nd, texture, NULL, &rect) ) {
            // fprintf ( stderr, "Failed to render %s", SDL_GetError() );
        }
        SDL_RenderPresent(renderer_2nd);
    }

    // ======================================================== 
    // deinit 
    // ======================================================== 

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer_1st);
    SDL_DestroyRenderer(renderer_2nd);
    SDL_VideoQuit();

    return 0;
}

