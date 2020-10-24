#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <mutex>
#include <vector>
#include <atomic>
#include "windows.h"
#include <queue>

using namespace std;
using namespace std::chrono;

static const int TaskNum = 4 * 1024 * 1024;
static const int ProducerNum = 4;
static const int ConsumerNum = 4;

int globalSum = 0;



class ThreadSafeDynamicQueue {
public:
	std::queue<uint8_t> data;
	std::mutex qmutex;

	void push(uint8_t val) {
		std::lock_guard<std::mutex> lock(qmutex);
		data.push(val);
	}
	bool pop(uint8_t& val) { 
		unique_lock<mutex> ulock(qmutex);
		if (data.empty()) {
			ulock.unlock();
			this_thread::sleep_for(milliseconds(1));
			unique_lock<mutex> ulock1(qmutex);
			if (data.empty()) {
				return false;
			}
		}
		val = data.front();
		data.pop();
		return true;
	}

};

static ThreadSafeDynamicQueue dynamicQueue;

void producer() {
	for (int i = 0; i < TaskNum; i++) {
		dynamicQueue.push(1);
	}
}

void consumer() {
	int localSum = 0;
	uint8_t zero = 0;
	for (int i = 0; i < TaskNum/ ConsumerNum; i++) {
		if (dynamicQueue.pop(zero) == true)
			localSum += 1;
	}
	globalSum += localSum;
}

bool check_sum() {
	return TaskNum == globalSum;
}

int main()
{
	thread consumers[ConsumerNum];
	thread producers[ProducerNum];

	for (int i = 0; i < ConsumerNum; i++)
	{
		consumers[i] = thread(consumer);
		producers[i] = thread(producer);
	}

	for (int i = 0; i < ConsumerNum; i++)
	{
		consumers[i].join();
		producers[i].join();
	}
	
	cout << "Sum: " << globalSum<<endl;
	check_sum() ? cout << "Succeded!" : cout << "Failed";

	return 0;
}
