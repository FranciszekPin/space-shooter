#include "Background.h"
#include "AssetManager.h"
#include "GameManager.h"
#include "constants.h"

Background::Background() {};

int Background::scrollingOffset = 0;

void Background::render() {
	AssetManager* assetManager = new AssetManager();
	assetManager->AddTexture("background", "assets/background.png");

	++scrollingOffset;

	if (scrollingOffset > SCREEN_HEIGHT) {
		scrollingOffset = 0;
	}

	SDL_Rect renderQuad = {0, scrollingOffset, SCREEN_WIDTH, SCREEN_HEIGHT};

	SDL_RenderCopy(GameManager::renderer, assetManager->GetTexture("background"), NULL, &renderQuad);

	renderQuad = {0, scrollingOffset-SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT};

	SDL_RenderCopy(GameManager::renderer, assetManager->GetTexture("background"), NULL, &renderQuad);

}