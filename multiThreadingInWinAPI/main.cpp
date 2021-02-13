#include <iostream>;
#include <windows.h>;
using namespace std;


int res_sum=0;

DWORD WINAPI ThreadFunction(PVOID Parametr)
{
	int th_sum = 0; 
	int i, *kk;
	kk = (int *)Parametr;
	int lenght = *kk + 50;
	for (i = *kk; i < lenght; i++)
	{
		th_sum += i;
	}
	Sleep(1000);
	
	printf("thread result: %d \n", th_sum);
	
	res_sum += th_sum;
	return  th_sum;
}

int result = 0;

DWORD WINAPI findFibonacñiNumberOf(PVOID number) { 
	
	int *pointer = (int *) number;

	int buf_number = *pointer;

	if (buf_number == 0) {
		result = 0;
		return 0;
	}
	if (buf_number == 1) {
		result = 1;
		return 1;
	}
	
	int buf1 = buf_number - 1;
	int buf2 = buf_number - 2;
	result = findFibonacñiNumberOf(&buf1) + findFibonacñiNumberOf(&buf2); 
	return result;
}



unsigned __int64    convert(const FILETIME & ac_FileTime)
{
	ULARGE_INTEGER    lv_Large;

	lv_Large.LowPart = ac_FileTime.dwLowDateTime;
	lv_Large.HighPart = ac_FileTime.dwHighDateTime;

	return lv_Large.QuadPart;
}

void choosePriority(HANDLE& h) {
	int option;
	cout << "Set priority: " << endl;
	cout << "1 - TIME_CRITICAL" << endl;
	cout << "Another - NORMAL" << endl;
	cout << "input: ";
	cin >> option;
	if (option == 1) {
		SetThreadPriority(h, THREAD_PRIORITY_TIME_CRITICAL);
	}
	else {
		SetThreadPriority(h, THREAD_PRIORITY_NORMAL);
	}
	return;
}



int main()
{
	FILETIME userTime, coreTime, dummy;  

	int number = 0;						 
	while (true)
	{
		cout << "input number: ";
		cin >> number;					 

		if (number < 0) break;

		HANDLE handle;					

		
		handle = CreateThread(NULL, 0, findFibonacñiNumberOf, &number, CREATE_SUSPENDED, NULL); 

		
		choosePriority(handle);

		ResumeThread(handle);   

		WaitForSingleObject(handle, INFINITE); 

		GetThreadTimes(handle, &dummy, &dummy, &coreTime, &userTime);  
																	  
		CloseHandle(handle); 

		cout << "main result: \t" << result << endl; 

		
		cout << "time spended : " << (convert(userTime) + convert(coreTime)) * 0.0000001 << endl; 
		cout << endl;
	}
	
	system("pause");
	return 0;
}

