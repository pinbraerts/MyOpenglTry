#pragma once
#include "Camera.h"

class Player {
private:
	glm::mat4 transform;
	glm::mat4 rotation;
	GLuint texture;
	GLuint shaderProgram;
	GLfloat verticles[20];
	GLuint VAO, VBO;
	GLfloat height, width;

	void init();

public:

	GLfloat &x = transform[3].x,
		&y = transform[3].y,
		&z = transform[3].z,
		&sx = transform[0].x,
		&sy = transform[1].y,
		&sz = transform[2].z;

	Player(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	Player(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
	Player(GLfloat, GLfloat);

	Player& rotate(GLfloat, GLfloat, GLfloat, GLfloat);
	Player& scale(GLfloat, GLfloat, GLfloat = 1);
	Player& translate(GLfloat, GLfloat, GLfloat = 0);

	void load(const char[]);

	void render() {
		glBindTexture(GL_TEXTURE_2D, texture);
		glUseProgram(shaderProgram);
		GLuint matLoc = glGetUniformLocation(shaderProgram, "transform");
		glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(transform));
		matLoc = glGetUniformLocation(shaderProgram, "rotation");
		glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(rotation));
		matLoc = glGetUniformLocation(shaderProgram, "projection");
		glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(camera.projection()));
		matLoc = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(camera.view()));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}

	~Player();
};