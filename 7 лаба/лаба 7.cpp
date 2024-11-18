#include "RekHeader.h"
#include "NotRekHeader.h"

int main() {
    setlocale(LC_ALL, "RUS");

    srand(time(NULL));
    int choise;

    printf("1 - Рекурсивный обход ");
    printf("\n2 - Не рекурсивный обход ");
    printf("\n3 - Выход ");
    printf("\nВыберите задание: ");
    scanf("%d", &choise);

    if (choise == 1)
    {
        rekStart();
    }
    else if (choise == 2)
    {
        notrekStart();
    }
    else if (choise == 3)
    {
        printf("\nДо свидания!\n");
        exit;
    }
    else
    {
        printf("Ошибка: введено некорректное значение!");
        main();
    }

    return 0;
}
