
#include<windows.h>
#include <iostream>
#include<time.h>
#include<random>

int main()
{
	char 	c;	// ��������� ������
	SECURITY_ATTRIBUTES sa;	// �������� ������
	SECURITY_DESCRIPTOR sd;	// ���������� ������
	HANDLE 	hNamedPipe;
	DWORD 	dwBytesRead;		// ��� ����� ����������� ����
	DWORD 	dwBytesWrite;		// ��� ����� ���������� ����
	int n;
	printf("Enter array dimension :\t");
	std::cin >> n;


	float* a = new float[n];
	printf("Array :\n");
	for (int i = 0; i < n; i++) {
		a[i] = rand() % 10 + 1;
		printf("%f\n", a[i]);
	}
	// ������������� ��������� ������
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = FALSE;	// ���������� ������ �������������
	// �������������� ���������� ������
	InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
	// ������������� �������� ������, �������� ������ ���� �������������
	SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);
	sa.lpSecurityDescriptor = &sd;
	// ������� ����������� ����� ��� ������
	hNamedPipe = CreateNamedPipeA(
		"\\\\.\\pipe\\demo_pipe",	// ��� ������
		PIPE_ACCESS_DUPLEX,		// ������ �� ������ � ����� � �����
		PIPE_TYPE_MESSAGE | PIPE_WAIT,	// ���������� �������� ���������
		1,		// ������������ ���������� ����������� ������ 
		0,		// ������ ��������� ������ �� ���������
		0,		// ������ �������� ������ �� ���������
		INFINITE,	// ������ ���� ����� 500 ��
		&sa		// ������ ��� ���� �������������
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


