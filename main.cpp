#include <stdio.h>
#include "sdlsystem.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *args[]) {
    //The window we'll be rendering to
    SDL_Window *window = NULL;

    //The surface contained by the window
    SDL_Surface *screenSurface = NULL;

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
            screenSurface = SDL_GetWindowSurface(window);

            //Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            image = SDL_LoadBMP("assets/purple_rectangle.bmp");

            if(image == NULL )
            {
                printf( "Unable to load image %s! SDL Error: %s\n", "assets/purple_rectangle.bmp", SDL_GetError());
            } else {
                SDL_BlitSurface(image, NULL, screenSurface, NULL);
            }
            //Update the surface
            SDL_UpdateWindowSurface(window);

            //Wait two seconds
            SDL_Delay(10000);
        }
    }

    SDL_FreeSurface(image);
    image = NULL;


    //Destroy window
    SDL_DestroyWindow(window);



    //Quit SDL subsystems
    SDL_Quit();

    return 0;
}