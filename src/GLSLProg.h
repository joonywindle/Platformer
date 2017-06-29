#ifndef GLSLPROG_H
#define GLSLPROG_H

#include <string>
#include <GL/glew.h>

class GLSLProg
{
public:
	GLSLProg();
	~GLSLProg();
	
	void compileShaders(const std::string &vertPath, const std::string &fragPath);
	
	void linkShaders();
	
	void addAttribute(const std::string& attName);
	GLint getUniformLocation(const std::string& uniformName);
	
	void use();
	void unuse();

private:
	GLuint progID;
	GLuint vertID;
	GLuint fragID;
	int numAttribs;
	
	void compileShader(std::string filePath, GLuint id);
	

};

#endif // GLSLPROG_H
