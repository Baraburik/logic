#include "Task1Header.h"

#define MAX_NODES 100

// Функция для генерации случайной матрицы смежности
void generateAdjacencyMatrix(int graph[MAX_NODES][MAX_NODES], int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (i == j) {
                graph[i][j] = 0; // Никаких петель
            }
            else {
                graph[i][j] = graph[j][i] = rand() % 2; // Симметрия
            }
        }
    }
}

// Вывод матрицы смежности
void printAdjacencyMatrix(int graph[MAX_NODES][MAX_NODES], int size) {
    printf("\nМатрица смежности:\n");
    printf("   ");
    for (int i = 0; i < size; i++) {
        printf("V%d  ", i);
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("V%d  ", i);
        for (int j = 0; j < size; j++) {
            printf("%d   ", graph[i][j]);
        }
        printf("\n");
    }
}

// Поиск путей в ширину
void bfsMatrix(int graph[MAX_NODES][MAX_NODES], int size, int start) {
    int dist[MAX_NODES];
    int queue[MAX_NODES];
    int front = 0, rear = 0;

    // Инициализация расстояний
    for (int i = 0; i < size; i++) {
        dist[i] = -1; // -1 означает, что вершина не посещена
    }

    // Начальная вершина
    dist[start] = 0;
    queue[rear++] = start;

    printf("\nПоиск расстояний (матрица смежности):\n");

    while (front < rear) {
        int current = queue[front++];

        for (int i = 0; i < size; i++) {
            if (graph[current][i] && dist[i] == -1) {
                dist[i] = dist[current] + 1;
                queue[rear++] = i;
            }
        }
    }

    printf("Расстояния от вершины %d:\n", start);
    for (int i = 0; i < size; i++) {
        if (dist[i] >= 0) {
            printf("Вершина %d->%d: %d\n", start, i, dist[i]);
        }
        else {
            printf("Вершина %d->%d: пути отсутствуют\n", start, i);
        }
    }
}

// Построение списка смежности из матрицы смежности
void buildAdjacencyList(int graph[MAX_NODES][MAX_NODES], int* adjList[MAX_NODES], int adjSize[MAX_NODES], int size) {
    for (int i = 0; i < size; i++) {
        adjList[i] = (int*)malloc(size * sizeof(int));
        adjSize[i] = 0;
        for (int j = 0; j < size; j++) {
            if (graph[i][j]) {
                adjList[i][adjSize[i]++] = j;
            }
        }
    }
}

// Вывод списка смежности
void printAdjacencyList(int* adjList[MAX_NODES], int adjSize[MAX_NODES], int size) {
    printf("\nСписок смежности:\n");
    for (int i = 0; i < size; i++) {
        printf("%d: ", i);
        for (int j = 0; j < adjSize[i]; j++) {
            printf("%d ", adjList[i][j]);
        }
        printf("\n");
    }
}

// Поиск путей в ширину (список смежности)
void bfsAdjacencyList(int* adjList[MAX_NODES], int adjSize[MAX_NODES], int size, int start) {
    int dist[MAX_NODES];
    int queue[MAX_NODES];
    int front = 0, rear = 0;

    // Инициализация расстояний
    for (int i = 0; i < size; i++) {
        dist[i] = -1;
    }

    // Начальная вершина
    dist[start] = 0;
    queue[rear++] = start;

    printf("\nПоиск расстояний (список смежности):\n");

    while (front < rear) {
        int current = queue[front++];

        for (int i = 0; i < adjSize[current]; i++) {
            int neighbor = adjList[current][i];
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[current] + 1;
                queue[rear++] = neighbor;
            }
        }
    }

    printf("Расстояния от вершины %d:\n", start);
    for (int i = 0; i < size; i++) {
        if (dist[i] >= 0) {
            printf("Вершина %d->%d: %d\n", start, i, dist[i]);
        }
        else {
            printf("Вершина %d->%d: пути отсутствуют\n", start, i);
        }
    }
}

int task1Start() {
    int graph[MAX_NODES][MAX_NODES];
    int* adjList[MAX_NODES];
    int adjSize[MAX_NODES];
    int size, start;

    printf("Введите количество вершин графа (максимум %d): ", MAX_NODES);
    scanf("%d", &size);

    if (size <= 0 || size > MAX_NODES) {
        printf("Некорректное количество вершин. Программа завершена.\n");
        return 1;
    }

    printf("Введите начальную вершину (от 0 до %d): ", size - 1);
    scanf("%d", &start);

    if (start < 0 || start >= size) {
        printf("Некорректная начальная вершина. Программа завершена.\n");
        return 1;
    }

    // Генерация матрицы смежности
    generateAdjacencyMatrix(graph, size);
    printAdjacencyMatrix(graph, size);

    // BFS матрицы смежности
    bfsMatrix(graph, size, start);

    // Генерация списка смежности
    buildAdjacencyList(graph, adjList, adjSize, size);
    printAdjacencyList(adjList, adjSize, size);

    // BFS списка смежности
    bfsAdjacencyList(adjList, adjSize, size, start);

    for (int i = 0; i < size; i++) {
        free(adjList[i]);
    }

    return 0;
}
