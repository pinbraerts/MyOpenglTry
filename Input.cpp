#include "Game.h"
using namespace Game;

void Input::_cursorMoved(GLFWwindow* window, double xpos, double ypos) {
	Cursor::moved(xpos, ypos);
}

glm::vec2 Input::Cursor::getPos() {
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	return glm::vec2(x, y);
}

void Input::Cursor::setPos(double x, double y) {
	glfwSetCursorPos(window, x, y);
}

#include "Input.h"
using namespace Input;

GLenum getKey(GLenum key) {
	return glfwGetKey(window, key);
}

template<> class Hoverable<GameObject>;
