#include "Background.h"
#include "GameManager.h"
#include "constants.h"
#include "AssetManager.h"

int Background::scrollingOffset = 0;
AssetManager* assetManagerB = new AssetManager;

Background::Background() {
	assetManagerB->AddTexture("background", "assets/background.png");
}
Background::Background(int x)
{
	assetManagerB->AddTexture("deathscreen", "assets/deathscreen.png");
	SDL_Rect bg = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_RenderCopy(GameManager::renderer, assetManagerB->GetTexture("deathscreen"), NULL, &bg);
}

void Background::render2()
{
	SDL_Rect bg = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_RenderCopy(GameManager::renderer, assetManagerB->GetTexture("deathscreen"), NULL, &bg);
}

void Background::render() {

	++scrollingOffset;

	if (scrollingOffset > SCREEN_HEIGHT) {
		scrollingOffset = 0;
	}

	SDL_Rect renderQuad = {0, scrollingOffset, SCREEN_WIDTH, SCREEN_HEIGHT};

	SDL_RenderCopy(GameManager::renderer, assetManagerB->GetTexture("background"), NULL, &renderQuad);

	renderQuad = {0, scrollingOffset-SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT};

	SDL_RenderCopy(GameManager::renderer, assetManagerB->GetTexture("background"), NULL, &renderQuad);

}