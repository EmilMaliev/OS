#include "Queue.h"
Queue::~Queue() {
	delete[] queue;
	CloseHandle(hPopSemaphore);
	CloseHandle(hPushSemaphore);
}

void Queue::push(float c) {
	WaitForSingleObject(hPushSemaphore, INFINITE);
	ReleaseSemaphore(hPopSemaphore, 1, NULL);
	queue[realSize] = c;
	realSize++;
}

float Queue::pop() {
	WaitForSingleObject(hPopSemaphore, INFINITE);
	ReleaseSemaphore(hPushSemaphore, 1, NULL);
	float result = queue[0];
	realSize--;
	for (int i = 0; i < realSize; i++) {
		queue[i] = queue[i + 1];
	}
	return result;
}