#include <windows.h>
#include <iostream>
#include <process.h>
#include "MyStruct.h"






void worker(LPVOID object1) {
    mystruct* object = (mystruct*)object1;
    std::cout << "Odd elements:";
    for (int i = 0; i < object->size; i++) {
        if (object->array[i] % 2 == 1) {
            std::cout << std::endl;
            std::cout << object->array[i] ;
        }
    }
}

void PrintArray(short* array,int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand();
        std::cout << array[i] << "\n";
    }
}

int main() {
    HANDLE hThread;
    DWORD IDThread;
    UINT IDThread1;

    srand(time(NULL));
    mystruct object;
    
    std::cout << "Enter array size:" << "\n";
    std::cin >> object.size;
    std::cout << "\n";

    short* array = new short[object.size];
    std::cout << "Array:" << "\n";

    PrintArray(array, object.size);

    object.array = array;
    std::cout << "\n";

    int worker_suspend_time, worker_restart_time;
    std::cout << "Enter worker suspend time";
    std::cin >> worker_suspend_time;
    std::cout << "Enter worker resume time";
    std::cin >> worker_restart_time;

    hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)worker, &object, 0, &IDThread);

    if (hThread == NULL)
        return GetLastError();

    Sleep(worker_suspend_time);
    SuspendThread(hThread);
    Sleep(worker_restart_time);
    ResumeThread(hThread);
    WaitForSingleObject(hThread, INFINITE);
    TerminateThread(hThread, 0);
    CloseHandle(hThread);


    std::cout << "\n";
    std::cout << "_________________________________________________";
    std::cout << "\n";

    hThread = (HANDLE)
        _beginthreadex(NULL, 0, (_beginthreadex_proc_type)worker, &object, 0, &IDThread1);
    if (hThread == NULL)
        return GetLastError();
    WaitForSingleObject(hThread, INFINITE);
    TerminateThread(hThread, 0);
    CloseHandle(hThread);

    delete[]array;
    return 0;
}