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


int main()
{
	//setlocale(LC_ALL,"ru");

	/*DWORD idThread;
	int k1 = 1, k2 = 51;
	HANDLE h1, h2;*/
	
	//h1 = CreateThread(NULL, 0, ThreadFunction, &k1, CREATE_SUSPENDED, &idThread);
	//h2 = CreateThread(NULL, 0, ThreadFunction, &k2, CREATE_SUSPENDED, &idThread);
	//// Âûïîëíåíèå ïîòîêîâ
	//ResumeThread(h1);
	//ResumeThread(h2);
	
	/*WaitForSingleObject(h1, INFINITE);
	WaitForSingleObject(h2, INFINITE);*/

	int number = 0; 
	while (true)
	{
		cout << "input number: ";
		cin >> number;

		if (number < 0) break;

		HANDLE handle;		

		handle = CreateThread(NULL, 0, findFibonacñiNumberOf, &number, CREATE_SUSPENDED, NULL); 

		ResumeThread(handle);  

		WaitForSingleObject(handle, INFINITE); 

		cout << "main result: \t" << result << endl;
	}
	
	system("pause");

	return 0;
}

