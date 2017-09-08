#include "Shape.h"
#include <math.h>
#include <string>

Shape::Shape(Type ShapeType, Floating X, Floating Y, Floating OffsetX, Floating OffsetY) : type(ShapeType), x(X), y(Y), offsetX(OffsetX), offsetY(OffsetY) {}

bool Shape::collides(const Shape& other) const {
	static bool was = false;
	if (was) throw (std::string)"Collition between " + typeid(*this).name() + " and " + typeid(other).name() + " is not implemented!";
	was = true;
	bool res = other.collides(*this);
	was = false;
	return res;
}

Rectangle::Rectangle(Floating X, Floating Y, Floating Width, Floating Height, Floating OffsetX, Floating OffsetY) :
	width(Width > 0 ? Width : throw "Width is <= 0!"), height(Height > 0 ? Height : Width /* Quadro */), Shape(Rectangle_t, X, Y) {
#if !ALLOW_ALL_OFFSETS
	if (OffsetX < 0 || OffsetX > width) offsetX = width / 2;
	if (OffsetY < 0 || OffsetY > height) offsetY = height / 2;
#endif
}

Rectangle::Rectangle(Type ShapeType, Floating X, Floating Y, Floating Width, Floating Height, Floating OffsetX, Floating OffsetY) :
	width(Width > 0 ? Width : throw "Width is <= 0!"), height(Height > 0 ? Height : Width /* Quadro */), Shape(ShapeType, X, Y) {
#if !ALLOW_ALL_OFFSETS
	if (OffsetX < 0 || OffsetX > width) offsetX = width / 2;
	if (OffsetY < 0 || OffsetY > height) offsetY = height / 2;
#endif
}

bool Rectangle::contains(Point point) const {
	COUNT_OFFSETS;
	return point.x >= nx && point.x <= nx + width && point.y >= ny && point.y <= ny + height;
}

Point Rectangle::getNearestPoint(Point point) const {
	COUNT_OFFSETS;
	Floating left = nx + height, up = ny + width;
	return { point.x <= nx ? nx : point.x < left ? point.x : left, point.y <= ny ? ny : point.y < up ? point.y : up };
}

bool Rectangle::collides(const Shape& other) const {
	switch (other.type) {
	case Rectangle_t: {
		const Rectangle& oth = dynamic_cast<const Rectangle&>(other);
		COUNT_OFFSETS;
		Floating onx = oth.x - oth.offsetX, ony = oth.y - oth.offsetY;
		return onx <= nx + width && onx + oth.width >= nx && ony <= ny + height && ony + oth.height >= ny;
	}
	default:
		return __super::collides(other);
	}
}

bool Oval::contains(Point point) const {
	COUNT_OFFSETS;
	return pow(point.x - nx, 2) + pow((point.y - ny) * (width / height), 2) <= width * width / 4;
}

Point Oval::getNearestPoint(Point point) const {
	COUNT_OFFSETS;
	Floating scale = width / height, ox = point.x - nx, oy = (point.y - ny) * scale, rad = width / 2;
	if (ox * ox + oy * oy <= rad * rad) return point;
	Floating a = atan2(oy, ox);
	return { cos(a) * rad, sin(a) * rad / scale };
}

Oval::Oval(Floating X, Floating Y, Floating Width, Floating Height, Floating OffsetX, Floating OffsetY) : Rectangle(Sphere_t, X, Y, Width, Height, OffsetX, OffsetY) {}

bool Oval::collides(const Shape& other) const {
	COUNT_OFFSETS;
	return contains(other.getNearestPoint({ nx, ny }));
}

Floating Point::distance(Point other) {
	return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
}

std::ostream& operator<<(std::ostream& stream, const Rectangle& shape) {
	stream << "Shape { x: " << shape.x << ", y: " << shape.y << ", offsetX: " << shape.offsetX << ", offsetY: " << shape.offsetY << " }";
	switch (shape.type) {
	case Shape::Rectangle_t:
		stream << ", Rectangle { width: " << shape.width << ", height: " << shape.height << " }";
		break;
	case Shape::Sphere_t:
		stream << ", Sphere { width: " << shape.width << ", height: " << shape.height << " }";
		break;
	}
	return stream;
}
