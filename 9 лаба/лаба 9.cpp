#include "Task1Header.h"
#include "Task2Header.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "RUS");

    int choise;
    printf("1 - Задание 1 \n");
    printf("2 - Задание 2 \n");
    printf("3 - Выход \n");
    printf("Выберите задание: ");
    scanf("%d", &choise);

    if (choise == 1)
    {
        task1Start();
    }
    else if (choise == 2)
    {
        task2Start();
    }
    else if (choise == 3)
    {
        exit;
    }
    else
    {
        printf("\nОшибка: выбран некорректный номер!\n");
        main();
    }

    return 0;
}