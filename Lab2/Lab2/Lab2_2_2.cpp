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

static const int TaskNum = 4 * 1024*1024;
static const int ProducerNum = 4;
static const int ConsumerNum = 4;
static const int QueueSize = 16;


int globalSum = 0;


class ThreadSafeFixedSizeQueue {
public:

	void push(uint8_t val) {

		unique_lock<std::mutex> ul(qmutex);

		cv1.wait(ul, [this] {return !isFull(); });
		data.push(val);
		ul.unlock();
		cv2.notify_one();
	}

	bool pop(uint8_t& val) {

		unique_lock<mutex> ul(qmutex);

		cv2.wait(ul,[this] {return !data.empty(); });
		val = data.front();
		data.pop();
		ul.unlock();
		cv1.notify_one();
		return true;
	}
	bool isFull() {
		return data.size() >=QueueSize;
	}
private:
	std::queue<uint8_t> data;
	std::mutex qmutex;
	condition_variable cv1;
	condition_variable cv2;

};

static ThreadSafeFixedSizeQueue staticQueue;

void producer() {
	for (int i = 0; i < TaskNum/ ConsumerNum; i++) {
		staticQueue.push(1);
	}
}

void consumer() {
	int localSum = 0;
	uint8_t elem;
	for (int i = 0; i < TaskNum / ConsumerNum; i++) {
		if (staticQueue.pop(elem) == true)
			localSum += elem;
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
		producers[i] = thread(producer);
		consumers[i] = thread(consumer);

	}

	for (int i = 0; i < ConsumerNum; i++)
	{
		producers[i].join();
		consumers[i].join();

	}

	cout << "Sum: " << globalSum << endl;
	check_sum() ? cout << "Succeded!" : cout << "Failed";

	return 0;
}
