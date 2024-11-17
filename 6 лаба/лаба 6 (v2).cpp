#include "Task12Header.h"
#include "Task34Header.h"


int main() {
    setlocale(LC_ALL, "RUS");

    int choise;
    printf("1 - задания 1, 2 \n");
    printf("2 - задания 3, 4 \n");
    printf("3 - Выход \n");
    printf("Веберите номер задания: ");
    scanf("%d", &choise);

    if (choise == 1)
    {
        startTaskOneTwo();
    }
    else if (choise == 2)
    {
        startTaskThreeFour();
    }
    else if (choise == 3)
    {
        printf("\nДо свидания!\n");
        exit;
    }
    else
    {
        printf("Ошибка: введен некорректный номер задания\n");
        main();
    }

    return 0;
}