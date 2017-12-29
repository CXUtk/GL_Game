/*
	Texture2D.h
	********************
	Contains shader class represents a 2D Texture
*/

#ifndef _TEXTURE_2D_H_
#define _TEXTURE_2D_H_

#include "stb_image.h"

#include <glad\glad.h>
#include <string>
#include <iostream>

class Texture2D {
public:
	GLuint ID;

	Texture2D(const GLchar * path);

	// Apply the texture
	void apply(){ glBindTexture(GL_TEXTURE_2D, this->ID); }
};

#endif