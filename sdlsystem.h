//
// Created by learning-account on 23.12.2020.
//

#ifndef UNTITLED2_SDLSYSTEM_H
#define UNTITLED2_SDLSYSTEM_H

#ifdef __linux__
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_mixer.h>
#else
    #include <SDL.h>
    #include <SDL_image.h>
    #include <SDL_mixer.h>
#endif

#endif //UNTITLED2_SDLSYSTEM_H
