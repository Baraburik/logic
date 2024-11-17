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

int main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));

	int size;
	int izol, conc, dom, reb = 0;

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

	int cnti = 0, cntc = size, cntd = 0, izolir = 0, domin = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			reb += G[i][j];

			if (G[i][j])
			{
				cntd += 1;
			}
			if (!G[i][j] && i != j)
			{
				cnti += 1;
			}
		}

		if (cnti == size - 1)
		{
			izolir += 1;
			cntc -= 1;
		}

		if (cntd == size - 1)
		{
			cntc -= 1;
			domin += 1;
		}

		cntd = 0;
		cnti = 0;
	}

	if (cntc < 0)
	{
		cntc = 0;
	}

	printf("\nРазмер графа - %d\n", reb / 2);
	printf("Изолированных - %d\nКонцевых - %d\nДоминирующих - %d\n", izolir, cntc, domin);


	//инцидентная
	const int r = reb / 2;

	//printf("\nreb - %d\n", r);

	int** I = new int* [size];

	for (int i = 0; i < size; i++)
	{
		I[i] = new int[64];
	}

	int C = 0;

	//Заполнение
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < r; j++)
		{
			I[i][j] = 0;
		}
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (G[i][j])
			{
				I[i][C] = 1;
				I[j][C++] = 1;
			}
		}
	}

	//Вывод
	printf("\n\nМатрица инцидентности: \n");
	printf("   ");
	for (int i = 0; i < r; i++)
	{
		printf("r%d  ", i + 1);
	}
	printf("\n");
	for (int i = 0; i < size; i++)
	{
		printf("V%d  ", i + 1);
		for (int j = 0; j < r; j++)
		{
			printf("%d   ", I[i][j]);
		}
		printf("\n");
	}

	printf("\nРазмер графа - %d\n", r);
	printf("Изолированных - %d\nКонцевых - %d\nДоминирующих - %d\n", izolir, cntc, domin);
}