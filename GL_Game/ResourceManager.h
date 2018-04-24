/* 
** 资源管理器 
** 一个单例（静态）类，管理所有Shader和Texture2D等资源的加载
*/

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <cstdio>
#include <cstring>
#include <string>

#include <glad\glad.h>

#include "Shader.h"
#include "Texture2D.h"

class ResourceManager
{
public:

	// 从文件中加载一个Shader
	static Shader LoadShader(const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile, const std::string & name);

	// 根据名字获取一个Shader
	static Shader GetShader(const std::string& name);

	// 从文件中加载一个Texture2D贴图对象
	static Texture2D LoadTexture(const GLchar * path, const std::string& name);

	// 从文件中加载一个Texture2D贴图对象
	static Texture2D LoadTexture(Texture2D& tex, const std::string& name);

	// 根据名字获取一个贴图
	static Texture2D GetTexture(const std::string& name);

	~ResourceManager();

private:
	static std::map<std::string, Shader>	_shaders;
	static std::map<std::string, Texture2D>	_textures;

	// 单例类型禁止实例化
	ResourceManager() {}

};
#endif
