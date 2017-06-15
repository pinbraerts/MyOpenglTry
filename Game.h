#pragma once
#include <map>
#include <string>

#include "includes.h"

namespace Game {
	static GLFWwindow* window;
	static Event<void> render;
	static Event<void, double, double> cursorMove;

	static void _cursorMove(GLFWwindow* window, double xpos, double ypos) {
		cursorMove(xpos, ypos);
	}

	static void init(unsigned height, unsigned width, const char* title, GLFWmonitor* monitor, GLFWwindow* share,
		std::map<size_t, size_t> hints = std::map<size_t, size_t>(), std::map<size_t, size_t> inputModes = std::map<size_t, size_t>(),
		GLfloat rclear = 0.2f, GLfloat gclear = 0.3f, GLfloat bclear = 0.3f, GLfloat aclear = 1) {
		glfwInit();

		for (auto pair : hints) glfwWindowHint(pair.first, pair.second);

		window = glfwCreateWindow(height, width, title, monitor, share);
		if (window == nullptr) {
			glfwTerminate();
			throw std::runtime_error("Failed to create GLFW window!");
		}
		glfwMakeContextCurrent(window);
		glfwSetCursorPosCallback(window, _cursorMove);

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
		glClearColor(rclear, gclear, bclear, aclear);
	}

	static int run() {
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
			glClear(GL_COLOR_BUFFER_BIT);
			render();
			glfwSwapBuffers(window);
		}
		glfwTerminate();
		return 0;
	}
};
