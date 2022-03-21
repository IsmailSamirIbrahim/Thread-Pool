ThreadPool
==========

A simple C++11 Thread Pool implementation.

Basic usage:
```c++

// simple function that adds multiplies two numbers and prints the result
void multiply(const int a, const int b) {
	const int res = a * b;
	std::cout << a << " * " << b << " = " << res << std::endl;
}

// same as before but now we have an output parameter
void multiply_output(int & out, const int a, const int b) {
	out = a * b;
	std::cout << a << " * " << b << " = " << out << std::endl;
}

// same as before but now we have an output parameter
int multiply_return(const int a, const int b) {
	const int res = a * b;
	std::cout << a << " * " << b << " = " << res << std::endl;
	return res;
}

int main()
{
	// create thread pool with 3 worker threads
	Thread_Pool pool{3};

	// submit (partial) multiplication table
	for (int i = 1; i < 3; ++i)
		for (int j = 1; j < 10; ++j)
			pool.submit(multiply, i, j);

	// submit function with output parameter passed by ref
	int output_ref;
	auto future1 = pool.submit(multiply_output, std::ref(output_ref), 5, 6);

	// wait for multiplication output to finish
	future1.get();
	std::cout << "Last operation result is equals to " << output_ref << std::endl;

	// submit function with return parameter 
	auto future2 = pool.submit(multiply_return, 5, 3);

	// wait for multiplication output to finish
	int res = future2.get();
	std::cout << "Last operation result is equals to " << res << std::endl;

	return 0;
}
```
