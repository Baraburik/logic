#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <limits.h>
#include <locale.h>

// Функция для генерации случайной матрицы смежности
void generateAdjacencyMatrix(std::vector<std::vector<int>>& graph, int size, bool isDirected) {
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
void printMatrix(const std::vector<std::vector<int>>& graph, int size) {
    std::cout << "   ";
    for (int i = 0; i < size; i++) {
        std::cout << "V" << i + 1 << "  ";
    }
    std::cout << "\n";
    for (int i = 0; i < size; i++) {
        std::cout << "V" << i + 1 << "  ";
        for (int j = 0; j < size; j++) {
            std::cout << graph[i][j] << "   ";
        }
        std::cout << "\n";
    }
}

// Поиск расстояний (поиск в ширину)
void bfs(const std::vector<std::vector<int>>& graph, int size, int start, std::vector<int>& distances) {
    std::vector<bool> visited(size, false);
    std::queue<int> queue;

    // Инициализация начальной вершины
    for (int i = 0; i < size; i++) {
        distances[i] = INT_MAX;  // Установка начальных расстояний
    }
    distances[start] = 0;
    queue.push(start);
    visited[start] = true;

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();

        for (int i = 0; i < size; i++) {
            if (graph[current][i] != 0 && !visited[i]) {
                visited[i] = true;
                distances[i] = distances[current] + graph[current][i];
                queue.push(i);
            }
        }
    }
}

// Вычисление радиуса и диаметра графа
void calculateRadiusAndDiameter(const std::vector<std::vector<int>>& graph, int size, int& radius, int& diameter) {
    radius = INT_MAX;
    diameter = 0;

    for (int i = 0; i < size; i++) {
        std::vector<int> distances(size);
        bfs(graph, size, i, distances);

        int maxDistance = 0;
        for (int j = 0; j < size; j++) {
            if (distances[j] != INT_MAX && distances[j] > maxDistance) {
                maxDistance = distances[j];
            }
        }
        if (maxDistance < radius) {
            radius = maxDistance;
        }
        if (maxDistance > diameter) {
            diameter = maxDistance;
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");

    int size, radius, diameter;

    std::cout << "Введите количество вершин: ";
    std::cin >> size;

    // Выделение памяти для матрицы смежности
    std::vector<std::vector<int>> graph(size, std::vector<int>(size));

    // Генерация и вывод неориентированного графа
    std::cout << "\nНеориентированный граф:\n\n";
    generateAdjacencyMatrix(graph, size, false);
    printMatrix(graph, size);

    // Вычисление радиуса и диаметра неориентированного графа
    calculateRadiusAndDiameter(graph, size, radius, diameter);
    std::cout << "\nРадиус: " << radius << ", Диаметр: " << diameter << "\n";

    // Генерация и вывод ориентированного графа
    std::cout << "\nОриентированный граф:\n\n";
    generateAdjacencyMatrix(graph, size, true);
    printMatrix(graph, size);

    // Вычисление радиуса и диаметра ориентированного графа
    calculateRadiusAndDiameter(graph, size, radius, diameter);
    std::cout << "\nРадиус: " << radius << ", Диаметр: " << diameter << "\n";

    return 0;
}
