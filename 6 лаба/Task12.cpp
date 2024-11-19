#include "Task12Header.h"

// Функция для генерации случайной матрицы смежности
void generateMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (i == j) {
                matrix[i][j] = 0; // Диагональные элементы равны 0
            }
            else {
                matrix[i][j] = matrix[j][i] = rand() % 2; // Заполнение случайными 0 и 1
            }
        }
    }
}

// Функция для вывода матрицы смежности
void printMatrix(int** matrix, int size) {
    printf("Матрица смежности:\n");
    printf("   ");
    for (int i = 0; i < size; i++) {
        printf("V%d  ", i);
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("V%d  ", i);
        for (int j = 0; j < size; j++) {
            printf("%d   ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Функция для отождествления двух вершин
void mergeVertices(int** matrix, int size, int v1, int v2) {
    for (int i = 0; i < size; i++) {
        matrix[v1][i] |= matrix[v2][i]; // Совмещение ребер
        matrix[i][v1] = matrix[v1][i];
    }
    for (int i = 0; i < size; i++) {
        matrix[v2][i] = matrix[i][v2] = 0; // Удаление второй вершины
    }
}

// Функция для стягивания ребра
void contractEdge(int** matrix, int size, int v1, int v2) {
    mergeVertices(matrix, size, v1, v2);
}

// Функция для расщепления вершины
void splitVertex(int*** matrix, int* size, int v) {
    int newSize = *size + 1;

    // Расширяем указатель на строки
    *matrix = (int**)realloc(*matrix, newSize * sizeof(int*));
    if (*matrix == NULL) {
        printf("Ошибка: недостаточно памяти!\n");
        exit(1);
    }

    // Расширяем каждую строку
    for (int i = 0; i < newSize; i++) {
        if (i < *size) {
            (*matrix)[i] = (int*)realloc((*matrix)[i], newSize * sizeof(int));
        }
        else {
            // Выделяем новую строку
            (*matrix)[i] = (int*)malloc(newSize * sizeof(int));
        }

        if ((*matrix)[i] == NULL) {
            printf("Ошибка: недостаточно памяти!\n");
            exit(1);
        }
    }

    // Инициализируем новую строку и новый столбец
    for (int i = 0; i < newSize; i++) {
        (*matrix)[newSize - 1][i] = 0;
        (*matrix)[i][newSize - 1] = 0;
    }

    printf("Вершина %d будет расщеплена на вершины %d и %d.\n", v, v, newSize - 1);
    printf("Новые связи между вершинами:\n");

    // Добавляем новые связи
    for (int i = 0; i < *size; i++) {
        if ((*matrix)[v][i]) {
            (*matrix)[v][i] = (*matrix)[i][v] = 0; // Удаляем старое ребро
            (*matrix)[newSize - 1][i] = (*matrix)[i][newSize - 1] = 1; // Добавляем новое ребро
            printf("(%d, %d)\n", newSize - 1, i); // Выводим новые связи
        }
    }

    *size = newSize; // Обновляем размер
}

int task12Start() {
    setlocale(LC_ALL, "RUS");

    int size;
    printf("Введите размер матрицы смежности: ");
    scanf("%d", &size);

    // Создание динамической матрицы
    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
    }

    srand(time(NULL));

    // Генерация и вывод матрицы
    generateMatrix(matrix, size);
    printMatrix(matrix, size);

    // Выполнение операций
    int operation, v1, v2;
    printf("\n1 - Отождествление вершин\n2 - Стягивание ребра\n3 - Расщепление вершины\nВыберите операцию: ");
    scanf("%d", &operation);

    switch (operation) {
    case 1:
        printf("Введите номера двух вершин для отождествления (0-%d): ", size - 1);
        scanf("%d %d", &v1, &v2);
        if (v1 < 0 || v1 >= size || v2 < 0 || v2 >= size || v1 == v2) {
            printf("Некорректные номера вершин!\n");
            break;
        }
        mergeVertices(matrix, size, v1, v2);
        printf("Результат после отождествления вершин:\n");
        printMatrix(matrix, size);
        break;

    case 2:
        printf("Введите номера двух вершин для стягивания ребра (0-%d): ", size - 1);
        scanf("%d %d", &v1, &v2);
        if (v1 < 0 || v1 >= size || v2 < 0 || v2 >= size || v1 == v2) {
            printf("Некорректные номера вершин!\n");
            break;
        }
        contractEdge(matrix, size, v1, v2);
        printf("Результат после стягивания ребра:\n");
        printMatrix(matrix, size);
        break;

    case 3:
        printf("Введите номер вершины для расщепления (0-%d): ", size - 1);
        scanf("%d", &v1);
        if (v1 < 0 || v1 >= size) {
            printf("Некорректный номер вершины!\n");
            break;
        }
        splitVertex(&matrix, &size, v1);
        printf("Результат после расщепления вершины:\n");
        printMatrix(matrix, size);
        break;

    default:
        printf("Неверная операция!\n");
        break;
    }

    // Очистка памяти
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
