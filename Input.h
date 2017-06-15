#pragma once
#include "Game.h"

namespace Input {
	GLenum getKey(GLenum key) {
		return glfwGetKey(Game::window, key);
	}

	struct {
		operator glm::vec2() {
			double xpos, ypos;
			glfwGetCursorPos(Game::window, &xpos, &ypos);
			return glm::vec2(xpos, ypos);
		}

		glm::vec2 operator=(glm::vec2 newpos) {
			glfwSetCursorPos(Game::window, newpos.x, newpos.y);
			return newpos;
		}
	} cursor;
};
