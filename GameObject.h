#pragma once
#include "Game.h"
#include "Shape.h"
#include <type_traits>

class Game::GameObject {
private:
	Rectangle* shape;

public:

	template<class T, class... Args> typename std::enable_if<std::is_base_of<Rectangle, T>::value>::type setShape(Args&&... args) {
		delete shape;
		shape = new T(std::forward<Args>(args)...);
	}

	const Rectangle& getShape() { return *shape; }

	GameObject();
	// template<class T, class... Args> GameObject(Args&&... args) : shape(new T(std::forward<Args>(args)...)) {}

	~GameObject();
};

class Game::ImageRenderer {
private:
	GLuint texture, VAO, VBO, shaderProgram;
	std::string imagePath;

	void load();
	void init();

public:
	ImageRenderer(std::string fileName);

	void reload(std::string fileName);

	void render();
};
