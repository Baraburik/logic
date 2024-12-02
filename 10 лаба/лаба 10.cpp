#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <locale.h>

// Функция для генерации случайной матрицы смежности
void generateAdjacencyMatrix(int** graph, int size, int isDirected) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i != j) {
                graph[i][j] = rand() % 9 + 1;  // Случайный вес от 1 до 10
                if (!isDirected) {
                    graph[j][i] = graph[i][j];
                }
            }
            else {
                graph[i][j] = 0;  // Диагональ матрицы (петли отсутствуют)
            }
        }
    }
}

// Вывод матрицы смежности
void printMatrix(int** graph, int size) {
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

// Поиск расстояний
void bfs(int** graph, int size, int start, int* distances) {
    int* visited = (int*)calloc(size, sizeof(int));
    int* queue = (int*)malloc(size * sizeof(int));
    int front = 0, rear = 0;

    // Инициализация начальной вершины
    for (int i = 0; i < size; i++) {
        distances[i] = INT_MAX;  // Установка начальных расстояний
    }
    distances[start] = 0;
    queue[rear++] = start;
    visited[start] = 1;

    while (front < rear) {
        int current = queue[front++];
        for (int i = 0; i < size; i++) {
            if (graph[current][i] != 0 && !visited[i]) {
                visited[i] = 1;
                distances[i] = distances[current] + graph[current][i];
                queue[rear++] = i;
            }
        }
    }

    free(visited);
    free(queue);
}

// Вычисление радиуса и диаметра графа
void calculateRadiusAndDiameter(int** graph, int size, int* radius, int* diameter) {
    *radius = INT_MAX;
    *diameter = 0;

    for (int i = 0; i < size; i++) {
        int* distances = (int*)malloc(size * sizeof(int));
        bfs(graph, size, i, distances);

        int maxDistance = 0;
        for (int j = 0; j < size; j++) {
            if (distances[j] != INT_MAX && distances[j] > maxDistance) {
                maxDistance = distances[j];
            }
        }
        if (maxDistance < *radius) {
            *radius = maxDistance;
        }
        if (maxDistance > *diameter) {
            *diameter = maxDistance;
        }

        free(distances);
    }
}

int main() {
    setlocale(LC_ALL, "RUS");

    int size, radius, diameter;

    printf("Введите размер графа (количество вершин): ");
    scanf("%d", &size);

    // Выделение памяти для матрицы смежности
    int** graph = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        graph[i] = (int*)malloc(size * sizeof(int));
    }

    // Генерация и вывод неориентированного графа
    printf("\nНеориентированный граф:\n\n");
    generateAdjacencyMatrix(graph, size, 0);
    printMatrix(graph, size);

    // Вычисление радиуса и диаметра неориентированного графа
    calculateRadiusAndDiameter(graph, size, &radius, &diameter);
    printf("\nРадиус: %d, Диаметр: %d\n", radius, diameter);

    // Генерация и вывод ориентированного графа
    printf("\nОриентированный граф:\n\n");
    generateAdjacencyMatrix(graph, size, 1);
    printMatrix(graph, size);

    // Вычисление радиуса и диаметра ориентированного графа
    calculateRadiusAndDiameter(graph, size, &radius, &diameter);
    printf("\nРадиус: %d, Диаметр: %d\n", radius, diameter);

    for (int i = 0; i < size; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}
