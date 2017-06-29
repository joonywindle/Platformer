#include "SpriteBatch.h"
#include <algorithm>

SpriteBatch::SpriteBatch() : vbo(0), vao(0)
{
}

SpriteBatch::~SpriteBatch()
{
}

void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uVRect, GLuint texture,float depth, Color color)
{
	Glyph* newGlyph = new Glyph;
	newGlyph->texture = texture;
	newGlyph->depth = depth;
	newGlyph->color = color;
	
	newGlyph->topLeft.setColor(color);
	newGlyph->topLeft.setPosition(destRect.x,destRect.y + destRect.w);
	newGlyph->topLeft.setUV(uVRect.x,uVRect.y + uVRect.w);
	
	newGlyph->bottomLeft.setColor(color);
	newGlyph->bottomLeft.setPosition(destRect.x,destRect.y);
	newGlyph->bottomLeft.setUV(uVRect.x,uVRect.y);
	
	newGlyph->topRight.setColor(color);
	newGlyph->topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
	newGlyph->topRight.setUV(uVRect.x + uVRect.z, uVRect.y + uVRect.w);
	
	newGlyph->bottomRight.setColor(color);
	newGlyph->bottomRight.setPosition(destRect.x + destRect.z,  destRect.y);
	newGlyph->bottomRight.setUV(uVRect.x + uVRect.z,uVRect.y);
	
	glyphs.push_back(newGlyph);
}

void SpriteBatch::createVertexArray()
{
	if(vao == 0)
		glGenVertexArrays(1,&vao);
	if(vbo == 0)
		glGenBuffers(1,&vbo);
	
	glBindVertexArray(vao);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
	// Position attrib pointer
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*)offsetof(Vertex,position));
	
	//Color attrib pointer
	glVertexAttribPointer(1,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof(Vertex),(void*) offsetof(Vertex,color));
	
	// UV attrib pointer
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,sizeof(Vertex),(void*) offsetof(Vertex,uv));
	
	glBindVertexArray(0);
	
}

void SpriteBatch::init()
{
	createVertexArray();
}

void SpriteBatch::begin(GlyphSortType sortType)
{
	renderBatches.clear();
	for (int i = 0; i < glyphs.size(); i++)
		delete glyphs[i];
	glyphs.clear();
	this->sortType = sortType;
}

void SpriteBatch::end()
{
	sortGlyphs();
	createRenderBatches();
}

void SpriteBatch::sortGlyphs()
{
	switch(sortType)
	{
		case GlyphSortType::BACK_FRONT:
			std::stable_sort(glyphs.begin(), glyphs.end(),compareBackFront);
			break;
		case GlyphSortType::FRONT_BACK:
			std::stable_sort(glyphs.begin(), glyphs.end(),compareFrontBack);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(glyphs.begin(), glyphs.end(), compareTexture);
			break;
	}
}

bool SpriteBatch::compareFrontBack(Glyph* a, Glyph* b)
{
	return a->depth < b->depth;
}
bool SpriteBatch::compareBackFront(Glyph* a, Glyph* b)
{
	return a->depth > b->depth;
}
bool SpriteBatch::compareTexture(Glyph* a, Glyph* b)
{
	return a->texture < b->texture;
}

void SpriteBatch::createRenderBatches()
{
	std::vector<Vertex> vertices;
	vertices.resize(glyphs.size()*6);
	if(glyphs.empty())
		return;
	int currentVertex = 0;
	int offset = 0;
	renderBatches.emplace_back(offset,6,glyphs[0]->texture);
	vertices[currentVertex++] = glyphs[0]->topLeft;
	vertices[currentVertex++] = glyphs[0]->bottomLeft;
	vertices[currentVertex++] = glyphs[0]->bottomRight;
	vertices[currentVertex++] = glyphs[0]->bottomRight;
	vertices[currentVertex++] = glyphs[0]->topRight;
	vertices[currentVertex++] = glyphs[0]->topLeft;
	offset += 6;
	
	for (int cg = 1; cg < glyphs.size(); cg++)
	{
		if(glyphs[cg]->texture != glyphs[cg-1]->texture)
			renderBatches.emplace_back(offset,6,glyphs[cg]->texture);
		else
			renderBatches.back().numVertices += 6;
		vertices[currentVertex++] = glyphs[cg]->topLeft;
		vertices[currentVertex++] = glyphs[cg]->bottomLeft;
		vertices[currentVertex++] = glyphs[cg]->bottomRight;
		vertices[currentVertex++] = glyphs[cg]->bottomRight;
		vertices[currentVertex++] = glyphs[cg]->topRight;
		vertices[currentVertex++] = glyphs[cg]->topLeft;
		offset += 6;
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);	
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	
}

void SpriteBatch::renderBatch()
{
	glBindVertexArray(vao);
	for (int i = 0; i < renderBatches.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, renderBatches[i].texture);
		glDrawArrays(GL_TRIANGLES,renderBatches[i].offset, renderBatches[i].numVertices);
	}
	glBindVertexArray(0);
}