#include "Utils.h"
Vector2D getCurrentMousePos(GLFWwindow * window) {
	double mX, mY;
	glfwGetCursorPos(window, &mX, &mY);
	Vector2D ret(mX, mY);
	return ret;
}