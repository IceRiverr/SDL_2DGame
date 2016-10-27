
#include <stdio.h>
#include <Windows.h>
#include <windowsx.h>
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>
#include <conio.h>
#include <process.h>
#include <string>

const int MAX_THREADS = 3;
HANDLE g_Mutex;

void TestWait();
void TestMutex();
DWORD WINAPI Printer_Thread(LPVOID data);
DWORD WINAPI PrintMsg_Thread(LPVOID msg);

int main()
{
	g_Mutex = CreateMutex(NULL, false, NULL);
	TestMutex();
	return 0;
}

DWORD WINAPI Printer_Thread(LPVOID data)
{
	for (int i = 0;i < 50;++i)
	{
		printf("%d", data);
		Sleep(100);

	}
	return (DWORD)(data);
}

void TestWait()
{
	HANDLE thread_handle[MAX_THREADS];
	DWORD thread_id[MAX_THREADS];
	printf("Starting thread...\n");
	for (int i = 0; i < MAX_THREADS; ++i)
	{
		thread_handle[i] = CreateThread(NULL, 0, Printer_Thread, (LPVOID)(i + 1), 0, &thread_id[i]);
	}

	for (int i = 0; i < 20; ++i)
	{
		printf("4");
		Sleep(100);
	}

	printf("Wait for...\n");
	WaitForMultipleObjects(MAX_THREADS, &thread_handle[0], true, INFINITE);

	for (int i = 0; i < MAX_THREADS; ++i)
	{
		CloseHandle(thread_handle[i]);
	}

	printf("\nAll thread terminated...\n");
}

void TestMutex()
{
	HANDLE thread_handle[MAX_THREADS];
	DWORD thread_id[MAX_THREADS];

	for (int i = 0; i < MAX_THREADS; ++i)
	{
		thread_handle[i] = CreateThread(NULL, 0, PrintMsg_Thread, (LPVOID)(i + 1), 0, &thread_id[i]);
	}

	/*WaitForSingleObject(g_Mutex, INFINITE);
	for (int i = 0; i < 10; ++i)
	{
		printf("Hello Today %d\n",i);
		Sleep(500);
	}*/

	WaitForMultipleObjects(MAX_THREADS, &thread_handle[0], true, INFINITE);
	for (int i = 0; i < MAX_THREADS; ++i)
	{
		CloseHandle(thread_handle[i]);
	}

	printf("\nAll thread terminated...\n");
}

DWORD WINAPI PrintMsg_Thread(LPVOID msg)
{
	WaitForSingleObject(g_Mutex, INFINITE);
	
	for (int i = 0; i < 10; ++i)
	{
		printf("Good Day,%d-%d\n",(int)msg,i);
		Sleep(500);
	}
	return 0;
}