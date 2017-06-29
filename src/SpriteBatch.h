#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H
#include <GL/glew.h>
#include "Vertex.h"
#include <glm/glm.hpp>
#include <vector>

enum class GlyphSortType {
	NONE,
	FRONT_BACK,
	BACK_FRONT,
	TEXTURE
};

struct Glyph {
	GLuint texture;
	float depth;
	Vertex topLeft;
	Vertex bottomLeft;
	Vertex topRight;
	Vertex bottomRight;
	Color color;
};

class RenderBatch
{
public:
	RenderBatch(GLuint _offset,GLuint _numVertices, GLuint  _texture) : offset(_offset), numVertices(_numVertices),texture(_texture)
	{
		
	}
	GLuint offset;
	GLuint numVertices;
	GLuint texture;
	
};

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();
	void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
	void end();
	void draw(const glm::vec4& destRect, const glm::vec4& uVRect, GLuint texture, float depth, Color color);
	void renderBatch();
	void init();
private:
	GLuint vbo;
	GLuint vao;
	std::vector<Glyph*> glyphs;
	std::vector<RenderBatch> renderBatches;
	GlyphSortType sortType;
	void createVertexArray();
	void sortGlyphs();
	void createRenderBatches();
	
	static bool compareFrontBack(Glyph* a, Glyph* b);
	static bool compareBackFront(Glyph* a, Glyph* b);
	static bool compareTexture(Glyph* a, Glyph* b);

};

#endif // SPRITEBATCH_H
