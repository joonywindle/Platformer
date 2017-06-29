#include "ImageLoader.h"
#include "picopng.h"
#include "IOManager.h"
#include <iostream>

Texture ImageLoader::loadPNG(std::string filepath)
{
	Texture texture = {};
	std::vector<unsigned char> in;
	std::vector<unsigned char> out;
	unsigned long width, height;
	IOManager::readFileToBuffer(filepath, in);
	int errorCode = decodePNG(out,width,height,&in[0],in.size(),true);
	if(errorCode != 0)
	{
		std::cout << "Couldn't load png:  " << filepath << std::endl;
		exit(EXIT_FAILURE);
	}
	
	glGenTextures(1,&(texture.id));
	
	glBindTexture(GL_TEXTURE_2D, texture.id);
	
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, width, height, 0, GL_RGBA,GL_UNSIGNED_BYTE,&out[0]);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D,0);
	
	texture.width = width;
	texture.height = height;
	
	return texture;
	
}