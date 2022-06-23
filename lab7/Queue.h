#pragma once
#include<windows.h>
#include<iostream>
class Queue
{
	float* queue;
	int realSize;
	int maxSize;
	HANDLE hPushSemaphore;
	HANDLE hPopSemaphore;

public:

	Queue(int size) : realSize(0), maxSize(size) {
		hPushSemaphore = CreateSemaphore(NULL, maxSize, maxSize, NULL);
		hPopSemaphore = CreateSemaphore(NULL, 0, maxSize, NULL);
		queue = new float[size];
	}

	~Queue();
	void push(float c);
	float pop();
};