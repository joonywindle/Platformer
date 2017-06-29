#include "GLSLProg.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

GLSLProg::GLSLProg() : progID(0),vertID(0),fragID(0),numAttribs(0)
{
}

GLSLProg::~GLSLProg()
{
}

void GLSLProg::compileShaders(const std::string &vertPath, const std::string &fragPath)
{
	progID = glCreateProgram();
	vertID = glCreateShader(GL_VERTEX_SHADER);
	if(vertID == 0){
		std::cout << "Failed to create vertex shader" << std::endl;
		exit(EXIT_FAILURE);
    }
	
	fragID = glCreateShader(GL_FRAGMENT_SHADER);
	if(fragID == 0){
		std::cout << "Failed to create fragment shader" << std::endl;
		exit(EXIT_FAILURE);
    }
	
	compileShader(vertPath,vertID);
	compileShader(fragPath,fragID);
//	
	
}

void GLSLProg::linkShaders()
{
	glAttachShader(progID,vertID);
	glAttachShader(progID,fragID);
	
	glLinkProgram(progID);
	
	GLint success = 0;
	glGetProgramiv(progID, GL_LINK_STATUS, &success);
	if(success == GL_FALSE)
	{
		GLint maxLength = 0;
		
		glGetProgramiv(progID,GL_INFO_LOG_LENGTH,&maxLength);
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(progID,maxLength,&maxLength,&errorLog[0]);
		
		glDeleteProgram(progID);
		
		glDeleteShader(vertID);
		glDeleteShader(fragID);
		
		std::printf("%s\n",&(errorLog[0]));
		
		std::cout << "Shaders failed to link" << std::endl;
		exit(EXIT_FAILURE);
		
	}
	glDetachShader(progID,vertID);
	glDetachShader(progID,fragID);
}

void GLSLProg::compileShader(std::string filePath, GLuint ids)
{
	
	//std::ifstream shaderFile(filePath);
//	if(shaderFile.fail())
//	{
//		std::cout << "Could not open shader file" << filePath << std::endl;
//	}
//	
//	
//	std::string line;
//	std::string fileContents = "";
//	while(std::getline(shaderFile,line))
//	{
//		fileContents += line + "\n";
//	}
//	
//	shaderFile.close();

	std::ifstream shaderFile;
	
	shaderFile.exceptions(std::ifstream::badbit);
	std::string fileContents;
		shaderFile.open(filePath);
		std::stringstream filestream;
		filestream << shaderFile.rdbuf();
		shaderFile.close();
		fileContents = filestream.str();
		
	
	const GLchar* contentPointer = fileContents.c_str(); 
	
	glShaderSource(ids,1,&contentPointer, nullptr);
	
	glCompileShader(ids);
	
	GLint success = 0;
	glGetShaderiv(ids, GL_COMPILE_STATUS, &success);
	
	if(success == GL_FALSE)
	{
		GLint maxLength = 0;
		
		glGetShaderiv(ids,GL_INFO_LOG_LENGTH,&maxLength);
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(ids,maxLength,&maxLength,&errorLog[0]);
		glDeleteShader(ids);
//		
		std::printf("%s\n",&(errorLog[0]));
//		
		std::cout << "Shader failed to compile " << filePath << std::endl;
		exit(EXIT_FAILURE);
//		
	}	
}

void GLSLProg::addAttribute(const std::string& attName)
{
	glBindAttribLocation(progID,numAttribs,attName.c_str());
	numAttribs++;
}

void GLSLProg::use()
{
	glUseProgram(progID);
	for(int i = 0; i < numAttribs; i++)
		glEnableVertexAttribArray(i);
}

void GLSLProg::unuse()
{
	glUseProgram(0);
	for(int i = 0; i < numAttribs; i++)
		glDisableVertexAttribArray(i);
}

GLint GLSLProg::getUniformLocation(const std::string& uniformName)
{
	GLint location = glGetUniformLocation(progID,uniformName.c_str());
	if (location == GL_INVALID_INDEX)
	{
		std::cout << "Uniform name not found: " << uniformName << std::endl;
		exit(EXIT_FAILURE);
	}
	return location;
}