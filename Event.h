#pragma once
#include <vector>
#include <functional>

template<class... Args> class Event {
private:
	using Function = typename std::function<void(Args...)>;
	using Container = typename std::vector<Function>;
	using Iterator = typename Container::const_iterator;

	Container container;

public:
	void /* not Event& */ operator+=(Function f) {
		container.push_back(f);
		return *this;
	}

	Iterator connect(Function f) {
		container.push_back(f);
		return --container.end();
	}

	void /* not Event& */ operator-=(Iterator f) {
		container.erase(f);
		return *this;
	}

	void operator()(Args... args) {
		for (auto i : container) i(args...);
	}

	void clear() {
		container.clear();
	}
};
/*
template<> class Event<> {
private:
	using Function = typename std::function<void()>;
	using Container = std::vector<Function>;

	Container container;

public:
	Event& operator+=(Function f) {
		container.push_back(f);
		return *this;
	}

	void operator()() {
		for (auto i : container) i();
	}

	void clear() {
		container.clear();
	}
};
*/