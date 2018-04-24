
glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 lightPos = glm::vec3(0.0f, 2.0f, 0.0f);

GLboolean first = GL_TRUE;
Vector2D mouseOldPos;

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
/*
float vertices[] = {
	// positions		// color		    // coord
	0.5f, -0.5f, 0.5f,   1.0f, 0.0f, 0.0f, 0.0f, 0.0f,   // bottom right
	-0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   // bottom left
	0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 0.5f, 1.0f,    // top 

	0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 0.5f, 1.0f,

	0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 0.5f, 1.0f,

	-0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
	0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f, 0.5f, 1.0f,

	0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
};
*/
/* Whenever the window size changed (by OS or user resize) this callback function executes */
void frame_buffer_size_callback(GLFWwindow * window, int w, int h) {
	glViewport(0, 0, w, h);
}



Game::~Game()
{
	delete this->mainShader;
	delete this->texture;
}

void Game::Start()
{
	init();
	load_shader();

	glEnable(GL_DEPTH_TEST);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	/* Start the render loop */
	while (!glfwWindowShouldClose(window))
	{
		double time = glfwGetTime();
		/* Input */
		this->process_input();

		/* Render */
		this->draw();

		/* Check event and swap buffer */
		glfwSwapBuffers(window);
		glfwPollEvents();

		/* 60 FPS */
		while (glfwGetTime() - time < 0.0167) {

		}
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------

	glfwTerminate();
}

void Game::init()
{
	this->camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	/* Create the window */
	this->window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, this->name.c_str(), NULL, NULL);

	if (FAILED(window)) {
		/* End GLFW if failed */
		std::cerr << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	if (FAILED(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))) {
		/* End GLAD if failed */
		std::cerr << "Failed to initialize GLAD!" << std::endl;
	}

	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

#ifdef DEBUG
	GLint nAtt;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nAtt);
	std::cout << "Max vertex attributes: " << nAtt << std::endl;
#endif // DEBUG

	
}

void Game::load_shader()
{
	mainShader = new Shader("shaders/vertexShader.vs", "shaders/fragShader.fs");
	texture = new Texture2D("textures/wall.jpg");
	// Rectangle

	// 0. copy our vertices array in a buffer for OpenGL to use
	GLuint VBO;
	glGenBuffers(1, &VBO);

	// Generate a VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// 1. then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	texture->apply();
	mainShader->apply();
}

void Game::draw()
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*
	** Change Color
	**
	GLdouble time = glfwGetTime();
	GLfloat greenValue = (sin(time * 4.0) * 0.25f) + 0.5f;
	GLint vertexColor = glGetUniformLocation(shaderProgram, "ourColor");
	glUseProgram(shaderProgram);
	glUniform4f(vertexColor, 0.1f, greenValue, 0.1f, 1.0f);
	*/
	mainShader->setVec3("lightPos", glm::vec3(0.0f, 2.0f, 1.0f));
	mainShader->setVec3("lightColor", glm::vec3(1.0f, 0.5f, 0.2f));
	mainShader->setVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));
	glBindVertexArray(VAO);
	glm::mat4 model;
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0));
	//model = glm::rotate(model, glm::radians(sqrt(angleX * angleX + angleY * angleY) * 0.5f ), glm::vec3(0.0f, 0.0f, 1.0f));
	GLuint modLoc = glGetUniformLocation(mainShader->ID, "model");
	glUniformMatrix4fv(modLoc, 1, GL_FALSE, glm::value_ptr(model));


	glm::mat4 view;
	// note that we're translating the scene in the reverse direction of where we want to move
	view = camera.GetViewMatrix();
	GLuint viewLoc = glGetUniformLocation(mainShader->ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(camera.Zoom), SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	GLuint projLoc = glGetUniformLocation(mainShader->ID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	texture->apply();
	mainShader->apply();

	glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Game::process_input()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);


	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.moveFront(0.05f);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.moveFront(-0.05f);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.moveLeft(0.05f);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.moveLeft(-0.05f);

	double x, y;
	glfwGetCursorPos(window, &x, &y);

	if (first) {
		mouseOldPos.set(x, y);
		first = GL_FALSE;
	}

	float x_off = x - mouseOldPos.X;
	float y_off = mouseOldPos.Y - y;

	mouseOldPos.set(x, y);

	camera.mouseLookAround(x_off, y_off);
}


