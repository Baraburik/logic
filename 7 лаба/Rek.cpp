#include "RekHeader.h"

// Генерация матрицы смежности
void generateAdjacencyMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            }
            else {
                int edge = rand() % 2;
                matrix[i][j] = edge;
                matrix[j][i] = edge;
            }
        }
    }
}

// Вывод матрицы смежности
void printAdjacencyMatrix(int** matrix, int size) {
    printf("\nМатрица смежности:\n");
    printf("   ");
    for (int i = 0; i < size; i++) {
        printf("V%d  ", i + 1);
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("V%d  ", i + 1);
        for (int j = 0; j < size; j++) {
            printf("%d   ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Обход в глубину для матрицы смежности
void dfsMatrix(int** matrix, int* visited, int size, int vertex) {
    visited[vertex] = 1;
    printf("%d ", vertex + 1);

    for (int i = 0; i < size; i++) {
        if (matrix[vertex][i] == 1 && !visited[i]) {
            dfsMatrix(matrix, visited, size, i);
        }
    }
}

// Создание списка смежности
void convertToAdjList(int** matrix, int** adjList, int* listSizes, int size) {
    for (int i = 0; i < size; i++) {
        int k = 0;
        for (int j = 0; j < size; j++) {
            if (matrix[i][j] == 1) {
                adjList[i][k++] = j;
            }
        }
        listSizes[i] = k;
    }
}

// Вывод списка смежности
void printAdjList(int** adjList, int* listSizes, int size) {
    printf("Список смежности:\n");
    for (int i = 0; i < size; i++) {
        printf("%d: ", i + 1);
        for (int j = 0; j < listSizes[i]; j++) {
            printf("%d ", adjList[i][j] + 1);
        }
        printf("\n");
    }
}

// Обход в глубину для списка смежности
void dfsList(int** adjList, int* visited, int size, int* listSizes, int vertex) {
    visited[vertex] = 1;
    printf("%d ", vertex + 1);

    for (int i = 0; i < listSizes[vertex]; i++) {
        int neighbor = adjList[vertex][i];
        if (!visited[neighbor]) {
            dfsList(adjList, visited, size, listSizes, neighbor);
        }
    }
}

int rekStart() {
    setlocale(LC_ALL, "RUS");

    srand(time(NULL));
    int size;

    printf("Введите размер графа: ");
    scanf("%d", &size);

    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
    }

    int** adjList = (int**)malloc(size * sizeof(int*));
    int* listSizes = (int*)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        adjList[i] = (int*)malloc(size * sizeof(int));
    }

    int* visited = (int*)malloc(size * sizeof(int));

    generateAdjacencyMatrix(matrix, size);
    printAdjacencyMatrix(matrix, size);

    printf("\nОбход в глубину (матрица смежности): ");
    for (int i = 0; i < size; i++) {
        visited[i] = 0; // Сброс посещённых вершин
    }
    dfsMatrix(matrix, visited, size, 0);
    printf("\n\n");

    convertToAdjList(matrix, adjList, listSizes, size);
    printAdjList(adjList, listSizes, size);

    printf("\nОбход в глубину (список смежности): ");
    for (int i = 0; i < size; i++) {
        visited[i] = 0; // Сброс посещённых вершин
    }
    dfsList(adjList, visited, size, listSizes, 0);
    printf("\n");

    for (int i = 0; i < size; i++) {
        free(matrix[i]);
        free(adjList[i]);
    }
    free(matrix);
    free(adjList);
    free(listSizes);
    free(visited);

    return 0;
}
