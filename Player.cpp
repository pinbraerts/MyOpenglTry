#include <iostream>

#include "Player.h"

const GLchar* PlayerVSS = "#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec2 texCoord;\n"
"out vec2 TexCoord;\n"
"uniform mat4 rotation;\n"
"uniform mat4 transform;\n"
"uniform mat4 projection;\n"
"uniform mat4 view;\n"
"void main() {\n"
"	gl_Position = projection * view * transform * rotation * vec4(position, 1.0);\n"
"	TexCoord = vec2(texCoord.x, 1 - texCoord.y);\n"
"}";

const GLchar* PlayerFSS = "#version 330 core\n"
"in vec2 TexCoord;"
"out vec4 color;\n"
"uniform sampler2D mTexture;\n"
"void main() {\n"
"	color = texture(mTexture, TexCoord);\n"
"}";

Player::Player(GLfloat h, GLfloat w, GLfloat X, GLfloat Y, GLfloat Z, GLfloat Sx, GLfloat Sy, GLfloat Sz) : height(h), width(w), verticles{
	0, h, 0, 0, 1,
	0, 0, 0, 0, 0,
	w, h, 0, 1, 1,
	w, 0, 0, 1, 0
} {
	transform = glm::scale(transform, glm::vec3(Sx, Sy, Sz));
	transform = glm::translate(transform, glm::vec3(X, Y, Z));
	init();
}

Player::Player(GLfloat h, GLfloat w, GLfloat X, GLfloat Y, GLfloat Z) : height(h), width(w), verticles{
	0, h, 0, 0, 1,
	0, 0, 0, 0, 0,
	w, h, 0, 1, 1,
	w, 0, 0, 1, 0
} {
	transform = glm::translate(transform, glm::vec3(X, Y, Z));
	init();
}

Player::Player(GLfloat h, GLfloat w) : height(h), width(w), verticles{
	0, h, 0, 0, 1,
	0, 0, 0, 0, 0,
	w, h, 0, 1, 1,
	w, 0, 0, 1, 0
} {
	init();
}

Player& Player::rotate(GLfloat angle, GLfloat X, GLfloat Y, GLfloat Z) {
	rotation = glm::rotate(rotation, angle, glm::vec3(X, Y, Z));
	return *this;
}

Player & Player::scale(GLfloat X, GLfloat Y, GLfloat Z) {
	sx += X;
	sy += Y;
	sz += Z;
	return *this;
}

Player& Player::translate(GLfloat X, GLfloat Y, GLfloat Z) {
	x += X;
	y += Y;
	z += Z;
	return *this;
}

void Player::init() {
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

	shaderProgram = compileShaderProgram(1, &PlayerVSS, 1, &PlayerFSS);
	load("A_hint.png");
}

void Player::load(const char imageFile[]) {
	int width, height;
	unsigned char* image = SOIL_load_image(imageFile, &width, &height, nullptr, SOIL_LOAD_RGBA);
	if (image == nullptr) {
		std::stringstream ss("Failed to load image from ");
		ss << imageFile << " file!";
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

Player::~Player() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);
	glDeleteTextures(1, &texture);
}
