#pragma once

#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <memory>

#include <vector>

#include <pool/Queue.h>

namespace pool
{
	class Thread_Pool
	{
	public:
		Thread_Pool(std::size_t num_of_threads);
		~Thread_Pool();
		Thread_Pool(const Thread_Pool &) = delete;
		Thread_Pool(Thread_Pool &&) = delete;

		Thread_Pool & operator=(const Thread_Pool &) = delete;
		Thread_Pool & operator=(Thread_Pool &&) = delete;

		template<typename F, typename...Args>
		auto submit(F&& f, Args&&...args)->std::future<decltype(f(args...))>;

	private:
		void start(std::size_t num_of_threads);
		void stop();
	private:
		using Task = std::function<void()>;

		pool::Queue<Task> _tasks;
		std::vector<std::thread> _threads;
		std::mutex _mutex;
		std::condition_variable _cond;
		bool _shutdown;
	};

	void Thread_Pool::start(std::size_t num_of_threads)
	{
		for(size_t i = 0; i < num_of_threads; ++i)
			_threads.emplace_back([=]()
		{
			while (true)
			{
				Task task;
				{
					std::unique_lock<std::mutex> locker(_mutex);
					_cond.wait(locker, [=]() {return _shutdown || !_tasks.empty(); });

					if (_shutdown == true && _tasks.empty())
						break;

					task = std::move(_tasks.front());
					_tasks.pop();
				}

				task();
			}
		});
	}

	void Thread_Pool::stop()
	{
		{
			std::unique_lock<std::mutex> locker(_mutex);
			_shutdown = true;
		}
		_cond.notify_all();

		for (auto& thread : _threads)
			thread.join();
	}

	Thread_Pool::Thread_Pool(std::size_t num_of_threads)
	{
		start(num_of_threads);
	}

	Thread_Pool::~Thread_Pool()
	{
		stop();
	}

	template<typename F, typename...Args>
	auto Thread_Pool::submit(F&& f, Args&&... args) -> std::future<decltype(f(args...))>
	{
		// Create a function with bounded parameters ready to execute
		std::function<decltype(f(args...))()> func = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
		// Encapsulate it into a shared ptr in order to be able to copy construct / assign 
		auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);

		// Wrap packaged task into void function
		std::function<void()> wrapper_func = [task_ptr]() {
			(*task_ptr)();
		};

		// Enqueue generic wrapper function
		_tasks.push(wrapper_func);

		// Wake up one thread if its waiting
		_cond.notify_one();

		// Return future from promise
		return task_ptr->get_future();
	}
}