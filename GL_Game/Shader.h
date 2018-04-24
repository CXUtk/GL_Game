/*
	Shader.h
	********************
	Contains shader class represents a shader program object
*/
#ifndef _SHADER_H_
#define _SHADER_H_
#include <glad\glad.h>

#include <cstdio>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>

class Shader {
public:
	// The id of the shader program 
	GLuint ID;

	Shader(){}

	// Contructor that read shader from files
	Shader(const GLchar * vertexPath, const GLchar * fragmentPath);

	// Use & Activate the shader program
	void apply() { glUseProgram(this->ID); }

	// Utility uniform functions
	void setBool(const std::string & name, GLboolean value) const;
	void setInt(const std::string & name, GLint value) const;
	void setFloat(const std::string & name, GLfloat value) const;
	void setVec3(const std::string & name, glm::vec3 value) const;
	void setMat4(const std::string & name, glm::mat4 mat) const;

private:
	void load_shader(const GLchar * vShaderCode, const GLchar * fShaderCode);
};
#endif // _SHADER_H_
