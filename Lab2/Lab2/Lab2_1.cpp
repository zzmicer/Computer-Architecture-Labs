//#include <iostream>
//#include <thread>
//#include <chrono>
//#include <algorithm>
//#include <mutex>
//#include <vector>
//#include <atomic>
//#include <array>
//#include "windows.h"
//
//using namespace std;
//using namespace std::chrono;
//
//static const int NumThreads = 32;
//static const int NumTasks = 4000 * 4000;
//
//std::array<int, NumTasks> A;
//
//int m_ind = 0;
//atomic<int> a_ind{ 0 };
//
//mutex _lock;
//// Thread safe incrementing counter
//int incMutex() {
//	int index;
//	lock_guard<mutex> lock(_lock);
//	index = m_ind++;
//	return index;
//}
///**
// * Thread safe filling array A with ones via mutex or atomic counter.
// *
// * @param type_atomic If 1 use atomic counter, else mutex.
// */
//void addOne(bool type_atomic) {
//	int local_ind = 0;
//	try {
//		while (true) {
//			type_atomic ? local_ind = a_ind++ : local_ind = incMutex();
//			if (local_ind >= NumTasks) // break before we go beyond array
//				break;
//			A.at(local_ind)++;
//		}
//	}
//	catch (...) {
//		std::cerr << "Error!" << '\n';
//	}
//}
//
//bool check() {
//	for (int i = 0; i < NumTasks; i++)
//		if (A.at(i) != 1)
//			return false;
//	return true;
//}
//
//int main()
//{
//	for (int i = 0; i < NumTasks; i++)
//		A.at(i) = 0;
//	
//	auto startTime = high_resolution_clock::now();
//	thread t[NumThreads];
//	for (int i = 0; i < NumThreads; i++)
//	{
//		t[i] = thread(addOne,1);
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