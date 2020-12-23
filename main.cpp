#include <stdio.h>
#include "sdlsystem.h"
#include "constants.h"

int main(int argc, char *args[]) {
    //The window we'll be rendering to
    SDL_Window *window = NULL;

    SDL_Renderer *renderer;

    SDL_Surface *image = NULL;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    } else {
        //Create window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        } else {
            //Get window surface
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if( renderer == NULL ) {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
            }
            else {
                //Initialize renderer color
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Main loop flag
                bool quit = false;

                //Event handler
                SDL_Event e;

                while (!quit) {
                    while (SDL_PollEvent(&e) != 0) {
                        if (e.type == SDL_QUIT) {
                            quit = true;
                        }
                    }
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                    SDL_RenderClear(renderer);

                    //Render red filled quad
                    SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
                    SDL_RenderFillRect(renderer, &fillRect);

                    SDL_RenderPresent(renderer);
                }

            }

        }
    }

    //Destroy window
    SDL_DestroyWindow(window);



    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}