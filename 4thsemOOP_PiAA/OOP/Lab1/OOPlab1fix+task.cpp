
#include "pch.h"
#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <memory>
#include <iostream>
template<typename T>
class Array
{
public:
	// (default) constructor
	Array(const size_t size = 0)
		: m_size(size)
		, m_array(m_size ? new T[m_size]() : nullptr)
	{
		std::cout << "default constructor" << std::endl;
	}
	Array(const Array &obj) :
		m_size(obj.m_size),
		m_array(m_size ? new T[m_size]() : nullptr)
	{
		std::cout << "copy constructor" << std::endl;
		std::copy(obj.m_array.get(), obj.m_array.get() + obj.m_size, m_array.get());
	}
	Array(Array&& object) noexcept
		: Array()
	{
		std::cout << "move constructor"<<std::endl;
		std::swap(m_size, object.m_size);
		std::swap(m_array, object.m_array);
	}

	Array& operator=(const Array& object)         // оператор присваивания c копированием
	{
		Array temp_array(object);
		std::cout << "copy assignment"<<std::endl;
		std::swap(m_size, temp_array.m_size);
		std::swap(m_array, temp_array.m_array);

		return *this;
	}

	Array& operator=(Array&& object) noexcept //оператор присваивания с перемещением 
	{
		std::cout << "move assignment"<<std::endl;
		std::swap(m_size, object.m_size);
		std::swap(m_array, object.m_array);
		return (*this);
	}

	~Array() {
		m_array.reset();
	}


	const size_t size() const
	{
		return m_size;
	}

	T& operator [](const size_t index)
	{
		assert(index < m_size);

		return m_array[index];
	}

private:
	size_t m_size;
	std::unique_ptr<T[]> m_array;

};
int main()
{
	Array<int> a;
	Array<int> b(5);
	Array<int> c = 42;
	Array<int> d = a;
	Array<int> e = Array<int>(8);
	Array<int> f = std::move(c);
	Array<int> g(Array<int>(8));
	Array<int> h(std::move(g));
	std::cout <<" ----------" << std::endl;
	a = b;
	a = std::move(d);
	g = Array<int>(116);

	return 0;
}