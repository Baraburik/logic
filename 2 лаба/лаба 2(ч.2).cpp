#include <iostream>
#include <ctime>
#include <cstdint>
#include <locale.h>


void shell(int* items, int count)
{

    int i, j, gap, k;
    int x, a[5];

    a[0] = 9; a[1] = 5; a[2] = 3; a[3] = 2; a[4] = 1;

    for (k = 0; k < 5; k++) {
        gap = a[k];
        for (i = gap; i < count; ++i)
        {
            x = items[i];
            for (j = i - gap; (x < items[j]) && (j >= 0); j = j - gap)
                items[j + gap] = items[j];
            items[j + gap] = x;
        }
    }
}

void qs(int* items, int left, int right) //вызов функции: qs(items, 0, count-1);
{
    int i, j;
    int x, y;

    i = left; j = right;

    /* выбор компаранда */
    x = items[(left + right) / 2];

    do {
        while ((items[i] < x) && (i < right)) i++;
        while ((x < items[j]) && (j > left)) j--;

        if (i <= j) {
            y = items[i];
            items[i] = items[j];
            items[j] = y;
            i++; j--;
        }
    } while (i <= j);
    if (left < j) qs(items, left, j);
    if (i < right) qs(items, i, right);
}

int compare_ints(const void* a, const void* b)
{
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}
int main()
{
    setlocale(LC_ALL, "RUS");
    clock_t start, end;
    srand(time(0));
    const size_t MAS_SIZE = 500000;
    const size_t SIZE_FOR_SHELL = MAS_SIZE;
    {
        std::cout << "размер массива = " << SIZE_FOR_SHELL << std::endl;
        int help_var_for_sequence = MAS_SIZE;

        int* arr_for_shell = (int*)malloc(sizeof(int) * SIZE_FOR_SHELL);
        for (size_t i = 0; i < SIZE_FOR_SHELL; ++i)
        {
            arr_for_shell[i] = rand() % 50 + 1;
        }
        start = clock();
        shell(arr_for_shell, SIZE_FOR_SHELL);
        end = clock();
        std::cout << "shell (случайные числа) время выполнения: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << std::endl;
        end = 0;

        for (size_t i = 0; i < SIZE_FOR_SHELL; i++)
        {
            arr_for_shell[i] = help_var_for_sequence + 12;
            help_var_for_sequence += 12;
        }
        shell(arr_for_shell, SIZE_FOR_SHELL);
        end = clock();
        std::cout << "shell (возрастающая последовательность) время выполнения: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << std::endl;
        help_var_for_sequence = MAS_SIZE;
        end = 0;
        for (size_t i = 0; i < SIZE_FOR_SHELL; i++)
        {
            arr_for_shell[i] = help_var_for_sequence;
            help_var_for_sequence -= 12;
        }
        shell(arr_for_shell, SIZE_FOR_SHELL);
        end = clock();
        std::cout << "shell (убывающая последовательность) время выполнения: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << std::endl;
        help_var_for_sequence = 0;
        end = 0;
        for (size_t i = 0; i < SIZE_FOR_SHELL / 2; i++)
        {
            arr_for_shell[i] = help_var_for_sequence;
            help_var_for_sequence += 12;
        }

        for (size_t i = SIZE_FOR_SHELL / 2; i < SIZE_FOR_SHELL; i++)
        {
            arr_for_shell[i] = help_var_for_sequence;
            help_var_for_sequence -= 12;
        }
        shell(arr_for_shell, SIZE_FOR_SHELL);
        end = clock();
        std::cout << "shell (возрастающая и убывающая последовательность) время выполнения: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << std::endl;

        help_var_for_sequence = 0;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    const size_t SIZE_FOR_QS = 5000;
    {
        std::cout << "размер масисва = " << SIZE_FOR_QS << "  ( > 5000 - error (stack overflow))" << std::endl;;
        int help_var_for_sequence = MAS_SIZE;

        int* arr_for_qs = (int*)malloc(sizeof(int) * SIZE_FOR_QS);
        for (size_t i = 0; i < SIZE_FOR_QS; ++i)
        {
            arr_for_qs[i] = rand() % 10000 + 1;
        }
        start = clock();
        qs(arr_for_qs, 0, SIZE_FOR_QS - 1);
        end = clock();
        std::cout << "qs (случайные числа) время выполнения: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << std::endl;
        end = 0;

        for (size_t i = 0; i < SIZE_FOR_QS; i++)
        {
            arr_for_qs[i] = help_var_for_sequence + 12;
            help_var_for_sequence += 12;
        }
        qs(arr_for_qs, 0, SIZE_FOR_QS - 1);
        end = clock();
        std::cout << "qs (возрастающая последовательность) время выполнения: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << std::endl;
        help_var_for_sequence = 0;
        end = 0;
        for (size_t i = 0; i < SIZE_FOR_QS; i++)
        {
            arr_for_qs[i] = help_var_for_sequence;
            help_var_for_sequence -= 12;
        }
        qs(arr_for_qs, 0, SIZE_FOR_QS - 1);
        end = clock();
        std::cout << "qs (убывающая последовательность) время выполнения: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << std::endl;
        help_var_for_sequence = 0;
        end = 0;
        for (size_t i = 0; i < SIZE_FOR_QS / 2; i++)
        {
            arr_for_qs[i] = help_var_for_sequence;
            help_var_for_sequence += 12;
        }
        for (size_t i = SIZE_FOR_QS / 2; i < SIZE_FOR_QS; i++)
        {
            arr_for_qs[i] = help_var_for_sequence;
            help_var_for_sequence -= 12;
        }
        qs(arr_for_qs, 0, SIZE_FOR_QS - 1);
        end = clock();
        std::cout << "qs (возрастающая и убывающая последовательность) время выполнения: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << std::endl;

        help_var_for_sequence = 0;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    const size_t SIZE_FOR_STANDART_QS = MAS_SIZE;

    {
        std::cout << "размер массива = " << SIZE_FOR_STANDART_QS << std::endl;
        int help_var_for_sequence = MAS_SIZE;

        int* arr_for_standart_qs = (int*)malloc(sizeof(int) * SIZE_FOR_STANDART_QS);
        for (size_t i = 0; i < SIZE_FOR_STANDART_QS; ++i)
        {
            arr_for_standart_qs[i] = rand() % 50 + 1;
        }
        start = clock();
        qsort(arr_for_standart_qs, SIZE_FOR_STANDART_QS, sizeof(int), compare_ints);
        end = clock();
        std::cout << "standard qs (случайные числа) время выполнения: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << std::endl;
        end = 0;
        for (size_t i = 0; i < SIZE_FOR_STANDART_QS; i++)
        {
            arr_for_standart_qs[i] = help_var_for_sequence + 12;
            help_var_for_sequence += 12;
        }
        qsort(arr_for_standart_qs, SIZE_FOR_STANDART_QS, sizeof(int), compare_ints);
        end = clock();
        std::cout << "standard qs (возрастающая последовательность) время выполнения: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << std::endl;
        help_var_for_sequence = 0;
        end = 0;
        for (size_t i = 0; i < SIZE_FOR_STANDART_QS; i++)
        {
            arr_for_standart_qs[i] = help_var_for_sequence;
            help_var_for_sequence -= 12;
        }
        qsort(arr_for_standart_qs, SIZE_FOR_STANDART_QS, sizeof(int), compare_ints);
        end = clock();
        std::cout << "standard qs (убывающая последовательность) время выполнения: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << std::endl;
        help_var_for_sequence = 0;
        end = 0;
        for (size_t i = 0; i < SIZE_FOR_STANDART_QS / 2; i++)
        {
            arr_for_standart_qs[i] = help_var_for_sequence;
            help_var_for_sequence += 12;
        }
        for (size_t i = SIZE_FOR_STANDART_QS / 2; i < SIZE_FOR_STANDART_QS; i++)
        {
            arr_for_standart_qs[i] = help_var_for_sequence;
            help_var_for_sequence -= 12;
        }
        qsort(arr_for_standart_qs, SIZE_FOR_STANDART_QS, sizeof(int), compare_ints);
        end = clock();
        std::cout << "standard qs (возрастающая и убывающая последовательность) время выполнения: " << static_cast<double>(end - start) / CLOCKS_PER_SEC << std::endl;

        help_var_for_sequence = 0;
    }
    return 0;

}
