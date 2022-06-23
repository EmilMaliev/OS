
#include<windows.h>
#include <iostream>
#include<time.h>
#include<random>

int main()
{
	char 	c;	// служебный символ
	SECURITY_ATTRIBUTES sa;	// атрибуты защиты
	SECURITY_DESCRIPTOR sd;	// дескриптор защиты
	HANDLE 	hNamedPipe;
	DWORD 	dwBytesRead;		// для числа прочитанных байт
	DWORD 	dwBytesWrite;		// для числа записанных байт
	int n;
	printf("Enter array dimension :\t");
	std::cin >> n;


	float* a = new float[n];
	printf("Array :\n");
	for (int i = 0; i < n; i++) {
		a[i] = rand() % 10 + 1;
		printf("%f\n", a[i]);
	}
	// инициализация атрибутов защиты
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = FALSE;	// дескриптор канала ненаследуемый
	// инициализируем дескриптор защиты
	InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	// устанавливаем атрибуты защиты, разрешая доступ всем пользователям
	SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
	sa.lpSecurityDescriptor = &sd;
	// создаем именованный канал для чтения
	hNamedPipe = CreateNamedPipeA(
		"\\\\.\\pipe\\demo_pipe",	// имя канала
		PIPE_ACCESS_DUPLEX,		// читаем из канала и пишем в канал
		PIPE_TYPE_MESSAGE | PIPE_WAIT,	// синхронная передача сообщений
		1,		// максимальное количество экземпляров канала 
		0,		// размер выходного буфера по умолчанию
		0,		// размер входного буфера по умолчанию
		INFINITE,	// клиент ждет связь 500 мс
		&sa		// доступ для всех пользователей
	);

	if (hNamedPipe == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Creation of the named pipe failed." << std::endl
			<< "The last error code: " << GetLastError() << std::endl;
		std::cout << "Press any char to finish server: ";
		std::cin >> c;
		return 0;
	}

	std::cout << "The server is waiting for connection with a client." << std::endl;
	if (!ConnectNamedPipe(
		hNamedPipe,
		(LPOVERLAPPED)NULL
	))
	{
		std::cerr << "The connection failed." << std::endl
			<< "The last error code: " << GetLastError() << std::endl;
		CloseHandle(hNamedPipe);
		std::cout << "Press any char to finish the server: ";
		std::cin >> c;
		return 0;
	}

	//
	if (!WriteFile(
		hNamedPipe,
		&n,
		sizeof(int),
		&dwBytesWrite,
		(LPOVERLAPPED)NULL
	))
	{
		std::cerr << "Data writing to the named pipe failed." << std::endl
			<< "The last error code: " << GetLastError() << std::endl;
		CloseHandle(hNamedPipe);
		std::cout << "Press any char to finish the server: ";
		std::cin >> c;
		return (0);
	}
	if (!WriteFile(
		hNamedPipe,
		a,
		n * sizeof(float),
		&dwBytesWrite,
		(LPOVERLAPPED)NULL
	))
	{
		std::cerr << "Data writing to the named pipe failed." << std::endl
			<< "The last error code: " << GetLastError() << std::endl;
		CloseHandle(hNamedPipe);
		std::cout << "Press any char to finish the server: ";
		std::cin >> c;
		return (0);
	}
	float num;


	if (!ReadFile(
		hNamedPipe,
		&num,
		sizeof(float),
		&dwBytesRead,
		(LPOVERLAPPED)NULL
	))
	{
		std::cerr << "Data reading from the named pipe failed." << std::endl
			<< "The last error code: " << GetLastError() << endl;
		CloseHandle(hNamedPipe);
		std::cout << "Press any char to finish the server: ";
		std::cin >> c;
		return (0);
	}

	printf("Result\t%f :\n",num);
	
	CloseHandle(hNamedPipe);
	delete[] a;
	return 0;
}


