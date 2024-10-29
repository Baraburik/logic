#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Функция сортировки Шелла
void shell(int* items, int count) {
    int i, j, gap, k;
    int x, a[5] = { 9, 5, 3, 2, 1 };

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i) {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

// Функция быстрой сортировки
void qs(int* items, int left, int right) {
    int i, j, x, y;
    i = left;
    j = right;
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++;
            j--;
        }
    } while (i <= j);

    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

// Функция для генерации случайного массива
void generate_random_array(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000; // случайные числа от 0 до 9999
    }
}

// Основная программа для тестирования времени работы алгоритмов
int main() {
    int sizes[] = { 10000, 20000, 40000, 100000,500000, 10000000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    clock_t start, end;
    double time_shell, time_qs;

    srand(time(NULL)); // инициализация генератора случайных чисел

    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];
        int* array_shell = (int*)malloc(size * sizeof(int));
        int* array_qs = (int*)malloc(size * sizeof(int));

        // копирование массивов для двух алгоритмов
        generate_random_array(array_shell, size);
        for (int j = 0; j < size; j++) {
            array_qs[j] = array_shell[j]; // копируем массив для другого алгоритма
        }

        // Измерение времени для сортировки Шелла
        start = clock();
        shell(array_shell, size);
        end = clock();
        time_shell = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Измерение времени для быстрой сортировки
        start = clock();
        qs(array_qs, 0, size - 1);
        end = clock();
        time_qs = ((double)(end - start)) / CLOCKS_PER_SEC;

        // Вывод результатов
        printf("Размер массива: %d\n", size);
        printf("Время сортировки Шелла: %f секунд\n", time_shell);
        printf("Время быстрой сортировки: %f секунд\n", time_qs);
        printf("\n");

        // Освобождение памяти
        free(array_shell);
        free(array_qs);
    }

    return 0;
}
