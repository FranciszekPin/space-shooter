#include "AssetManager.h"
#include "GameManager.h"
#include "constants.h"

AssetManager::AssetManager()
{}

AssetManager::~AssetManager()
{}

void AssetManager::AddTexture(std::string id, const char* path)
{
	SDL_Surface* tempSurface = IMG_Load(path);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(GameManager::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	textures.emplace(id, tex);
}

void AssetManager::render(std::string id)
{
	SDL_Rect srcR, dstR;
	dstR.x = dstR.y = 0;
	dstR.w = SCREEN_WIDTH;
	dstR.h = SCREEN_HEIGHT;

	srcR.x = srcR.y = 0;
	srcR.w = SCREEN_WIDTH;
	srcR.h = SCREEN_HEIGHT;

	SDL_RenderCopy(GameManager::renderer, GetTexture(id), NULL, &dstR);
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}

