/*
	Main.cpp
	*******************************
	Main 
*/

/* Macros */
#define FAILED(X) (X == 0)

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif // !STB_IMAGE_IMPLEMENTATION


/* Incude header files */
#include <iostream>

/* OpenGL Headers */
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* Include Utils Headers */
#include "Shader.h"
#include "Texture2D.h"


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


Shader * ourShader;
Texture2D * texture;
GLuint VAO;

void load_shader() {

	
	ourShader = new Shader("shaders/vertexShader.vs", "shaders/fragShader.fs");
	texture = new Texture2D("textures/wall.jpg");
	// Rectangle
	float vertices[] = {
		// positions          // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};
	GLuint indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	// 0. copy our vertices array in a buffer for OpenGL to use
	GLuint VBO;
	GLuint EBO;
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	texture->apply();
	ourShader->apply();
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

	/*
	** Change Color 
	**
	GLdouble time = glfwGetTime();
	GLfloat greenValue = (sin(time * 4.0) * 0.25f) + 0.5f;
	GLint vertexColor = glGetUniformLocation(shaderProgram, "ourColor");
	glUseProgram(shaderProgram);
	glUniform4f(vertexColor, 0.1f, greenValue, 0.1f, 1.0f);
	*/
	glBindVertexArray(VAO);
	static float angle = 0.0f;
	angle += 0.1f;
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
	trans = glm::rotate(trans, glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));
	GLuint transLoc = glGetUniformLocation(ourShader->ID, "transform");
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));






	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	trans = glm::mat4();
	trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
	trans = glm::rotate(trans, glm::radians(-angle), glm::vec3(0.0, 0.0, 1.0));
	transLoc = glGetUniformLocation(ourShader->ID, "transform");
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(trans));
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

	delete ourShader;
	delete texture;

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------

	glfwTerminate();
	return 0;
}