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

	// ��������
	this->_window = glfwCreateWindow(width, height, name, nullptr, nullptr);
	// �����ʧ�ܾͱ���
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

	/* ��ʼ��Ϸ��Ⱦѭ�� */
	while (!glfwWindowShouldClose(this->_window))
	{
		double time = glfwGetTime();
		// �����ⲿ�豸����
		this->ProcessInput();

		// ��Ϸ�߼����º���
		this->Update();

		// ��Ⱦ���� 
		this->Render();

		// Check event and swap buffer
		glfwSwapBuffers(this->_window);
		glfwPollEvents();

		// 60 FPS
		while (glfwGetTime() - time < 0.0167);
	}

	// ��ѡ: �ͷ�������Դ���رճ���

	glfwTerminate();
}



void Game::Init()
{
	srand((unsigned)time);
	glfwSetFramebufferSizeCallback(this->_window, frame_buffer_size_callback);
	// GLAD ����ʧ�ܾͽ���
	if (FAILED(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))) {
		fprintf(stderr, "%s\n", "Failed to initialize GLAD!");
	}

	//glfwSetKeyCallback(this->_window, key_callback);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGetError();

	LoadResources();

	// ������ͼ
	_aiMap = new AIMap(100);
	_aiMap->GenerateMap(0.1f);
	_aiMap->SetTarget(90, 90);
	
	std::thread thread(thread, (void *)this);
	thread.detach();



	// DEBUG ģʽ��ʾһЩ�������Ϣ
#ifdef DEBUG

	GLint nAtt;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nAtt);
	fprintf(stdout, "Max vertex attributes: %d\n", nAtt);

#endif // DEBUG
}

void Game::LoadResources()
{
	// ����Shader
	ResourceManager::LoadShader("shaders/vertexShader.vs", "shaders/fragShader.fs", nullptr, "test");

	// ���ز���
	ResourceManager::LoadTexture("textures/inv.png", "test1");
	unsigned char white_pixel[] = { 0xFF, 0xFF, 0xFF, 0xFF };
	ResourceManager::LoadTexture(Texture2D(white_pixel, 1, 1), "white");

	// �任ͶӰ����
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

