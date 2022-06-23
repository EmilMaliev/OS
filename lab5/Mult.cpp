
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<Windows.h>
#include<conio.h>
#include <set>

int main(int argc, char* argv[])
{
    HANDLE end = CreateEvent(NULL, FALSE, FALSE, "end");
    HANDLE write = (HANDLE)atoi(argv[1]);
    HANDLE read = (HANDLE)atoi(argv[2]);
    HANDLE event = OpenEvent(SYNCHRONIZE, FALSE, "1");
    if (event == NULL) {
        GetLastError();
    }

    WaitForSingleObject(event, INFINITE);
    float* a = new float[atoi(argv[3])];
    int n = atoi(argv[3]);

    for (int i = 0; i < atoi(argv[3]); i++) {
        DWORD s;
        ReadFile(read, &a[i], sizeof(a[i]), &s, NULL);
    }
    for (int i = 0; i < atoi(argv[3]); i++) {
        std::cout << a[i]<<" ";
    }
    std::cout << '\n';
    float num = 1;
    for (int i = 0; i < atoi(argv[3]); i++) {
        num *= a[i];
    }
    DWORD sz;
    std::cout << num;
    WriteFile(write, &num, sizeof(num), &sz, NULL);

    SetEvent(end);
    _getch();


}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
