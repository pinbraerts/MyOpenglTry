#include <iostream>
#include <string>
#include "../Event.h"

Event<> click;

struct S;

template<class T = S> struct Clickable {
	Clickable() {
		click += [this] { check(); };
	}

	virtual void onClick() = 0;

private:
	void check() {
		if(static_cast<T&>(*this).x > 3) onClick();
	}
};

struct S : Clickable<> {
	double x = 5;

	void onClick() override {
		std::cout << "ok" << std::endl;
	}
};

int main() {
	S s;
	click();
	s.x = -4;
	click();
	return 0;
}
