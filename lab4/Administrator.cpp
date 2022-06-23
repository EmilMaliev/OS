#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<Windows.h>
#include <conio.h>

int main()
{
    HANDLE eX[2];
    eX[0] = CreateEvent(NULL, FALSE, FALSE, "writer");
    eX[1] = CreateEvent(NULL, TRUE, FALSE, "reader");

    int k;
    int n, m;
    std::cout << "Input number of Writer processes\n";
    std::cin >> n;
    m = n * 2;
    std::cout << "Input number of massages\n";
    std::cin >> k;
    HANDLE sem = CreateSemaphore(NULL, 2, 2, "semaphore");
    HANDLE* proc = new HANDLE[n + m];

    HANDLE mut;
    DWORD* id = new DWORD[n + m];
    STARTUPINFO* st = new STARTUPINFO[n + m];
    PROCESS_INFORMATION* pi = new PROCESS_INFORMATION[n + m];
    char p[2];

    mut = CreateMutex(NULL, FALSE, "mutex");
    if (mut == NULL) {
        GetLastError();
    }
    char z[80];
    wsprintf(z, "Writer.exe %d", k);
    for (int i = 0; i < n; i++) {
        ZeroMemory(&st[i], sizeof(STARTUPINFO));
        st[i].cb = sizeof(STARTUPINFO);
        CreateProcess(NULL, z, NULL, NULL, FALSE,
            CREATE_NEW_CONSOLE, NULL, NULL, &st[i], &pi[i]);
    }

    char z1[80];
    wsprintf(z1, "Reader.exe %d", k);
    for (size_t i = n; i < n + m; i++)
    {
        ZeroMemory(&st[i], sizeof(STARTUPINFO));
        st[i].cb = sizeof(STARTUPINFO);
        CreateProcess(NULL, z1, NULL, NULL, FALSE,
            CREATE_NEW_CONSOLE, NULL, NULL, &st[i], &pi[i]);
    }
    DWORD ind;
    
    Sleep(100);
    for (int i = 0; i < n + m; i++) {
        ind = WaitForMultipleObjects(2, eX, FALSE, INFINITE);
        if (ind == 0) {
            std::cout << "Reader ended his work\n";
        }
        else {
            std::cout << "Writer ended his work\n";
        }
    }
    _getch();
    delete[]pi;
    delete[]st;
    delete[]id;
    delete[]proc;
}
