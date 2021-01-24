#include <stdio.h>
#include "sdlsystem.h"
#include "constants.h"
#include "MusicManager.h"

void MusicManager::init()
{
	background = Mix_LoadMUS("sounds/vaporwave.mp3");
    alienshot = Mix_LoadWAV("sounds/sound1.wav");
    explosion = Mix_LoadWAV("sounds/sound2.wav");
    smallshot = Mix_LoadWAV("sounds/sound3.wav");
    //  Mix_FreeChunk(explosion);
    //  Mix_FreeMusic(background);
    Mix_VolumeChunk(alienshot, soundVolume);
    Mix_VolumeChunk(explosion, soundVolume);
    Mix_VolumeChunk(smallshot, soundVolume);
    Mix_VolumeMusic(soundVolume);

}
void MusicManager::playAlienShot()
{
	if(Mix_PlayChannel(-1, alienshot, 0) == -1)
	   {
            printf("Mix_PlayChannel alien: %s\n",Mix_GetError());
 
        }
}
void MusicManager::playShot()
{
    if(  Mix_PlayChannel(-1,smallshot , 0) == -1 )
     {
            printf("Mix_PlayChannel shot: %s\n",Mix_GetError());
 
        }
}
void MusicManager::playExplosion()
{
	if(Mix_PlayChannel(-1, explosion, 0) == -1)
       {
           printf("Mix_PlayChannel explosion: %s\n",Mix_GetError());
 
        }
}
void MusicManager::playBackground()
{
   Mix_PlayMusic(background, -1);
}