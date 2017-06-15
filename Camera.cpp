#include "Camera.h"

Camera::Camera() {}

void Camera::translate(GLfloat dx, GLfloat dy, GLfloat dz) {
	position += glm::vec3(dx, dy, dz);
	_view = glm::lookAt(position, position + direction, up);
}

void Camera::move(GLfloat dx, GLfloat dy) {
	position += dx * glm::cross(direction, up) + dy * direction;
	_view = glm::lookAt(position, position + direction, up);
}

void Camera::rotateTo(GLfloat yaw, GLfloat pitch) {
	if (pitch > glm::half_pi<GLfloat>()) pitch = glm::half_pi<GLfloat>();
	else if (pitch < -glm::half_pi<GLfloat>()) pitch = -glm::half_pi<GLfloat>();
	glm::vec3 right = glm::cross(direction, up);
	direction = glm::rotate(glm::mat4(), yaw, -up) * glm::rotate(glm::mat4(), pitch, right) * glm::vec4(direction, 1);
	up = glm::rotate(glm::mat4(), pitch, right) * glm::vec4(up, 1);
	_view = glm::lookAt(position, position + direction, up);
}

const glm::mat4& Camera::projection() {
	return _projection;
}

const glm::mat4& Camera::view() {
	return _view;
}