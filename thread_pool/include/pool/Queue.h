#pragma once
#include <assert.h>
#include <mutex>

namespace pool
{

	template<typename T>
	class Queue
	{
	public:
		Queue() = default;
		Queue(const Queue<T>& other) = default;
		Queue(Queue<T>&& other) = default;
		Queue<T>& operator=(const Queue<T>& other) = default;
		Queue<T>& operator=(Queue<T>&& other) = default;
		~Queue() = default;

		T& front();

		size_t size();

		bool empty();
		void clear();

		void push(const T& val);
		void pop();

	private:
		std::mutex _mutex;
		constexpr static size_t MAX_CAPACITY = 1024;
		T _data[MAX_CAPACITY];
		size_t _size = 0;
		int _front = -1;
		int _rear = -1;
	};

	template<typename T>
	T& Queue<T>::front()
	{
		std::lock_guard<std::mutex> locker(_mutex);
		assert(!this->empty() && "Queue is empty");
		return this->_data[this->_front];
	}

	template<typename T>
	size_t Queue<T>::size()
	{
		std::lock_guard<std::mutex> locker(_mutex);
		return this->_size;
	}

	template<typename T>
	bool Queue<T>::empty()
	{
		std::lock_guard<std::mutex> locker(_mutex);
		return _size == 0;
	}

	template<typename T>
	void Queue<T>::clear()
	{
		std::lock_guard<std::mutex> locker(_mutex);
		this->_front = -1;
		this->_rear = -1;
	}

	template<typename T>
	void Queue<T>::push(const T& val)
	{
		std::lock_guard<std::mutex> locker(_mutex);
		assert((_rear + 1) % MAX_CAPACITY != _front && "Queue is full");
		if (_rear == -1)
			_front = _rear = 0;
		else
			_rear = (_rear + 1) % MAX_CAPACITY;

		this->_data[_rear] = val;
		++_size;
	}

	template<typename T>
	void Queue<T>::pop()
	{
		std::lock_guard<std::mutex> locker(_mutex);
		assert(!this->empty() && "Queue is empty");
		if (_front == _rear)
			_front = _rear = -1;
		else
			_front = (_front + 1) % MAX_CAPACITY;

		--_size;
	}
}