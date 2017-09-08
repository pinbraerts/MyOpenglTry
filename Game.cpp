#include "Game.h"

void Game::init(unsigned height, unsigned width, const char * title,
	GLFWmonitor * monitor, GLFWwindow * share, std::map<size_t, size_t> hints,
	std::map<size_t, size_t> inputModes, glm::vec4 clearColor) {
	glfwInit();

	for (auto pair : hints) glfwWindowHint(pair.first, pair.second);

	window = glfwCreateWindow(height, width, title, monitor, share);
	if (window == nullptr) {
		glfwTerminate();
		throw std::runtime_error("Failed to create GLFW window!");
	}
	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, Input::_cursorMoved);

	glewExperimental = true;
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		glfwTerminate();
		std::stringstream msg("Failed to initialize GLEW ");
		msg << glewGetErrorString(err) << "!";
		throw std::runtime_error(msg.str());
	}

	for (auto pair : inputModes) glfwSetInputMode(window, pair.first, pair.second);

	int nwidth, nheight;
	glfwGetFramebufferSize(window, &nwidth, &nheight);
	glViewport(0, 0, nwidth, nheight);
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
}

int Game::run() {
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);
		render();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}
