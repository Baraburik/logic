#include "Task12Header.h"

// Функция для генерации случайной матрицы смежности
void generateRandomGraph(int** graph, int size) {
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
void printGraphMatrix(int** graph, int size) {
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

// Функция для преобразования матрицы смежности в списки смежности
void convertToAdjacencyList(int** graph, int size) {
    printf("\nСписки смежности:\n");
    for (int i = 0; i < size; i++) {
        printf("Вершина %d: ", i + 1);
        for (int j = 0; j < size; j++) {
            if (graph[i][j] == 1) {
                printf("%d ", j + 1);
            }
        }
        printf("\n");
    }
}

// Функция отождествления вершин
void mergeVertices(int** graph, int size, int u, int v) {
    u--; v--; // Перевод в нумерацию массива
    for (int i = 0; i < size; i++) {
        if (graph[u][i] == 1 || graph[v][i] == 1) {
            graph[u][i] = 1;
            graph[i][u] = 1;
        }
    }
    for (int i = 0; i < size; i++) {
        graph[v][i] = 0;
        graph[i][v] = 0;
    }
    printf("Вершины %d и %d отождествлены.\n", u + 1, v + 1);
}

// Функция стягивания ребра
void contractEdge(int** graph, int size, int u, int v) {
    if (graph[u - 1][v - 1] == 1) {
        mergeVertices(graph, size, u, v);
        printf("Ребро между вершинами %d и %d стянуто.\n", u, v);
    }
    else {
        printf("Между вершинами %d и %d нет ребра.\n", u, v);
    }
}

// Функция расщепления вершины
int** splitVertex(int** graph, int* size, int v) {
    v--; // Перевод в нумерацию массива
    int newSize = *size + 1;

    // Расширение графа
    int** newGraph = (int**)realloc(graph, newSize * sizeof(int*)); // Явное преобразование к int**
    if (!newGraph) {
        printf("Ошибка выделения памяти для строк!\n");
        return graph; // Возвращаем старый указатель без изменений
    }

    for (int i = 0; i < newSize; i++) {
        int* temp = (int*)realloc(newGraph[i], newSize * sizeof(int)); // Явное преобразование к int*
        if (!temp) {
            printf("Ошибка выделения памяти для столбцов!\n");

            // Освобождаем уже выделенную память для новых строк
            for (int j = 0; j < i; j++) {
                free(newGraph[j]);
            }
            free(newGraph);
            return graph; // Возвращаем старый указатель
        }
        newGraph[i] = temp;
    }

    // Инициализация новой строки и столбца
    for (int i = 0; i < newSize; i++) {
        newGraph[newSize - 1][i] = 0;
        newGraph[i][newSize - 1] = 0;
    }

    // Соединение новой вершины с окружением исходной
    for (int i = 0; i < *size; i++) {
        if (newGraph[v][i] == 1) {
            newGraph[newSize - 1][i] = 1;
            newGraph[i][newSize - 1] = 1;
        }
    }
    newGraph[v][newSize - 1] = 1;
    newGraph[newSize - 1][v] = 1;

    *size = newSize;
    printf("Вершина %d расщеплена на вершины %d и %d.\n", v + 1, v + 1, newSize);
    return newGraph; // Возвращаем новый указатель
}

// Функция для выполнения операций над графом
void performOperations(int** graph, int* size) {
    int v1, v2, choice;

    while (1) {
        printf("\nВыберите операцию:\n");
        printf("1 - Отождествление вершин\n");
        printf("2 - Стягивание ребра\n");
        printf("3 - Расщепление вершины\n");
        printf("4 - Вывод матрицы смежности\n");
        printf("5 - Выход\n");
        printf("Введите номер операции: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Введите номера вершин для отождествления: ");
            scanf("%d %d", &v1, &v2);
            mergeVertices(graph, *size, v1, v2);
            printGraphMatrix(graph, *size);
            convertToAdjacencyList(graph, *size);
        }
        else if (choice == 2) {
            printf("Введите номера вершин для стягивания ребра: ");
            scanf("%d %d", &v1, &v2);
            contractEdge(graph, *size, v1, v2);
            printGraphMatrix(graph, *size);
            convertToAdjacencyList(graph, *size);
        }
        else if (choice == 3) {
            printf("Введите номер вершины для расщепления: ");
            scanf("%d", &v1);
            graph = splitVertex(graph, size, v1);
            printGraphMatrix(graph, *size);
            convertToAdjacencyList(graph, *size);
        }
        else if (choice == 4) {
            printGraphMatrix(graph, *size);
            convertToAdjacencyList(graph, *size);
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

int startTaskOneTwo() {
    setlocale(LC_ALL, "RUS");

    int size;
    printf("Введите размер графа: ");
    scanf("%d", &size);

    // Динамическое выделение памяти для матрицы
    int** graph = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        graph[i] = (int*)malloc(size * sizeof(int));
    }

    // Генерация случайной матрицы смежности
    generateRandomGraph(graph, size);
    printGraphMatrix(graph, size);
    convertToAdjacencyList(graph, size);

    // Выполнение операций над графом
    performOperations(graph, &size);

    // Освобождение памяти
    for (int i = 0; i < size; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}