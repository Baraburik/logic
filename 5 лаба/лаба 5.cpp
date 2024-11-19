#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>



int** generator(int size)
{
	int** G = new int* [size];

	for (int i = 0; i < size; i++)
	{
		G[i] = new int [size];
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == j)
			{
				G[i][j] = 0;
			}
			else
			{
				G[i][j] = rand() % 2;
				if (G[i][j])
				{
					G[j][i] = 1;
				}
				else
				{
					G[j][i] = 0;
				}
			}
		}
	}

	return G;
}

// Cписок смежности
int** adjacencyMatrixToList(int** matrix, int size, int** listSizes) {
	
	int** adjacencyList = (int**)malloc(size * sizeof(int*));
	*listSizes = (int*)malloc(size * sizeof(int)); 

	for (int i = 0; i < size; i++) {
		int count = 0;

		// Считаем количество соседей для текущей вершины
		for (int j = 0; j < size; j++) {
			if (matrix[i][j] == 1) {
				count++;
			}
		}

		// Выделяем память для списка соседей
		adjacencyList[i] = (int*)malloc(count * sizeof(int));
		(*listSizes)[i] = count;

		// Заполняем список соседей
		int index = 0;
		for (int j = 0; j < size; j++) {
			if (matrix[i][j] == 1) {
				adjacencyList[i][index++] = j + 1; // Добавляем вершину
			}
		}
	}

	return adjacencyList;
}

void analyzeVertices(int** matrix, int size) {
	printf("\nАнализ вершин:\n");

	printf("Изолированные: ");
	int hasIsolated = 0;
	int hasDominating = 0;
	int hasTerminal = 0;

	for (int i = 0; i < size; i++) {
		int degree = 0;
		int isDominating = 1;

		for (int j = 0; j < size; j++) {
			degree += matrix[i][j];
			if (i != j && matrix[j][i] == 0) {
				isDominating = 0;
			}
		}

		// Изолированная вершина
		if (degree == 0) {
			printf("V%d ", i + 1);
			hasIsolated = 1;
		}

		// Концевая вершина
		if (degree == 1) {
			if (!hasTerminal) {
				printf("\nКонцевые: ");
				hasTerminal = 1;
			}
			printf("V%d ", i + 1);
		}

		// Доминирующая вершина
		if (isDominating) {
			if (!hasDominating) {
				printf("\nДоминирующие: ");
				hasDominating = 1;
			}
			printf("V%d ", i + 1);
		}
	}

	if (!hasIsolated) {
		printf("-\n");
	}
	else {
		printf("\n");
	}

	if (!hasTerminal) {
		printf("\nКонцевые: -\n");
	}

	if (!hasDominating) {
		printf("\nДоминирующие: -\n");
	}
}

// Функция для вывода списка смежности
void printAdjacencyList(int** list, int* listSizes, int size) {
	for (int i = 0; i < size; i++) {
		printf("V%d: ", i + 1);
		for (int j = 0; j < listSizes[i]; j++) {
			printf("V%d ", list[i][j]);
		}
		printf("\n");
	}
}

// Очистка памяти
void freeAdjacencyList(int** list, int* listSizes, int size) {
	for (int i = 0; i < size; i++) {
		free(list[i]);
	}
	free(list);
	free(listSizes);
}

int main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));

	int size;

	printf("Введите размер графа: ");
	scanf("%d", &size);

	int** G = generator(size);

	//Генератор

	//Вывод
	printf("Матрица смежности: \n");
	printf("   ");
	for (int i = 0; i < size; i++)
	{
		printf("V%d  ", i + 1);
	}
	printf("\n");

	for (int i = 0; i < size; i++)
	{
		printf("V%d  ", i + 1);
		for (int j = 0; j < size; j++)
		{
			printf("%d   ", G[i][j]);
		}
		printf("\n");
	}

	int* listSizes; // Массив для хранения размеров каждого списка
	int** adjacencyList = adjacencyMatrixToList(G, size, &listSizes);

	printf("\nСписок смежности:\n");
	printAdjacencyList(adjacencyList, listSizes, size);

	analyzeVertices(G, size);

	// Освобождение памяти
	freeAdjacencyList(adjacencyList, listSizes, size);
}