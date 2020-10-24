#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <mutex>
#include <vector>
#include <atomic>
#include "windows.h"

using namespace std;
using namespace std::chrono;

static const int NumThreads = 32;
static const int NumTasks = 4000 * 4000;

int A[NumTasks];

//int ind = 0;
//mutex _lock;

bool check() {
	for (int i = 0; i < NumTasks; i++)
		if (A[i] != 1)
			return false;
	return true;
}

//int next_ind() {
//	int index;
//	lock_guard<mutex> lock(_lock);
//	index = ind++;
//	return index;
//}

atomic<int> ind=0;
//mutex _lock1;
void addOne() {
	//lock_guard<mutex> lock(_lock1);
	while (ind < NumTasks) {
		A[ind++] += 1;
		Sleep(2*1e-3);
	}
}

//int main()
//{
//	auto startTime = high_resolution_clock::now();
//	thread t[NumThreads];
//	for (int i = 0; i < NumThreads; i++)
//	{
//		t[i] = thread(addOne);
//	}
//
//	for (int i = 0; i < NumThreads; i++)
//	{
//		t[i].join();
//	}
//
//	auto stopTime = high_resolution_clock::now();
//	auto elapsed = duration_cast<nanoseconds>(stopTime - startTime);
//	
//	check() ? cout << "Succeded!" : cout << "Failed";
//	cout << "Sec: " << elapsed.count() * 1e-9 << endl;
//
//
//	return 0;
//}