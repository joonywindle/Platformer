#include "TextureCache.h"
#include "ImageLoader.h"
#include <iostream>
TextureCache::TextureCache()
{
}

TextureCache::~TextureCache()
{
}

Texture TextureCache::getTexture(std::string filePath)
{
	auto mapItr = texMap.find(filePath);

	if(mapItr == texMap.end())
	{
		Texture newTex = ImageLoader::loadPNG(filePath);
		//std::pair<std::string,Texture> newPair(filePath,newTex);

		texMap.insert(make_pair(filePath,newTex));
		return newTex;
	}
	return mapItr->second;
}
