#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include "TextureCache.h"
#include <string>
class ResourceManager
{
public:
	static Texture getTexture(std::string filePath);
private:
	static TextureCache texCache;

};

#endif // RESOURCEMANAGER_H
