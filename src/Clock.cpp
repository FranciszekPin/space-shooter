
#include <stdio.h>
#include "sdlsystem.h"
#include "constants.h"
#include "Clock.h"
#include <vector>
Clock::Clock(SDL_Renderer *renderer)
{
 src.x = 0;
 src.y = 0;
 src.h = 12;
 src.w = 22;

 dst.x = SCREEN_WIDTH - (src.w*6);
 dst.y = 0;
 dst.h = 12*6;
 dst.w = 22*6;

 digitSRC = src;
 digitSRC.h = 5;
 digitSRC.w = 3;
 TheRenderer = renderer;
 TheClock = IMG_LoadTexture(renderer,"assets/clock.png");

 textures = {
                    IMG_LoadTexture(renderer,"assets/0.png"),
                    IMG_LoadTexture(renderer,"assets/1.png"),
                    IMG_LoadTexture(renderer,"assets/2.png"),
                    IMG_LoadTexture(renderer,"assets/3.png"),
                    IMG_LoadTexture(renderer,"assets/4.png"),
                    IMG_LoadTexture(renderer,"assets/5.png"),
                    IMG_LoadTexture(renderer,"assets/6.png"),
                    IMG_LoadTexture(renderer,"assets/7.png"),
                    IMG_LoadTexture(renderer,"assets/8.png"),
                    IMG_LoadTexture(renderer,"assets/9.png")};


}
SDL_Rect Clock::getTime()
{
	SDL_Rect time;
	float t = SDL_GetTicks();
		t *= 0.001f;
		int sek = round(t);
	time.x = (sek%60)%10 ;
	time.y = (sek%60)/10 ;
	time.w = (sek/60)%10;
	time.h = ((sek/60)/10)%10;
		return time;
}

void Clock::getDigitParams(int a)
{
	digitDST.y = 30;
	digitDST.w = 3*6;
	digitDST.h = 5*6;
	switch(a)
	{
		case 1:
		digitDST.x = SCREEN_WIDTH - 30;
			break;
		case 2:
		digitDST.x = SCREEN_WIDTH - 54;
			break;
		case 3:
		digitDST.x = SCREEN_WIDTH - 90;
			break;
		case 4:
		digitDST.x = SCREEN_WIDTH - 114;
			break;
	}
}
void Clock::render()
{
		SDL_RenderCopy(TheRenderer, TheClock, &src,&dst);
					getDigitParams(1);
		SDL_RenderCopy(TheRenderer, textures[getTime().x],&digitSRC,&digitDST);
		 			getDigitParams(2);
        SDL_RenderCopy(TheRenderer, textures[getTime().y],&digitSRC,&digitDST);
          			getDigitParams(3);
        SDL_RenderCopy(TheRenderer, textures[getTime().w],&digitSRC,&digitDST);
         			getDigitParams(4);
        SDL_RenderCopy(TheRenderer, textures[getTime().h],&digitSRC,&digitDST);
		
		SDL_RenderPresent(TheRenderer);
}
