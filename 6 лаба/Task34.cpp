#include "Task34Header.h"


// Функция для генерации случайной матрицы смежности
void generateRandomGraphh(int** graph, int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                graph[i][j] = 0;
            }
            else {
                graph[i][j] = rand() % 2;
                graph[j][i] = graph[i][j]; // Симметричность для неориентированного графа
            }
        }
    }
}

// Функция для вывода матрицы смежности
void printGraphMatrixx(int** graph, int size) {
    printf("Матрица смежности:\n");
    printf("   ");
    for (int i = 0; i < size; i++) {
        printf("V%d  ", i + 1);
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("V%d  ", i + 1);
        for (int j = 0; j < size; j++) {
            printf("%d   ", graph[i][j]);
        }
        printf("\n");
    }
}

// Функция объединения графов
void unionGraphs(int** graph1, int** graph2, int size, int** result) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = graph1[i][j] || graph2[i][j];
        }
    }
}

// Функция пересечения графов
void intersectGraphs(int** graph1, int** graph2, int size, int** result) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = graph1[i][j] && graph2[i][j];
        }
    }
}

// Функция кольцевой суммы графов
void ringSumGraphs(int** graph1, int** graph2, int size, int** result) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i][j] = graph1[i][j] ^ graph2[i][j];
        }
    }
}

// Функция декартова произведения графов
void cartesianProductGraphs(int** graph1, int size1, int** graph2, int size2, int** result) {
    int size = size1 * size2;
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            for (int k = 0; k < size1; k++) {
                for (int l = 0; l < size2; l++) {
                    int index1 = i * size2 + j;
                    int index2 = k * size2 + l;
                    result[index1][index2] = (i == k && graph2[j][l]) || (j == l && graph1[i][k]);
                }
            }
        }
    }
}

// Функция для выполнения операций над графом
void performOperations(int** graph1, int** graph2, int* size1, int* size2) {
    int v1, v2, choice;

    while (1) {
        printf("\nВыберите операцию:\n");
        printf("1 - Объединение\n");
        printf("2 - Пересечение\n");
        printf("3 - Кольцевая сумма\n");
        printf("4 - Декартово произведение\n");
        printf("5 - Выход\n");
        printf("Введите номер операции: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int** result = (int**)malloc(*size1 * sizeof(int*));
            for (int i = 0; i < *size1; i++) result[i] = (int*)malloc(*size1 * sizeof(int));
            unionGraphs(graph1, graph2, *size1, result);
            printf("\nОбъединение графов:\n");
            printGraphMatrixx(result, *size1);
            for (int i = 0; i < *size1; i++) free(result[i]);
            free(result);
        }
        else if (choice == 2) {
            int** result = (int**)malloc(*size1 * sizeof(int*));
            for (int i = 0; i < *size1; i++) result[i] = (int*)malloc(*size1 * sizeof(int));
            intersectGraphs(graph1, graph2, *size1, result);
            printf("\nПересечение графов:\n");
            printGraphMatrixx(result, *size1);
            for (int i = 0; i < *size1; i++) free(result[i]);
            free(result);
        }
        else if (choice == 3) {
            int** result = (int**)malloc(*size1 * sizeof(int*));
            for (int i = 0; i < *size1; i++) result[i] = (int*)malloc(*size1 * sizeof(int));
            ringSumGraphs(graph1, graph2, *size1, result);
            printf("\nКольцевая сумма графов:\n");
            printGraphMatrixx(result, *size1);
            for (int i = 0; i < *size1; i++) free(result[i]);
            free(result);
        }
        else if (choice == 4) {
            int sizeProduct = *size1 * *size2;
            int** cartesianResult = (int**)malloc(sizeProduct * sizeof(int*));
            for (int i = 0; i < sizeProduct; i++) cartesianResult[i] = (int*)malloc(sizeProduct * sizeof(int));
            cartesianProductGraphs(graph1, *size1, graph2, *size2, cartesianResult);
            printf("\nДекартово произведение графов:\n");
            printGraphMatrixx(cartesianResult, sizeProduct);
            for (int i = 0; i < sizeProduct; i++) free(cartesianResult[i]);
            free(cartesianResult);
        }
        else if (choice == 5) {
            printf("До свидания!\n");
            break;
        }
        else {
            printf("Ошибка: неверный выбор операции\n");
        }
    }
}

int startTaskThreeFour() {
    setlocale(LC_ALL, "RUS");

    int size1, size2;
    printf("Введите размер первого графа: ");
    scanf("%d", &size1);
    printf("Введите размер второго графа: ");
    scanf("%d", &size2);

    // Динамическое выделение памяти для матрицы
    int** graph1 = (int**)malloc(size1 * sizeof(int*));
    for (int i = 0; i < size1; i++) {
        graph1[i] = (int*)malloc(size1 * sizeof(int));
    }

    int** graph2 = (int**)malloc(size1 * sizeof(int*));
    for (int i = 0; i < size1; i++) {
        graph2[i] = (int*)malloc(size1 * sizeof(int));
    }

    generateRandomGraphh(graph1, size1);
    generateRandomGraphh(graph2, size2);
    printf("\nГраф 1:\n");
    printGraphMatrixx(graph1, size1);
    printf("\nГраф 2:\n");
    printGraphMatrixx(graph2, size2);

    performOperations(graph1, graph2, &size1, &size2);

    for (int i = 0; i < size1; i++) free(graph1[i]);
    for (int i = 0; i < size2; i++) free(graph2[i]);
    free(graph1);
    free(graph2);

    return 0;
}