#include "Task12Header.h"
#include "Task34Header.h"

int main() {
	setlocale(LC_ALL, "RUS");

	int choise;
	printf("1 - Задание 1 - 2\n");
	printf("2 - Задание 3 - 4\n");
	printf("3 - Выход\n");
	printf("Выберите действие: ");
	scanf("%d", &choise);

	if (choise > 3) {
		printf("\nОшибка: выбрано некорректное действие\n");
		main();
	}

	switch (choise)
	{
	case 1:
		task12Start();
		break;
	case 2:
		task34Start();
		break;
	case 3:
		exit;
	}
}