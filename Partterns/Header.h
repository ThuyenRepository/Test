#pragma once
template <class T>
class MyClass
{
public:
	MyClass();
	~MyClass();
	void init();
private:

};

template<class T>
inline MyClass<T>::MyClass()
{
}

template<class T>
inline MyClass<T>::~MyClass()
{
}

template<class T>
inline void MyClass<T>::init()
{
}
class TestExtern
{
public:
	TestExtern();
	~TestExtern();
	void update(int i);

private:

};
