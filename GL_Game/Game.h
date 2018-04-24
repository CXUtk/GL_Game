#ifndef __GL_GAME_H__
#define __GL_GAME_H__

/* Include ���������ͷ�ļ� */
#include <cstdio>
#include <thread>

/* OpenGL ͷ�ļ� */
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* Include ����ͷ�ļ� */
#include "Shader.h"
#include "Texture2D.h" 
#include "Vector2D.h"
#include "Utils.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "LifeMap.h"
#include "AIMap.h"



// ������Ϸ״̬��ö�ٳ���
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN,
	GAME_LOSE
};

class Game
{
public:

	// ���죬��������
	Game(const char * name, GLuint width, GLuint height);
	void Perform();
	~Game();
	void Start();

private:

	// ��Ϸ״̬
	GLboolean			_keys[1024];
	GameState			_gameState;
	GLuint				_width, _height;
	GLFWwindow *		_window;
	SpriteRenderer *	_renderer;
	AIMap *				_aiMap;

	// ��Ϸ��ʼ��������������Ϸ��Դ
	void Init();
	void LoadResources();

	// ��Ϸѭ��
	void ProcessInput();
	void Update();
	void Render();

};

#endif // !__GL_GAME__

