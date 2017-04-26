/*
	Christopher Peterson
	3/27/17
	Multithreading assignment
*/

#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

using namespace std;

void threadFunction(int threadNumber, shared_ptr<string> sharedResource, shared_ptr<mutex> mutexLock);

int main()
{
	// Make shared pointers to avoid using global variables
	shared_ptr<mutex> myMutex(new mutex());
	shared_ptr<string> sharedString(new string(""));
	// Vector to hold shared pointers to threads
	vector<shared_ptr<thread>> threads;

	// Use for loop to create threads
	for (int i = 0; i < 10; ++i)
	{
		// Create shared pointer to a new thread and add it to the vector
		shared_ptr<thread> newThread(new thread(threadFunction, i, sharedString, myMutex));
		threads.push_back(newThread);
	}

	// Loop through the vector and join each thread
	for (vector<shared_ptr<thread>>::const_iterator it = threads.begin(); it != threads.end(); ++it)
	{
		(*it)->join();
	}

	// Output the shared string at the end
	cout << *sharedString << endl;

	system("pause");
	return 0;
}

void threadFunction(int threadNumber, shared_ptr<string> sharedResource, shared_ptr<mutex> mutexLock)
{
	// Lock the mutex
	mutexLock->lock();

	// Append the required information to the shared resource string
	sharedResource->append("Thread #");
	sharedResource->append(to_string(threadNumber));
	sharedResource->append("\n");

	// Unlock the mutex
	mutexLock->unlock();
}
