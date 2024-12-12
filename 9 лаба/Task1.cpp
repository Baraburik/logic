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
    std::cout << "\nМатрица смежности:\n";
    std::cout << "   ";
    for (int i = 0; i < size; i++) {
        std::cout << "V" << i << "  ";
    }
    std::cout << "\n";
    for (int i = 0; i < size; i++) {
        std::cout << "V" << i << "  ";
        for (int j = 0; j < size; j++) {
            std::cout << graph[i][j] << "   ";
        }
        std::cout << "\n";
    }
}

// Поиск путей в ширину с использованием стандартной очереди
void bfsMatrix(int graph[MAX_NODES][MAX_NODES], int size, int start) {
    int dist[MAX_NODES];
    std::queue<int> queue;

    // Инициализация расстояний
    for (int i = 0; i < size; i++) {
        dist[i] = -1; // -1 означает, что вершина не посещена
    }

    // Начальная вершина
    dist[start] = 0;
    queue.push(start);

    std::cout << "\nПоиск расстояний (матрица смежности):\n";

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();

        for (int i = 0; i < size; i++) {
            if (graph[current][i] && dist[i] == -1) {
                dist[i] = dist[current] + 1;
                queue.push(i);
            }
        }
    }

    std::cout << "Расстояния от вершины " << start << ":\n";
    for (int i = 0; i < size; i++) {
        if (dist[i] >= 0) {
            std::cout << "Вершина " << start << "->" << i << ": " << dist[i] << "\n";
        }
        else {
            std::cout << "Вершина " << start << "->" << i << ": пути отсутствуют\n";
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
    std::cout << "\nСписок смежности:\n";
    for (int i = 0; i < size; i++) {
        std::cout << i << ": ";
        for (int j = 0; j < adjSize[i]; j++) {
            std::cout << adjList[i][j] << " ";
        }
        std::cout << "\n";
    }
}

// Поиск путей в ширину (список смежности) с использованием стандартной очереди
void bfsAdjacencyList(int* adjList[MAX_NODES], int adjSize[MAX_NODES], int size, int start) {
    int dist[MAX_NODES];
    std::queue<int> queue;

    // Инициализация расстояний
    for (int i = 0; i < size; i++) {
        dist[i] = -1;
    }

    // Начальная вершина
    dist[start] = 0;
    queue.push(start);

    std::cout << "\nПоиск расстояний (список смежности):\n";

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();

        for (int i = 0; i < adjSize[current]; i++) {
            int neighbor = adjList[current][i];
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[current] + 1;
                queue.push(neighbor);
            }
        }
    }

    std::cout << "Расстояния от вершины " << start << ":\n";
    for (int i = 0; i < size; i++) {
        if (dist[i] >= 0) {
            std::cout << "Вершина " << start << "->" << i << ": " << dist[i] << "\n";
        }
        else {
            std::cout << "Вершина " << start << "->" << i << ": пути отсутствуют\n";
        }
    }
}

int task1Start() {
    int graph[MAX_NODES][MAX_NODES];
    int* adjList[MAX_NODES];
    int adjSize[MAX_NODES];
    int size, start;

    std::cout << "Введите количество вершин графа (максимум " << MAX_NODES << "): ";
    std::cin >> size;

    if (size <= 0 || size > MAX_NODES) {
        std::cout << "Некорректное количество вершин. Программа завершена.\n";
        return 1;
    }

    std::cout << "Введите начальную вершину (от 0 до " << size - 1 << "): ";
    std::cin >> start;

    if (start < 0 || start >= size) {
        std::cout << "Некорректная начальная вершина. Программа завершена.\n";
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
