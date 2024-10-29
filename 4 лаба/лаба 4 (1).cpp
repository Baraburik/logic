#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdint>
#include <cstdlib>
#include "FirstFunc.h"
#include "SecondFunc.h"


int main()
{
	setlocale(LC_ALL, "RUS");

	printf("Выберите задание: \n");
	printf("1 - Алгоритм поиска вводимого с клавиатуры значения\n");
	printf("2 - Функция подсчёта числа вхождений заданного элемента в дерево\n");
	printf("3 - Исключение добавления одинаковых символов\n");
	printf("4 - Выход\n");
	printf("Введите номер выбранного задания: ");

	int choise;
	scanf("%d", &choise);
	printf("\n");

	if (choise == 4)
	{
		printf("До свидания!\n");
		return 0;
	}

	switch (choise)
	{
	case 1:
		start();
		printf("\nЖелаете выполнить поиск числа?\n1 - да, 0 - нет: ");
		scanf("%d", &choise);
		printf("\n");
		if (choise)
		{
			finder();
			main();
		}
		else
		{
			main();
		}
		break;
	case 2:
		start();
		printf("\nЖелаете выполнить подсчет вхождений числа?\n1 - да, 0 - нет: ");
		scanf("%d", &choise);
		printf("\n");
		if (choise)
		{
			counter();
			main();
		}
		else
		{
			main();
		}
		break;
	case 3:
		start_noreplies();
		main();
		break;
	}

	return 0;
}
