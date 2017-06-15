#include <iostream>

#include "Game.h"
#include "Camera.h"
#include "Player.h"

void key(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

GLfloat sensitivity = 0.0005f;
double lastX, lastY;
GLfloat fov = glm::quarter_pi<GLfloat>();

void cursor(double xpos, double ypos) {
	GLfloat xoffset = (GLfloat)(xpos - lastX);
	GLfloat yoffset = (GLfloat)(lastY - ypos);
	lastX = xpos;
	lastY = ypos;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	camera.rotateTo(xoffset, yoffset);
}

void scroll(GLFWwindow *window, double xoffset, double yoffset) {
	if (fov < 0.02f) fov = 0.02f;
	else if (fov > glm::quarter_pi<GLfloat>()) fov = glm::quarter_pi<GLfloat>();
	else fov -= (GLfloat)yoffset / 50;
}

int main() {
	Game::init(800, 600, "My window", nullptr, nullptr,
		{
			{GLFW_CONTEXT_VERSION_MAJOR, 3},
			{GLFW_CONTEXT_VERSION_MINOR, 3},
			{GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE}
		},
		{ {GLFW_STICKY_KEYS, GL_TRUE}, {GLFW_CURSOR, GLFW_CURSOR_DISABLED} });
	Player a(0.5f, 0.5f, -0.25f, -.25f, 0);
	Player b(1, 1, -0.5f, -0.5f, 0);
	b.rotate(glm::half_pi<GLfloat>(), 1, 0, 0);
	camera.translate(0, 0, 3);
	Game::render.connect(a, &Player::render);
	Game::render.connect(b, &Player::render);
	Game::cursorMove += cursor;
	return Game::run();
}