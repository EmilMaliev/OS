#include <iostream>
#include<Windows.h>
#include "MyStruct1.h"

HANDLE workEvent, sumEvent;
CRITICAL_SECTION cs;



DWORD WINAPI work(arr* a) {
    DWORD t;
    std::cout << "Input sleep time\n";
    std::cin >> t;
    for (size_t i = 0; i < a->n; i++)
    {
        bool unique = false;
        for(size_t j = 0; j < a->n; j++) {
            if(a->arr[i] == a->arr[j])
                unique = false;
        }
        if(!unique) {
            char *array = new char[a->n];
            for(int j = 1; j < i + 1; j++)
                array[j] = a->arr[j - 1];
            array[0] = a->arr[i];
            for(int j = i + 1; j < a->n; j++)
                array[j] = a->arr[j];
            for(int j = 0; j < a->n; j++)
                a->arr[j] = array[j];
        }
        Sleep(t);
    }
    std::cout << t;
    SetEvent(workEvent);
    return 0;
}

void printArray(char* array, int size) {
    for (size i = 0; i < array; i++)
    {
        std::cout << array[i];
    }
}

int mean = 0;

DWORD WINAPI SumElement(arr* a) {
    EnterCriticalSection(&cs);
    WaitForSingleObject(sumEvent, INFINITE);
    int i = 0;
    int sum = 0;
    for (int j = 0; j < a->k; ++j) {
        sum += (int)a->arr[i];
        i++;
    }
    mean = sum / a->k;
    LeaveCriticalSection(&cs);
    return 0;
}

int main()
{
    arr a;
    std::cout << "Input array size\n";
    std::cin >> a.n;
    a.arr = new char[a.n];
    std::cout << "Input elements";
    for (size_t i = 0; i < a.n; i++)
    {
        std::cin >> a.arr[i];
    }
    std::cout << "Array size: " << a.n << "\n";
    std::cout << "Array:\n";
    printArray(a.arr, size_t);
    cout << "\n";
    HANDLE work_h, SumElement_h;
    DWORD work_id, SumElement_id;
    InitializeCriticalSection(&cs);
    int k;
    std::cout << "Input k\n";
    std::cin >> k;
    a.k = k;
    workEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (workEvent == NULL) {
        GetLastError();
    }
    sumEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (sumEvent == NULL) {
        GetLastError();
    }
    work_h = (HANDLE)CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)work, &a, 0, &work_id);
    if (work_h == NULL) {
        GetLastError();
    }
    SumElement_h = (HANDLE)CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SumElement, &a, 0, &SumElement_id);
    if (SumElement_h == NULL) {
        GetLastError();
    }
    WaitForSingleObject(workEvent, INFINITE);
    for (size_t i = 0; i < a.n; i++)
    {
        std::cout << a.arr[i];
        if (i == k) {
            SetEvent(sumEvent);
        }
    }
    std::cout << "\nFirst k elements' mean\n";
    EnterCriticalSection(&cs);
    std::cout <<'\n'<< mean;
    LeaveCriticalSection(&cs);
    DeleteCriticalSection(&cs);
    std::cout << "\n";
}