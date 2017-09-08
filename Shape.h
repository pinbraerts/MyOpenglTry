#pragma once
#include <iostream>

using Floating = float;

#ifndef ALLOW_ALL_OFFSETS
#define ALLOW_ALL_OFFSETS 0
#endif // !ALLOW_ALL_OFFSETS

#define COUNT_OFFSETS Floating nx = x - offsetX, ny = y - offsetY

struct Point {
	Floating x, y;

	Floating distance(Point other);
};

class Shape {
public:
	const enum Type {
		None,
		Rectangle_t,
		Sphere_t
	} type; // TODO: manage "partial" enum via namespaces and unsigned for custom

protected:
	Shape(Type type, Floating X = 0, Floating Y = 0, Floating OffsetX = 0, Floating OffsetY = 0);

public:
	Floating x, y, offsetX, offsetY; // TODO: add invalid value check

	virtual bool collides(const Shape& other) const;
	virtual bool contains(Point point) const = 0;
	virtual Point getNearestPoint(Point point) const = 0;
};

class Rectangle : public Shape {
#ifdef __GNUC__
private:
	using __super = Shape;
#endif
public:
	static constexpr Floating CENTER_OFFSET = -1; // or another negative or higher than size (height or width) value
	static constexpr Floating QUADRO_HEIGHT = 0; // or negative value
	Floating width, height; // TODO: add invalid value check

	friend std::ostream& operator<<(std::ostream& stream, const Rectangle& shape);

	Rectangle(Floating X = 0, Floating Y = 0, Floating Width = 1, Floating Height = QUADRO_HEIGHT, Floating OffsetX = CENTER_OFFSET, Floating OffsetY = CENTER_OFFSET);

protected:
	Rectangle(Type ShapeType, Floating X = 0, Floating Y = 0, Floating Width = 1, Floating Height = QUADRO_HEIGHT, Floating OffsetX = CENTER_OFFSET, Floating OffsetY = CENTER_OFFSET);

public:
	bool collides(const Shape& other) const override;
	bool contains(Point point) const override;
	Point getNearestPoint(Point point) const override;
};

class Oval : public Rectangle {
#ifdef __GNUC__
private:
	using __super = Rectangle;
#endif
protected:
	//using Rectangle::Rectangle;

public:
	Oval(Floating X = 0, Floating Y = 0, Floating Width = 1, Floating Height = QUADRO_HEIGHT, Floating OffsetX = CENTER_OFFSET, Floating OffsetY = CENTER_OFFSET);

	bool collides(const Shape& other) const override;
	bool contains(Point point) const override;
	Point getNearestPoint(Point point) const override;
};

