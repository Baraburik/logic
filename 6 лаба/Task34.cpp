#include "Task34Header.h"

// Функция для генерации матрицы смежности
void generateMatrixx(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (i == j) {
                matrix[i][j] = 0; // Диагональные элементы равны 0
            }
            else {
                matrix[i][j] = matrix[j][i] = rand() % 2; // Заполнение случайными 0 и 1
            }
        }
    }
}

// Функция для вывода матрицы
void printMatrixx(int** matrix, int size) {
    printf("   ");
    for (int i = 0; i < size; i++) {
        printf("V%d  ", i);
    }
    printf("\n");
    for (int i = 0; i < size; i++) {
        printf("V%d  ", i);
        for (int j = 0; j < size; j++) {
            printf("%d   ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Функция для создания матрицы динамически
int** createMatrix(int size) {
    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
    }
    return matrix;
}

// Функция для освобождения памяти
void freeMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Операция объединения матриц
void unionMatrix(int** result, int** matrix1, int size1, int** matrix2, int size2) {
    int minSize = (size1 < size2) ? size1 : size2;
    for (int i = 0; i < minSize; i++) {
        for (int j = 0; j < minSize; j++) {
            result[i][j] = matrix1[i][j] || matrix2[i][j];
        }
    }
}

// Операция пересечения матриц
void intersectionMatrix(int** result, int** matrix1, int size1, int** matrix2, int size2) {
    int minSize = (size1 < size2) ? size1 : size2;
    for (int i = 0; i < minSize; i++) {
        for (int j = 0; j < minSize; j++) {
            result[i][j] = matrix1[i][j] && matrix2[i][j];
        }
    }
}

// Операция кольцевой суммы матриц
void symmetricDifferenceMatrix(int** result, int** matrix1, int size1, int** matrix2, int size2) {
    int minSize = (size1 < size2) ? size1 : size2;
    for (int i = 0; i < minSize; i++) {
        for (int j = 0; j < minSize; j++) {
            result[i][j] = matrix1[i][j] ^ matrix2[i][j];
        }
    }
}

// Операция декартова произведения матриц
void cartesianProduct(int** result, int** matrix1, int size1, int** matrix2, int size2) {
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size1; j++) {
            for (int k = 0; k < size2; k++) {
                for (int l = 0; l < size2; l++) {
                    result[i * size2 + k][j * size2 + l] = matrix1[i][j] && matrix2[k][l];
                }
            }
        }
    }
}

int task34Start() {
    setlocale(LC_ALL, "RUS");
    srand(time(0));

    int size1, size2;

    // Ввод размеров первой матрицы
    printf("Введите размер первой матрицы: ");
    scanf("%d", &size1);

    // Ввод размеров второй матрицы
    printf("Введите размер второй матрицы: ");
    scanf("%d", &size2);

    // Создание динамических матриц
    int** M = createMatrix(size1);
    int** M1 = createMatrix(size2);

    // Создание результирующих матриц
    int minSize = (size1 < size2) ? size1 : size2;
    int** unionM = createMatrix(minSize);
    int** intersectionM = createMatrix(minSize);
    int** symmetricDiffM = createMatrix(minSize);
    int** cartesianM = createMatrix(size1 * size2);

    // Генерация матриц
    printf("\nМатрица M:\n");
    generateMatrixx(M, size1);
    printMatrixx(M, size1);

    printf("\nМатрица M1:\n");
    generateMatrixx(M1, size2);
    printMatrixx(M1, size2);

    // Операции над матрицами
    printf("\nОбъединение:\n");
    unionMatrix(unionM, M, size1, M1, size2);
    printMatrixx(unionM, minSize);

    printf("\nПересечение:\n");
    intersectionMatrix(intersectionM, M, size1, M1, size2);
    printMatrixx(intersectionM, minSize);

    printf("\nКольцевая сумма:\n");
    symmetricDifferenceMatrix(symmetricDiffM, M, size1, M1, size2);
    printMatrixx(symmetricDiffM, minSize);

    printf("\nДекартово произведение:\n");
    cartesianProduct(cartesianM, M, size1, M1, size2);
    printMatrixx(cartesianM, size1 * size2);

    // Освобождение памяти
    freeMatrix(M, size1);
    freeMatrix(M1, size2);
    freeMatrix(unionM, minSize);
    freeMatrix(intersectionM, minSize);
    freeMatrix(symmetricDiffM, minSize);
    freeMatrix(cartesianM, size1 * size2);

    return 0;
}

