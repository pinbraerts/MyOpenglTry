#pragma once
#include <sstream>
#include <iostream>

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <SOIL\SOIL.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include "Event.h"

static GLuint compileShaderProgram(size_t vn, const char** vertexShaderSource, size_t fn, const char** fragmentShaderSource) {

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShader == 0) throw std::runtime_error("Failed to generate vertex shader!");
	glShaderSource(vertexShader, vn, vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), nullptr, infoLog);
		std::stringstream ss("Failed to compile vertex shader \"");
		ss << vertexShaderSource[0] << "\" (" << infoLog << ")!";
		std::cout << ss.str();
		throw std::runtime_error(ss.str());
	}

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShader == 0) throw std::runtime_error("Failed to generate fragment shader!");
	glShaderSource(fragmentShader, fn, fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, sizeof(infoLog), nullptr, infoLog);
		std::stringstream ss("Failed to compile fragment shader \"");
		ss << fragmentShaderSource[0] << "\" (" << infoLog << ")!";
		throw std::runtime_error(ss.str());
	}

	GLuint shaderProgram = glCreateProgram();
	if (shaderProgram == 0) throw std::runtime_error("Failed to generate shader program!");
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, sizeof(infoLog), nullptr, infoLog);
		std::stringstream ss("Failed to link shader program (");
		ss << infoLog << ")!";
		throw std::runtime_error(ss.str());
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}

static void loadTextures(GLuint dest[], size_t n, const char* files) {
	const char **f = &files;
	glGenTextures(n, dest);
	for (size_t i = 0; i < n; ++i) {
		int width, height;
		unsigned char* image = SOIL_load_image(*f, &width, &height, nullptr, SOIL_LOAD_RGB);
		if (image == nullptr) {
			std::cerr << "Failed to load image from " << *f << " file!" << std::endl;
			continue;
		}
		if (dest[i] == 0) {
			std::cerr << "Failed to generate texture!" << std::endl;
			SOIL_free_image_data(image);
			continue;
		}
		glBindTexture(GL_TEXTURE_2D, dest[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
