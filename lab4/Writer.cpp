#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<Windows.h>
#include <conio.h>

int main(int argc, char* argv[])
{
	HANDLE exitR = OpenEvent(EVENT_ALL_ACCESS, FALSE, "reader");
	HANDLE mut = OpenMutex(SYNCHRONIZE, FALSE, "mutex");

	WaitForSingleObject(mut, INFINITE);
	std::cout << "Active: ";
	HANDLE events[2];
	char p[2];
	for (size_t i = 0; i < 2; i++)
	{
		_itoa(i + 1, p, 10);
		events[i] = CreateEvent(NULL, FALSE, FALSE, p);
		if (events[i] == NULL) {
			GetLastError();
		}
	}
	int k = atoi(argv[1]);
	char c;
	for (int i = 0; i < k * 2; i++) {
		std::cout << "Input message A or B\n";
		std::cin >> c;
		if (c == 'A') {
			SetEvent(events[0]);
			//Sleep(2);
			//ResetEvent(events[0]);
		}
		else {
			SetEvent(events[1]);
			//Sleep(2);
			//ResetEvent(events[1]);
		}
	}
	ReleaseMutex(mut);
	SetEvent(exitR);
}