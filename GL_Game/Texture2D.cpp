#include "Texture2D.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void Init(Texture2D * obj, unsigned char * data, int width, int height) {
	// Genreating texture
	GLuint texture;
	glGenTextures(1, &texture);
	obj->ID = texture;
	glBindTexture(GL_TEXTURE_2D, obj->ID);

	// Set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Failed to load texture!" << std::endl;
	}
}

Texture2D::Texture2D(const GLchar * path)
{

	// Load and generate the texture
	int width, height, nrChannels;
	stbi_uc *data = stbi_load(path, &width, &height, &nrChannels, 0);
	
	Init(this, data, width, height);

	// Release the memory
	stbi_image_free(data);

#ifdef DEBUG
	std::cout << "Successfully load " << path << std::endl;
#endif
}

Texture2D::Texture2D(unsigned char * data, int width, int height)
{
	Init(this, data, width, height);
}
