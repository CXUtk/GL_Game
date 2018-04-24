#include "Game.h"

GLboolean Keys[1024];

/* Whenever the window size changed (by OS or user resize) this callback function executes */
void frame_buffer_size_callback(GLFWwindow * window, int w, int h) {
	glViewport(0, 0, w, h);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

void thread(void * args)
{
	Game * game = (Game *)args;
	game->Perform();
}


Game::Game(const char * name, GLuint width, GLuint height)
{
	this->_width = width;
	this->_height = height;

	// 创建窗体
	this->_window = glfwCreateWindow(width, height, name, nullptr, nullptr);
	// 窗体打开失败就报错
	if (!this->_window) {
		fprintf(stderr, "%s\n", "Failed to create GLFW window!");
		glfwTerminate();
	}
	glfwMakeContextCurrent(this->_window);
}

void Game::Perform()
{
	if (this->_aiMap->Solve_Astar(this->_renderer)) {
		fprintf(stdout, "The Map is solvable! STEP: %d\n", this->_aiMap->GetStep());
	}
	else {
		fprintf(stdout, "%s\n", "ERROR: CANNOT SOLVE the MAP!");
	}
}

Game::~Game()
{
	delete _aiMap;
}

void Game::Start()
{
	Init();


	this->_gameState = GAME_ACTIVE;

	/* 开始游戏渲染循环 */
	while (!glfwWindowShouldClose(this->_window))
	{
		double time = glfwGetTime();
		// 处理外部设备输入
		this->ProcessInput();

		// 游戏逻辑更新函数
		this->Update();

		// 渲染函数 
		this->Render();

		// Check event and swap buffer
		glfwSwapBuffers(this->_window);
		glfwPollEvents();

		// 60 FPS
		while (glfwGetTime() - time < 0.0167);
	}

	// 可选: 释放所有资源，关闭程序

	glfwTerminate();
}



void Game::Init()
{
	srand((unsigned)time);
	glfwSetFramebufferSizeCallback(this->_window, frame_buffer_size_callback);
	// GLAD 启动失败就结束
	if (FAILED(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))) {
		fprintf(stderr, "%s\n", "Failed to initialize GLAD!");
	}

	//glfwSetKeyCallback(this->_window, key_callback);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGetError();

	LoadResources();

	// 创建地图
	_aiMap = new AIMap(100);
	_aiMap->GenerateMap(0.1f);
	_aiMap->SetTarget(90, 90);
	
	std::thread thread(thread, (void *)this);
	thread.detach();



	// DEBUG 模式显示一些额外的信息
#ifdef DEBUG

	GLint nAtt;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nAtt);
	fprintf(stdout, "Max vertex attributes: %d\n", nAtt);

#endif // DEBUG
}

void Game::LoadResources()
{
	// 加载Shader
	ResourceManager::LoadShader("shaders/vertexShader.vs", "shaders/fragShader.fs", nullptr, "test");

	// 加载材质
	ResourceManager::LoadTexture("textures/inv.png", "test1");
	unsigned char white_pixel[] = { 0xFF, 0xFF, 0xFF, 0xFF };
	ResourceManager::LoadTexture(Texture2D(white_pixel, 1, 1), "white");

	// 变换投影矩阵
	glm::mat4 projection = glm::ortho(0.0f, (float)_width, (float)_height, 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("test").apply();
	ResourceManager::GetShader("test").setInt("image", 0);
	ResourceManager::GetShader("test").setMat4("projection", projection);


	// Set render-specific controls
	_renderer = new SpriteRenderer(ResourceManager::GetShader("test"));
}

void Game::ProcessInput()
{
	if (glfwGetKey(this->_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(this->_window, true);

}

void Game::Update()
{
}

void Game::Render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//_renderer->DrawSprite(ResourceManager::GetTexture("test1"), glm::vec2(0, 0), glm::vec2(100, 100), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

	_aiMap->Draw(_renderer);
	
}



void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			Keys[key] = GL_FALSE;
	}
}

