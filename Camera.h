#pragma once
#include "Game.h"

static class Camera {
private:
	glm::vec3 position;
	glm::vec3 direction = glm::vec3(0, 0, -1);
	glm::vec3 up = glm::vec3(0, 1, 0);
	glm::mat4 _projection = glm::perspective(glm::quarter_pi<GLfloat>(), (GLfloat)800 / 600, 0.1f, 100.0f);
	glm::mat4 _view = glm::lookAt(position, position + direction, up);

public:

	Camera();

	const glm::mat4& projection();
	const glm::mat4& view();

	void translate(GLfloat, GLfloat, GLfloat);

	void move(GLfloat, GLfloat);

	void rotateTo(GLfloat, GLfloat);
} camera;
