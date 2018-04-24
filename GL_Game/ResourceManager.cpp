#include "ResourceManager.h"

// Instantiate static variables
std::map<std::string, Shader>			ResourceManager::_shaders;
std::map<std::string, Texture2D>		ResourceManager::_textures;

Shader ResourceManager::LoadShader(const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile, const std::string & name)
{
	_shaders[name] = Shader(vShaderFile, fShaderFile);
	return _shaders[name];
}

Shader ResourceManager::GetShader(const std::string & name)
{
	return _shaders[name];
}

Texture2D ResourceManager::LoadTexture(const GLchar * path, const std::string & name)
{
	_textures[name] = Texture2D(path);
	return _textures[name];
}

Texture2D ResourceManager::LoadTexture(Texture2D & tex, const std::string & name)
{
	_textures[name] = tex;
	return _textures[name];
}

Texture2D ResourceManager::GetTexture(const std::string & name)
{
	return _textures[name];
}

ResourceManager::~ResourceManager()
{
}
