#include <iostream>
#include <queue>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <locale>

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
    std::cout << "\nМатрица смежности:\n";
    std::cout << "   ";
    for (int i = 0; i < nodes; i++) {
        std::cout << "V" << i + 1 << "  ";
    }
    std::cout << "\n";
    for (int i = 0; i < nodes; i++) {
        std::cout << "V" << i + 1 << "  ";
        for (int j = 0; j < nodes; j++) {
            std::cout << graph[i][j] << "   ";
        }
        std::cout << "\n";
    }
}

// Обход в ширину для матрицы смежности
void bfsMatrix(int graph[MAX_NODES][MAX_NODES], int nodes, int start) {
    std::vector<bool> visited(nodes, false);
    std::queue<int> q;

    visited[start] = true;
    q.push(start);

    std::cout << "\nОбход в ширину (матрица смежности): ";
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        std::cout << current + 1 << " ";

        for (int i = 0; i < nodes; i++) {
            if (graph[current][i] && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    std::cout << "\n";
}

// Вывод списка смежности
void printAdjacencyList(std::vector<int> adjList[], int adjSize[], int nodes) {
    std::cout << "\nСписок смежности:\n";
    for (int i = 0; i < nodes; i++) {
        std::cout << i + 1 << ": ";
        for (int j = 0; j < adjSize[i]; j++) {
            std::cout << adjList[i][j] + 1 << " ";
        }
        std::cout << "\n";
    }
}

// Обход в ширину для списка смежности
void bfsAdjacencyList(std::vector<int> adjList[], int adjSize[], int nodes, int start) {
    std::vector<bool> visited(nodes, false);
    std::queue<int> q;

    visited[start] = true;
    q.push(start);

    std::cout << "\nОбход в ширину (список смежности): ";
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        std::cout << current + 1 << " ";

        for (int i = 0; i < adjSize[current]; i++) {
            int neighbor = adjList[current][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    std::cout << "\n";
}

int main() {
    setlocale(LC_ALL, "RUS");

    int graph[MAX_NODES][MAX_NODES];
    int nodes;

    std::cout << "Введите количество вершин графа (максимум " << MAX_NODES << "): ";
    std::cin >> nodes;

    if (nodes <= 0 || nodes > MAX_NODES) {
        std::cout << "Некорректное количество вершин. Программа завершена.\n";
        return 1;
    }

    generateAdjacencyMatrix(graph, nodes);
    printAdjacencyMatrix(graph, nodes);

    bfsMatrix(graph, nodes, 0);

    // Построение списка смежности
    std::vector<int> adjList[MAX_NODES];
    int adjSize[MAX_NODES] = { 0 };

    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            if (graph[i][j]) {
                adjList[i].push_back(j);
                adjSize[i]++;
            }
        }
    }

    printAdjacencyList(adjList, adjSize, nodes);

    bfsAdjacencyList(adjList, adjSize, nodes, 0);

    return 0;
}
