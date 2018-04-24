/*
	Main.cpp
	*******************************
	Main 
*/


/* OpenGL Headers */
#include "Game.h"


int main(int argc, char * argv[]) {
	
	/* Initialize GLFW */
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // If it is on MAC X OS 

	Game game("GL_GAME", 1280, 960);
	game.Start();
	
	return 0;
}