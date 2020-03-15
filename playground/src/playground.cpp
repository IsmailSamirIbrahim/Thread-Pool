#include <iostream>
#include <pool/Queue.h>

using namespace std;
using namespace pool;

int
main(int argc, char** argv)
{
	Queue<int> q{};

	for (size_t i = 0; i < 100; ++i)
		q.push(int(i));

	cout << "Size = " << q.size() << endl;
	return 0;
}
