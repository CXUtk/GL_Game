#include "Texture2D.h"
Texture2D::Texture2D(const GLchar * path)
{
	// Genreating texture
	GLuint texture;
	glGenTextures(1, &texture);
	this->ID = texture;
	glBindTexture(GL_TEXTURE_2D, this->ID);

	// Set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load and generate the texture
	int width, height, nrChannels;
	stbi_uc *data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cerr << "Failed to load texture!" << std::endl;
	}
	
	// Release the memory
	stbi_image_free(data);

#ifdef DEBUG
	std::cout << "Successfully load " << path << std::endl;
#endif
}