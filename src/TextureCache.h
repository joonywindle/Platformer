#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H
#include <map>
#include "Texture.h"
class TextureCache
{
public:
	TextureCache();
	~TextureCache();
	
	std::map<std::string, Texture> texMap;
	
	
	Texture getTexture(std::string filePath);
	

};

#endif // TEXTURECACHE_H
