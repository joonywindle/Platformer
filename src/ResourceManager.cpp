#include "ResourceManager.h"

TextureCache ResourceManager::texCache;

Texture ResourceManager::getTexture(std::string filePath)
{
	return texCache.getTexture(filePath);
}

