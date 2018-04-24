#ifndef __GL_GAME_H__
#define __GL_GAME_H__

/* Include 输入输出流头文件 */
#include <cstdio>
#include <thread>

/* OpenGL 头文件 */
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* Include 其他头文件 */
#include "Shader.h"
#include "Texture2D.h" 
#include "Vector2D.h"
#include "Utils.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "LifeMap.h"
#include "AIMap.h"



// 代表游戏状态的枚举常量
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN,
	GAME_LOSE
};

class Game
{
public:

	// 构造，析构函数
	Game(const char * name, GLuint width, GLuint height);
	void Perform();
	~Game();
	void Start();

private:

	// 游戏状态
	GLboolean			_keys[1024];
	GameState			_gameState;
	GLuint				_width, _height;
	GLFWwindow *		_window;
	SpriteRenderer *	_renderer;
	AIMap *				_aiMap;

	// 游戏初始化函数，加载游戏资源
	void Init();
	void LoadResources();

	// 游戏循环
	void ProcessInput();
	void Update();
	void Render();

};

#endif // !__GL_GAME__

