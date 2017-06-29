#ifndef SPRITE_H
#define SPRITE_H
#include <GL/glew.h>
#include "Texture.h"
#include <string>
class Sprite
{
public:
	Sprite();
	~Sprite();
	
	void draw();
	void init(float _x, float _y, float _width, float _height, std::string texturePath);
	
private:
	float x;
	float y;
	float width;
	float height;
	
	GLuint vboID;
	
	Texture texture;

};

#endif // SPRITE_H
