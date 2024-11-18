#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define MAX_NODES 100

// Генератор матрицы
void generateAdjacencyMatrix(int graph[MAX_NODES][MAX_NODES], int nodes) {
    srand(time(NULL));
    for (int i = 0; i < nodes; i++) {
        for (int j = i; j < nodes; j++) {
            if (i == j) {
                graph[i][j] = 0;
            }
            else {
                graph[i][j] = graph[j][i] = rand() % 2;
            }
        }
    }
}

// Вывод матрицы
void printAdjacencyMatrix(int graph[MAX_NODES][MAX_NODES], int nodes) {
    printf("\nМатрица смежности:\n");
    printf("   ");
    for (int i = 0; i < nodes; i++) {
        printf("V%d  ", i + 1);
    }
    printf("\n");
    for (int i = 0; i < nodes; i++) {
        printf("V%d  ", i + 1);
        for (int j = 0; j < nodes; j++) {
            printf("%d   ", graph[i][j]);
        }
        printf("\n");
    }
}

// Обход в ширину для матрицы смежности
void bfsMatrix(int graph[MAX_NODES][MAX_NODES], int nodes, int start) {
    int visited[MAX_NODES] = { 0 };
    int queue[MAX_NODES];
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    printf("\nОбход в ширину (матрица смежности): ");
    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current+1);

        for (int i = 0; i < nodes; i++) {
            if (graph[current][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
    printf("\n");
}

// Вывод списка смежности
void printAdjacencyList(int* adjList[], int adjSize[], int nodes) {
    printf("\nСписок смежности:\n");
    for (int i = 0; i < nodes; i++) {
        printf("%d: ", i+1);
        for (int j = 0; j < adjSize[i]; j++) {
            printf("%d ", adjList[i][j]+1);
        }
        printf("\n");
    }
}

// Обход в ширину для списка смежности
void bfsAdjacencyList(int* adjList[], int adjSize[], int nodes, int start) {
    int visited[MAX_NODES] = { 0 };
    int queue[MAX_NODES];
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    printf("\nОбход в ширину (список смежности): ");
    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current+1);

        for (int i = 0; i < adjSize[current]; i++) {
            int neighbor = adjList[current][i];
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                queue[rear++] = neighbor;
            }
        }
    }
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "RUS");

    int graph[MAX_NODES][MAX_NODES];
    int nodes;

    printf("Введите количество вершин графа (максимум %d): ", MAX_NODES);
    scanf("%d", &nodes);

    if (nodes <= 0 || nodes > MAX_NODES) {
        printf("Некорректное количество вершин. Программа завершена.\n");
        return 1;
    }

    generateAdjacencyMatrix(graph, nodes);
    printAdjacencyMatrix(graph, nodes);

    bfsMatrix(graph, nodes, 0);

    // Построение списка смежности
    int* adjList[MAX_NODES];
    int adjSize[MAX_NODES] = { 0 };

    for (int i = 0; i < nodes; i++) {
        adjList[i] = (int*)malloc(nodes * sizeof(int));
        for (int j = 0; j < nodes; j++) {
            if (graph[i][j]) {
                adjList[i][adjSize[i]++] = j;
            }
        }
    }

    printAdjacencyList(adjList, adjSize, nodes);

    bfsAdjacencyList(adjList, adjSize, nodes, 0);

    for (int i = 0; i < nodes; i++) {
        free(adjList[i]);
    }

    return 0;
}
