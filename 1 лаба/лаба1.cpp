#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include <Windows.h>


int func1() {
    int mas[10] = { 10, 20, 11, 2, 3, 4, 5, 89, 1, 5 };
    int max = INT_MIN, min = INT_MAX;
    for (int i = 0; i <= 9; i++) {
        if (mas[i] > max)
            max = mas[i];
        if (mas[i] < min)
            min = mas[i];
    }
    printf("Максимальное /  Минимальное: %d / %d", max, min);
    printf("\n\n");
    return 0;
}


int func2() {
    srand(time(NULL));
    int mas[10];
    for (int i = 0; i < 10; i++) {
        mas[i] = rand() % 100;
        printf(" %d ", mas[i]);
    }
    printf("\n\n");
    return 0;
}

int func3() {
    srand(time(NULL));
    int a;
    printf("Введите размерность массива: ");
    scanf("%d", &a);
    int* arr = (int*)malloc(a * sizeof(int));
    for (int i = 0; i < a; i++) {
        arr[i] = rand() % 60 - 20;
        printf(" %d ", arr[i]);
    }
    free(arr);
    printf("\n\n");
    return 0;
}

int func4() {
    srand(time(NULL));
    int sum = 0;

    int n;
    printf("Введите размерность массива: ");
    scanf("%d", &n);
    int** a = (int**)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        a[i] = (int*)malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = rand() % 10;
            printf(" %d ", a[i][j]);
            if (i == j) sum += a[i][j];
        }
        printf("\n");
    }
    printf("\nсумма горизонтали: %d\n", sum);
    return 0;
}

typedef char td1;
typedef char td2;
typedef int td3;
typedef char td4;

struct vlot {
    td1 name[20];
    td2 facult[20];
    td3 zach;
    td4 surname[20];
};

typedef struct sNode {
    struct vlot bd;
    struct sNode* next;
} tNode;

tNode* create_list()
{
    tNode* p_begin = NULL;
    tNode* p = NULL;
    int cnt = 0;
    p_begin = (tNode*)malloc(sizeof(tNode));
    p = p_begin;
    p->next = NULL;
    printf("\nВведите имя студента: ");
    scanf("%s", &p->bd.name);
    printf("Введите фамилию стеднта: ");
    scanf("%s", &p->bd.surname);
    printf("Введите название факультета: ");
    scanf("%s", &p->bd.facult);
    printf("Введите номер зачетной книжки: ");
    scanf("%d", &p->bd.zach);
    printf("Для продолжения нажмите: '1', для завершения: '0' - ");
    scanf("%d", &cnt);

    while (cnt != 0)
    {
        p->next = (tNode*)malloc(sizeof(tNode));
        p = p->next;
        p->next = NULL;
        printf("\nВведите имя студента: ");
        scanf("%s", &p->bd.name);
        printf("Введите фамилию стеднта: ");
        scanf("%s", &p->bd.surname);
        printf("Введите название факультета: ");
        scanf("%s", &p->bd.facult);
        printf("Введите номер зачетной книжки: ");
        scanf("%d", &p->bd.zach);
        printf("Для продолжения нажмите: '1', для завершения: '0' - ");
        scanf("%d", &cnt);
    }
    return p_begin;
}
void print_list(tNode* p_begin)
{
    tNode* p = p_begin;
    printf("\n|      Имя       |     Фамилия     |   Факультет   | Номер зач. кн. | \n---------------------------------------------------------------------");
    while (p != NULL) {
        printf("\n| %14s | %15s | %13s | %14d |", p->bd.name, p->bd.surname, p->bd.facult, p->bd.zach);
        p = p->next;
    }
    printf("\n---------------------------------------------------------------------");
}
void delete_list(tNode* p_begin)
{
    tNode* p = p_begin;
    while (p != NULL) {
        tNode* tmp;
        p = (tNode*)malloc(sizeof(p));
        tmp = p;
        p = p->next;
        free(tmp);
    }
}
void func5() {
    tNode* p_begin = create_list();
    print_list(p_begin);
    delete_list(p_begin);
}
int main()
{
    srand(time(NULL));
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int choice;

    do {
        printf("Выберите задание:\n");
        printf("1 - Функция 1 (Макс / мин)\n");
        printf("2 - Функция 2 (Массив случайных чисел)\n");
        printf("3 - Функция 3 (Массив любого размера)\n");
        printf("4 - Функция 4 (Сумма в строке)\n");
        printf("5 - Функция 5 (Поиск студента)\n");

        printf("\nВведите номер задания: ");
        scanf("%d", &choice);  // Чтение целого числа

        switch (choice) {
        case 1:
            func1();
            break;
        case 2:
            func2();
            break;
        case 3:
            func3();
            break;
        case 4:
            func4();
            break;
        case 5:
            func5();
            break;
        default:
            printf("Неверный выбор\n");
        }

        printf("\nВернуться в меню? (1 - да, 0 - нет): ");
        scanf("%d", &choice);

    } while (choice == 1);
}

