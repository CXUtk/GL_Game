/*
	Texture2D.h
	********************
	Contains shader class represents a 2D Texture
*/

#ifndef _TEXTURE_2D_H_
#define _TEXTURE_2D_H_



#include <glad\glad.h>
#include <string>
#include <iostream>

class Texture2D {
public:
	GLuint ID;

	Texture2D(){}

	// 从路径名加载材质
	Texture2D(const GLchar * path);

	// 从像素矩阵加载材质
	Texture2D(unsigned char * data, int width, int height);

	// Apply the texture
	void apply(){ glBindTexture(GL_TEXTURE_2D, this->ID); }
};

#endif