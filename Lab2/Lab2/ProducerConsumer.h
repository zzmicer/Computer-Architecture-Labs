#pragma once
//// Push ones into queue
//template <class T>
//void producer(T& queue,int TaskNum, int ConsumerNum) {
//	for (int i = 0; i < TaskNum / ConsumerNum; i++) {
//		queue.push(1);
//	}
//}
//// Pop ones from queue, and add to global sum
//template <class T>
//int consumer(T& queue, int TaskNum, int ConsumerNum, int globalSum) {
//	int localSum = 0;
//	uint8_t elem;
//	for (int i = 0; i < TaskNum / ConsumerNum; i++) {
//		if (queue.pop(elem) == true)
//			localSum += elem;
//	}
//	return localSum;
//}