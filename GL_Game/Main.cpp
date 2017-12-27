/*
	Main.cpp
	*******************************
	Main 
*/

/* Macros */
#define FAILED(X) (X == 0)

/* Incude header files */
#include <iostream>

/* OpenGL Headers */
#include <glad\glad.h>
#include <GLFW\glfw3.h>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"	vertexColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";

GLuint shaderProgram;

void load_shader() {

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	GLchar infoLog[512];
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "ERROR: VERTEX SHADER: COMPILATION FAILED\n" << infoLog << std::endl;
	}

	// fragment shader
	GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "ERROR: SHADER: FRAGMENT: COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Create shader program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check if successfully created shader program
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR: SHADER: PROGRAM: CREATE_FAILED\n" << infoLog << std::endl;
	}

	// Delete unused shader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Triangle
	GLfloat vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	GLuint indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	// 0. copy our vertices array in a buffer for OpenGL to use
	GLuint VBO;
	GLuint EBO;
	GLuint VAO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Generate a VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 1. then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	//glBindVertexArray(0);
}

/* Whenever the window size changed (by OS or user resize) this callback function executes */
void frame_buffer_size_callback(GLFWwindow * window, int w, int h) {
	glViewport(0, 0, w, h);
}

/* Input process function */
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void render_scene() {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	GLdouble time = glfwGetTime();
	GLfloat greenValue = (sin(time * 4.0) * 0.25f) + 0.5f;
	GLint vertexColor = glGetUniformLocation(shaderProgram, "ourColor");
	glUseProgram(shaderProgram);
	glUniform4f(vertexColor, 0.1f, greenValue, 0.1f, 1.0f);

	//glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int main(int argc, char * argv[]) {
	
	/* Initialize GLFW */
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // If it is on MAC X OS 

	/* Create the window */
	GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "GL_TEST", NULL, NULL);

	if (FAILED(window)) {
		/* End GLFW if failed */
		std::cerr << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return -1;
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

	load_shader();

	/* Start the render loop */
	while (!glfwWindowShouldClose(window))
	{
		/* Input */
		processInput(window);

		/* Render */
		render_scene();

		/* Check event and swap buffer */
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}