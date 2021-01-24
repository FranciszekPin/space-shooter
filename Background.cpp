#include "Background.h"
#include "GameManager.h"
#include "constants.h"
#include "AssetManager.h"

int Background::scrollingOffset = 0;
AssetManager* assetManagerB = new AssetManager;

Background::Background() {
	assetManagerB->AddTexture("background", "assets/background.png");
};

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