#ifndef IMAGELOADER_H
#define IMAGELOADER_H
#include "Texture.h"
#include <string>

class ImageLoader
{
public:
	static Texture loadPNG(std::string filepath);

};

#endif // IMAGELOADER_H
