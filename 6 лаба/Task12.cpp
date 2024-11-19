#include "Task12Header.h"

// ������� ��� ��������� ��������� ������� ���������
void generateMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i; j < size; j++) {
            if (i == j) {
                matrix[i][j] = 0; // ������������ �������� ����� 0
            }
            else {
                matrix[i][j] = matrix[j][i] = rand() % 2; // ���������� ���������� 0 � 1
            }
        }
    }
}

// ������� ��� ������ ������� ���������
void printMatrix(int** matrix, int size) {
    printf("������� ���������:\n");
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

// ������� ��� �������������� ���� ������
void mergeVertices(int** matrix, int size, int v1, int v2) {
    for (int i = 0; i < size; i++) {
        matrix[v1][i] |= matrix[v2][i]; // ���������� �����
        matrix[i][v1] = matrix[v1][i];
    }
    for (int i = 0; i < size; i++) {
        matrix[v2][i] = matrix[i][v2] = 0; // �������� ������ �������
    }
}

// ������� ��� ���������� �����
void contractEdge(int** matrix, int size, int v1, int v2) {
    mergeVertices(matrix, size, v1, v2);
}

// ������� ��� ����������� �������
void splitVertex(int*** matrix, int* size, int v) {
    int newSize = *size + 1;

    // ��������� ��������� �� ������
    *matrix = (int**)realloc(*matrix, newSize * sizeof(int*));
    if (*matrix == NULL) {
        printf("������: ������������ ������!\n");
        exit(1);
    }

    // ��������� ������ ������
    for (int i = 0; i < newSize; i++) {
        if (i < *size) {
            (*matrix)[i] = (int*)realloc((*matrix)[i], newSize * sizeof(int));
        }
        else {
            // �������� ����� ������
            (*matrix)[i] = (int*)malloc(newSize * sizeof(int));
        }

        if ((*matrix)[i] == NULL) {
            printf("������: ������������ ������!\n");
            exit(1);
        }
    }

    // �������������� ����� ������ � ����� �������
    for (int i = 0; i < newSize; i++) {
        (*matrix)[newSize - 1][i] = 0;
        (*matrix)[i][newSize - 1] = 0;
    }

    printf("������� %d ����� ���������� �� ������� %d � %d.\n", v, v, newSize - 1);
    printf("����� ����� ����� ���������:\n");

    // ��������� ����� �����
    for (int i = 0; i < *size; i++) {
        if ((*matrix)[v][i]) {
            (*matrix)[v][i] = (*matrix)[i][v] = 0; // ������� ������ �����
            (*matrix)[newSize - 1][i] = (*matrix)[i][newSize - 1] = 1; // ��������� ����� �����
            printf("(%d, %d)\n", newSize - 1, i); // ������� ����� �����
        }
    }

    *size = newSize; // ��������� ������
}

int task12Start() {
    setlocale(LC_ALL, "RUS");

    int size;
    printf("������� ������ ������� ���������: ");
    scanf("%d", &size);

    // �������� ������������ �������
    int** matrix = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        matrix[i] = (int*)malloc(size * sizeof(int));
    }

    srand(time(NULL));

    // ��������� � ����� �������
    generateMatrix(matrix, size);
    printMatrix(matrix, size);

    // ���������� ��������
    int operation, v1, v2;
    printf("\n1 - �������������� ������\n2 - ���������� �����\n3 - ����������� �������\n�������� ��������: ");
    scanf("%d", &operation);

    switch (operation) {
    case 1:
        printf("������� ������ ���� ������ ��� �������������� (0-%d): ", size - 1);
        scanf("%d %d", &v1, &v2);
        if (v1 < 0 || v1 >= size || v2 < 0 || v2 >= size || v1 == v2) {
            printf("������������ ������ ������!\n");
            break;
        }
        mergeVertices(matrix, size, v1, v2);
        printf("��������� ����� �������������� ������:\n");
        printMatrix(matrix, size);
        break;

    case 2:
        printf("������� ������ ���� ������ ��� ���������� ����� (0-%d): ", size - 1);
        scanf("%d %d", &v1, &v2);
        if (v1 < 0 || v1 >= size || v2 < 0 || v2 >= size || v1 == v2) {
            printf("������������ ������ ������!\n");
            break;
        }
        contractEdge(matrix, size, v1, v2);
        printf("��������� ����� ���������� �����:\n");
        printMatrix(matrix, size);
        break;

    case 3:
        printf("������� ����� ������� ��� ����������� (0-%d): ", size - 1);
        scanf("%d", &v1);
        if (v1 < 0 || v1 >= size) {
            printf("������������ ����� �������!\n");
            break;
        }
        splitVertex(&matrix, &size, v1);
        printf("��������� ����� ����������� �������:\n");
        printMatrix(matrix, size);
        break;

    default:
        printf("�������� ��������!\n");
        break;
    }

    // ������� ������
    for (int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
