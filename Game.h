#pragma once
#include <map>
#include <string>

#include "includes.h"

namespace Game {
	static GLFWwindow* window;
	static Event<> render;

	namespace Input {
		namespace Cursor {
			static Event<double, double> moved;
			static glm::vec2 getPos();
			static void setPos(double, double);
		};

		static void _cursorMoved(GLFWwindow* window, double xpos, double ypos) {
			Cursor::moved(xpos, ypos);
		}
	}

	class GameObject;
	class ImageRenderer;

	static void init(unsigned height, unsigned width, const char* title,
		GLFWmonitor* monitor, GLFWwindow* share,
		std::map<size_t, size_t> hints = std::map<size_t, size_t>(),
		std::map<size_t, size_t> inputModes = std::map<size_t, size_t>(),
		glm::vec4 clearColor = glm::vec4(0.5f, 0.5f, 0.5f, 1));

	static int run();
};
