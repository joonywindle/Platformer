#ifndef VERTEX_H
#define VERTEX_H
#include <GL/glew.h>

struct Position{
	float x;
	float y;
};

struct Color {
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte alpha;
};

struct UV {
	float u;
	float v;
};
struct Vertex {
	Position position;
	Color color;
	UV uv;
	
	void setColor(GLubyte r, GLubyte g,GLubyte b,GLubyte alpha)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.alpha= alpha;
	}
	
	void setColor(Color _color)
	{
		color = _color;
	}
	
	void setUV(float u, float v)
	{
		uv.u = u;
		uv.v = v;
	}
	
	void setPosition(float x, float y)
	{
		position.x = x;
		position.y = y;
	}
};

#endif // VERTEX_H
