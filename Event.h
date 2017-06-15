#pragma once
#include <vector>

template<class Ret, class... Args> using Function = Ret(*)(Args...);

template<class Ret, class... Args> class Callable {
public:
	virtual Ret operator()(Args...) = 0;
};

template<class T, class Ret, class... Args> class ThisCall : public Callable<Ret, Args...> {
private:
	using Ftype = Ret(T::*)(Args...);

	T& self;
	Ftype _method;

public:
	ThisCall(T& Self, Ftype method) : self(Self), _method(method) {}

	virtual Ret operator()(Args... args) {
		return (self.*_method)(args...);
	}
};

template<class Ret, class... Args> class NormalCall : public Callable<Ret, Args...> {
private:
	using Ftype = Function<Ret, Args...>;
	Ftype _function;

public:
	NormalCall(Ftype function) : _function(function) {}

	virtual Ret operator()(Args... args) {
		return _function(args...);
	}
};

template<class Ret, class... Args> Callable<Ret, Args...>* newCallable(Ret(*f)(Args...)) {
	return new NormalCall<Ret, Args...>(f);
}

template<class T, class Ret, class... Args> Callable<Ret, Args...>* newCallable(T& self, Ret(T::*f)(Args...)) {
	return new ThisCall<T, Ret, Args...>(self, f);
}

template<class Ret, class... Args> class Event {
private:
	using Ftype = Function<Ret, Args...>;
	std::vector<Callable<Ret, Args...>*> listeners;
	bool noSetRet = true;

public:
	Ret standart;

	~Event() {
		for (auto i : listeners) delete i;
		listeners.clear();
	}

	Ret operator()(Args... args) const {
		auto mEnd = listeners.end(), i = listeners.begin();
		--mEnd;
		for (; i < mEnd; ++i) i->operator()(args...);
		return listeners.empty() ? standart : noSetRet ? i->operator()(args...), standart : i->operator()(args...);
	}

	Event& operator+=(Ftype listener) {
		noSetRet = false;
		listeners.push_back(newCallable(listener));
		return *this;
	}

	template<class Ret2> Event& operator+=(Function<Ret2, Args...> listener) {
		noSetRet = true;
		listeners.push_back(newCallable((Ftype)listener));
		return *this;
	}

	template<class T> Event& connect(T& self, Ret(T::*method)(Args...)) {
		noSetRet = true;
		listeners.push_back(newCallable(self, method));
		return *this;
	}

	template<class T, class Ret2> Event& connect(T& self, Ret2(T::*method)(Args...)) {
		noSetRet = false;
		listeners.push_back(newCallable(self, (Ret(T::*)(Args...))method));
		return *this;
	}

	const Ftype& operator[](size_t index) {
		return listeners[index];
	}
};

template<class... Args> class Event<void, Args...> {
private:
	using Ftype = Function<void, Args...>;
	std::vector<Callable<void, Args...>*> listeners;

public:
	void operator()(Args... args) const {
		for (auto i: listeners) i->operator()(args...);
	}

	~Event() {
		for (auto i : listeners) delete i;
		listeners.clear();
	}

	template<class Ret2> Event& operator+=(Function<Ret2, Args...> listener) {
		listeners.push_back(newCallable((Ftype)listener));
		return *this;
	}

	template<class T, class Ret2> Event& connect(T& self, Ret2(T::*method)(Args...)) {
		listeners.push_back(newCallable(self, (void(T::*)(Args...))method));
		return *this;
	}

	const Ftype& operator[](size_t index) {
		return listeners[index];
	}
};
