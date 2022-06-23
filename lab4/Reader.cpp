#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<Windows.h>
#include <conio.h>

int main(int argc, char* argv[])
{
	HANDLE exitW = OpenEvent(EVENT_ALL_ACCESS, FALSE, "reader");
	HANDLE sem = OpenSemaphore(SEMAPHORE_ALL_ACCESS, TRUE, "semaphore");

	if (sem == NULL) {
		GetLastError();
	}
	WaitForSingleObject(sem, INFINITE);
	std::cout << "Active: ";
	HANDLE events[2];
	char p[2];
	for (size_t i = 0; i < 2; i++)
	{
		_itoa(i + 1, p, 10);
		events[i] = (HANDLE)CreateEvent(NULL, TRUE, FALSE, p);
		if (events[i] == NULL) {
			GetLastError();
		}
	}
	int k = atoi(argv[1]);
	DWORD ind;
	for (int i = 0; i < k; i++)
	{


		ind = WaitForMultipleObjects(2, events, FALSE, INFINITE);

		if (ind == 0) {
			std::cout << "A";
		}
		else {
			std::cout << "B";
		}
		
	}
	ReleaseSemaphore(sem, 1, NULL);

	_getch();
	SetEvent(exitW);
}