#pragma once
#include <stdio.h>
#include <vector>
#include "sdlsystem.h"
#include "constants.h"

class Clock
{
	public:
		Clock(SDL_Renderer *renderer);
		SDL_Rect getTime();
		void getDigitParams(int a);
		void render();
	private:
		SDL_Rect src;
		SDL_Rect dst;
		SDL_Renderer *TheRenderer;
		SDL_Rect digitSRC;
		SDL_Rect digitDST;
		SDL_Texture* TheClock;
		std::vector<SDL_Texture*> textures;

};