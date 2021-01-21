#include "AssetManager.h"
#include "GameManager.h"

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

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return textures[id];
}