/*
	Shader.h
	********************
	Contains shader class represents a shader program object
*/
#ifndef _SHADER_H_
#define _SHADER_H_
#include <glad\glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	// The id of the shader program 
	GLuint ID;


	// Contructor that read shader from files
	Shader(const std::string & vertexPath, const std::string & fragmentPath);

	// Use & Activate the shader program
	void apply() { glUseProgram(this->ID); }

	// Utility uniform functions
	void setBool(const std::string & name, GLboolean value) const;
	void setInt(const std::string & name, GLint value) const;
	void setFloat(const std::string & name, GLfloat value) const;

private:
	void load_shader(const std::string & vShaderCode, const std::string & fShaderCode);
};
#endif // _SHADER_H_
