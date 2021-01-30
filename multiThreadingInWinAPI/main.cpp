#include <iostream>;
#include <windows.h>;
//#include <stdio.h>

using namespace std;


int res_sum=0;

int result = 0; // глобальная переменная для получения данных из порожденного потока

DWORD WINAPI ThreadFunction(PVOID Parametr)
{
	int th_sum = 0; // результат произведения
	int i, *kk;
	kk = (int *)Parametr;
	int lenght = *kk + 50;
	for (i = *kk; i < lenght; i++)
	{
		th_sum += i;
	}
	Sleep(1000);
	//cout << "thread result: " << th_sum << endl;
	printf("thread result: %d \n", th_sum);
	//Parametr = &proizv;
	res_sum += th_sum;
	return  th_sum;
}

DWORD WINAPI findFibonacсiNumberOf(PVOID number) {  //функция вычисления числа Фибоначчи
	
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
	result = findFibonacсiNumberOf(&buf1) + findFibonacсiNumberOf(&buf2); //рекурсия
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
	//// Выполнение потоков
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

		HANDLE handle;		// объявляем дескриптор будущего объекта т.е. потока

		handle = CreateThread(NULL, 0, findFibonacсiNumberOf, &number, CREATE_SUSPENDED, NULL); // создаем поток

		//первые два параметра по умолчанию: дескриптор не наследуем, размер стека как у порождающего потока
		//далее передаем указатель на функцию, которая будет выполняться в потоке
		//4-й параметр: наши исходные вводимые данные, они передаются в функцию
		//5-й - создаем и приостанавливаем поток
		//6-й - идентификатор потока не указываем

		ResumeThread(handle);  //запускаем приостановленный поток

		WaitForSingleObject(handle, INFINITE); // ждем пока поток отработает, после этого получаем результат

		cout << "main result: \t" << result << endl;
	}
	
	system("pause");

	return 0;
}

