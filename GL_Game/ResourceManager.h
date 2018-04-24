/* 
** ��Դ������ 
** һ����������̬���࣬��������Shader��Texture2D����Դ�ļ���
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

	// ���ļ��м���һ��Shader
	static Shader LoadShader(const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile, const std::string & name);

	// �������ֻ�ȡһ��Shader
	static Shader GetShader(const std::string& name);

	// ���ļ��м���һ��Texture2D��ͼ����
	static Texture2D LoadTexture(const GLchar * path, const std::string& name);

	// ���ļ��м���һ��Texture2D��ͼ����
	static Texture2D LoadTexture(Texture2D& tex, const std::string& name);

	// �������ֻ�ȡһ����ͼ
	static Texture2D GetTexture(const std::string& name);

	~ResourceManager();

private:
	static std::map<std::string, Shader>	_shaders;
	static std::map<std::string, Texture2D>	_textures;

	// �������ͽ�ֹʵ����
	ResourceManager() {}

};
#endif
