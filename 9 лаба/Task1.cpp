#include "Task1Header.h"

#define MAX_NODES 100

// ������� ��� ��������� ��������� ������� ���������
void generateAdjacencyMatrix(int graph[MAX_NODES][MAX_NODES], int size) {
    srand(time(0));
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (i == j) {
                graph[i][j] = 0; // ������� ������
            }
            else {
                graph[i][j] = graph[j][i] = rand() % 2; // ���������
            }
        }
    }
}

// ����� ������� ���������
void printAdjacencyMatrix(int graph[MAX_NODES][MAX_NODES], int size) {
    std::cout << "\n������� ���������:\n";
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

// ����� ����� � ������ � �������������� ����������� �������
void bfsMatrix(int graph[MAX_NODES][MAX_NODES], int size, int start) {
    int dist[MAX_NODES];
    std::queue<int> queue;

    // ������������� ����������
    for (int i = 0; i < size; i++) {
        dist[i] = -1; // -1 ��������, ��� ������� �� ��������
    }

    // ��������� �������
    dist[start] = 0;
    queue.push(start);

    std::cout << "\n����� ���������� (������� ���������):\n";

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

    std::cout << "���������� �� ������� " << start << ":\n";
    for (int i = 0; i < size; i++) {
        if (dist[i] >= 0) {
            std::cout << "������� " << start << "->" << i << ": " << dist[i] << "\n";
        }
        else {
            std::cout << "������� " << start << "->" << i << ": ���� �����������\n";
        }
    }
}

// ���������� ������ ��������� �� ������� ���������
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

// ����� ������ ���������
void printAdjacencyList(int* adjList[MAX_NODES], int adjSize[MAX_NODES], int size) {
    std::cout << "\n������ ���������:\n";
    for (int i = 0; i < size; i++) {
        std::cout << i << ": ";
        for (int j = 0; j < adjSize[i]; j++) {
            std::cout << adjList[i][j] << " ";
        }
        std::cout << "\n";
    }
}

// ����� ����� � ������ (������ ���������) � �������������� ����������� �������
void bfsAdjacencyList(int* adjList[MAX_NODES], int adjSize[MAX_NODES], int size, int start) {
    int dist[MAX_NODES];
    std::queue<int> queue;

    // ������������� ����������
    for (int i = 0; i < size; i++) {
        dist[i] = -1;
    }

    // ��������� �������
    dist[start] = 0;
    queue.push(start);

    std::cout << "\n����� ���������� (������ ���������):\n";

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

    std::cout << "���������� �� ������� " << start << ":\n";
    for (int i = 0; i < size; i++) {
        if (dist[i] >= 0) {
            std::cout << "������� " << start << "->" << i << ": " << dist[i] << "\n";
        }
        else {
            std::cout << "������� " << start << "->" << i << ": ���� �����������\n";
        }
    }
}

int task1Start() {
    int graph[MAX_NODES][MAX_NODES];
    int* adjList[MAX_NODES];
    int adjSize[MAX_NODES];
    int size, start;

    std::cout << "������� ���������� ������ ����� (�������� " << MAX_NODES << "): ";
    std::cin >> size;

    if (size <= 0 || size > MAX_NODES) {
        std::cout << "������������ ���������� ������. ��������� ���������.\n";
        return 1;
    }

    std::cout << "������� ��������� ������� (�� 0 �� " << size - 1 << "): ";
    std::cin >> start;

    if (start < 0 || start >= size) {
        std::cout << "������������ ��������� �������. ��������� ���������.\n";
        return 1;
    }

    // ��������� ������� ���������
    generateAdjacencyMatrix(graph, size);
    printAdjacencyMatrix(graph, size);

    // BFS ������� ���������
    bfsMatrix(graph, size, start);

    // ��������� ������ ���������
    buildAdjacencyList(graph, adjList, adjSize, size);
    printAdjacencyList(adjList, adjSize, size);

    // BFS ������ ���������
    bfsAdjacencyList(adjList, adjSize, size, start);

    for (int i = 0; i < size; i++) {
        free(adjList[i]);
    }

    return 0;
}
