#include "GameObject.h"

using namespace Game;

GameObject::GameObject() : shape(new Rectangle()) {}

GameObject::~GameObject() {
	delete shape;
}

void Game::ImageRenderer::load() {
	int width, height;
	unsigned char* image = SOIL_load_image(imagePath.c_str(), &width, &height, nullptr, SOIL_LOAD_RGBA);
	if (image == nullptr) {
		std::stringstream ss("Failed to load image from ");
		ss << imagePath << " file!";
		throw std::runtime_error(ss.str());
	}
	glGenTextures(1, &texture);
	if (texture == 0) {
		SOIL_free_image_data(image);
		throw std::runtime_error("Failed to generate texture!");
	}
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
}

void Game::ImageRenderer::init() {
	glGenVertexArrays(1, &VAO);
	if (VAO == 0) throw std::runtime_error("Failed to generate vertex array object!");
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	if (VBO == 0) throw std::runtime_error("Failed to generate vertex buffer object!");
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	shaderProgram = compileShaderProgram(1, &VSS, 1, &FSS);
}

Game::ImageRenderer::ImageRenderer(std::string fileName) : imagePath(fileName) {
	load();
}

void Game::ImageRenderer::reload(std::string fileName) {

}

void Game::ImageRenderer::render() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glDeleteTextures(1, &texture);
}
