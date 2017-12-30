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
#include "Vector2D.h"
#include "Utils.h"


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


Shader * ourShader;
Texture2D * texture;
GLuint VAO;
GLboolean isMouseDown;
Vector2D mouseOldPos;
float angleX = -89.0f;
float angleY = 0.0f;
float oldAngleX = 0.0f;
float oldAngleY = 0.0f;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);


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


void load_shader() {

	
	ourShader = new Shader("shaders/vertexShader.vs", "shaders/fragShader.fs");
	texture = new Texture2D("textures/wall.jpg");
	// Rectangle

	GLuint indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	// 0. copy our vertices array in a buffer for OpenGL to use
	GLuint VBO;
	glGenBuffers(1, &VBO);

	// Generate a VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


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
	float cameraSpeed = 0.05f;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

	if (isMouseDown) {

		Vector2D vec = getCurrentMousePos(window) - mouseOldPos;
		double mX, mY;
		glfwGetCursorPos(window, &mX, &mY);
		mouseOldPos.set(mX, mY);
		angleX += (float)vec.X;
		angleY += (float)-vec.Y;

		if (angleY > 89.0f)
			angleY = 89.0f;
		if (angleY < -89.0f)
			angleY = -89.0f;

		glm::vec3 front;
		front.x = cos(glm::radians(angleX)) * cos(glm::radians(angleY));
		front.y = sin(glm::radians(angleY));
		front.z = sin(glm::radians(angleX)) * cos(glm::radians(angleY));
		cameraFront = glm::normalize(front);
	}
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
		isMouseDown = GL_TRUE;
		double mX, mY;
		glfwGetCursorPos(window, &mX, &mY);
		mouseOldPos.set(mX, mY);

	}
	if (action == GLFW_RELEASE) {
		isMouseDown = GL_FALSE;
		double mX, mY;
		glfwGetCursorPos(window, &mX, &mY);
		mouseOldPos.set(mX, mY);
	}
}

void render_scene() {
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
	glBindVertexArray(VAO);
	glm::mat4 model;
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0));
	//model = glm::rotate(model, glm::radians(sqrt(angleX * angleX + angleY * angleY) * 0.5f ), glm::vec3(0.0f, 0.0f, 1.0f));
	GLuint modLoc = glGetUniformLocation(ourShader->ID, "model");
	glUniformMatrix4fv(modLoc, 1, GL_FALSE, glm::value_ptr(model));
	

	glm::mat4 view;
	// note that we're translating the scene in the reverse direction of where we want to move
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	GLuint viewLoc = glGetUniformLocation(ourShader->ID, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	GLuint projLoc = glGetUniformLocation(ourShader->ID, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


	glDrawArrays(GL_TRIANGLES, 0, 18);
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

	glEnable(GL_DEPTH_TEST);

	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	/* Start the render loop */
	while (!glfwWindowShouldClose(window))
	{
		double time = glfwGetTime();
		/* Input */
		processInput(window);

		/* Render */
		render_scene();

		/* Check event and swap buffer */
		glfwSwapBuffers(window);
		glfwPollEvents();

		while (glfwGetTime() - time < 0.0167) {

		}
	}

	delete ourShader;
	delete texture;

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------

	glfwTerminate();
	return 0;
}