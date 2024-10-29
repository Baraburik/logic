#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <locale.h>

struct node {
    char* data;
    uint32_t priority;
    struct node* next;
    struct node* prev;
};

struct priority_queue {
    struct node* head;
    struct node* tail;
    uint32_t max_prior;
};

struct node* create_node(const char* str, uint32_t prior) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (!new_node) {
        fprintf(stderr, "Ошибка при распределении памяти\n");
        exit(EXIT_FAILURE);
    }

    new_node->data = (char*)malloc(strlen(str) + 1);
    if (!new_node->data) {
        fprintf(stderr, "Ошибка при распределении памяти\n");
        free(new_node);
        exit(EXIT_FAILURE);
    }
    strcpy(new_node->data, str);
    new_node->priority = prior;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

void delete_node(struct node* n) {
    free(n->data);
    free(n);
}


void info_for_node(struct node* temp) {
    printf("Содержимое: %s  ", temp->data);
    printf("Приоритет: %u\n", temp->priority);
}

struct priority_queue* create_priority_queue() {
    struct priority_queue* pq = (struct priority_queue*)malloc(sizeof(struct priority_queue));
    if (!pq) {
        fprintf(stderr, "Ошибка при распределении памяти\n");
        exit(EXIT_FAILURE);
    }
    
    pq->head = NULL;
    pq->tail = NULL;
    pq->max_prior = 0;
    return pq;
}

void append(struct priority_queue* pq, struct node* new_node) {
    if (!pq->head) {
        pq->head = pq->tail = new_node;
        pq->max_prior = new_node->priority;
        return;
    }

    struct node* temp = pq->head;
    while (temp != NULL && new_node->priority >= temp->priority) {
        temp = temp->next;
    }

    if (temp == pq->head) {
        new_node->next = pq->head;
        pq->head->prev = new_node;
        pq->head = new_node;
    }
    else if (!temp) {
        pq->tail->next = new_node;
        new_node->prev = pq->tail;
        pq->tail = new_node;
    }
    else {
        new_node->next = temp;
        new_node->prev = temp->prev;
        if (temp->prev) {
            temp->prev->next = new_node;
        }
        temp->prev = new_node;
    }

    if (new_node->priority > pq->max_prior) {
        pq->max_prior = new_node->priority;
    }
}

struct node* pop(struct priority_queue* pq) {
    if (!pq->tail) return NULL;

    struct node* temp = pq->tail;

    if (pq->head == pq->tail) {
        pq->head = NULL;
        pq->tail = NULL;
    }
    else {
        pq->tail = pq->tail->prev;
        pq->tail->next = NULL;
    }

    temp->prev = NULL;
    return temp;
}

void print_all(const struct priority_queue* pq) {
    if (!pq->head) {
        printf("Очередь пуста\n\n");
        return;
    }
    struct node* temp = pq->head;
    printf("Список:\n\n");
    while (temp != NULL) {
        info_for_node(temp);
        temp = temp->next;
    }
    printf("\n");
}

void search(const struct priority_queue* pq, const char* target) {
    struct node* temp = pq->head;
    while (temp != NULL) {
        if (strcmp(temp->data, target) == 0) {
            free(temp->data);
            temp = temp->next;
            return;
        }
        temp = temp->next;
    }
    printf("Элемент '%s' не найден.\n\n", target);
}

void remove(struct priority_queue* pq, const char* target) {
    struct node* temp = pq->head;
    int found = 0;

    while (temp != NULL) {
        struct node* next = temp->next;  
        if (strcmp(temp->data, target) == 0) {
            found = 1;

            if (temp == pq->head) {
                pq->head = temp->next;
                if (pq->head) {
                    pq->head->prev = NULL;
                }
                else {
                    pq->tail = NULL;  
                }
            }
            else if (temp == pq->tail) {
                pq->tail = temp->prev;
                pq->tail->next = NULL;
            }
            else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }

            delete_node(temp);
        }
        temp = next;  
    }

    if (found) {
        printf("Элементы с названием '%s' удалены.\n", target);
    }
    else {
        printf("Элементы с названием '%s' не найдены.\n", target);
    }
}


void start() {
    struct priority_queue* pr_q = create_priority_queue();

    while (1) {
        printf("Выберите действие:\n");
        printf("1 - Добавление элемента\n");
        printf("2 - Удаление последнего элемента\n");
        printf("3 - Просмотр содержимого списка\n");
        printf("4 - Удаление элемента по названию\n");
        printf("5 - Выход\n");
        printf("Введите номер выбранного действия: ");

        uint16_t choice;
        if (scanf("%hu", &choice) != 1) {
            fprintf(stderr, "Введено некорректное значение, попробуйте снова!\n");
            while (getchar() != '\n');
            continue;
        }

        getchar();

        switch (choice) {
        case 1: {
            while (1) {
                char buffer[256];
                printf("Введите данные (для завершения введите '-'): ");
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;

                if (strcmp(buffer, "-") == 0) break;

                uint32_t prior;
                printf("Укажите приоритет: ");
                scanf("%u", &prior);
                if (prior > 1000)
                {
                    fprintf(stderr, "Некорретное значие!\n");
                    while (getchar() != '\n');
                    continue;
                }
                getchar();
                struct node* new_node = create_node(buffer, prior);
                append(pr_q, new_node);
            }
            break;
        }
        case 2: {
            struct node* popped = pop(pr_q);
            if (popped) {
                printf("Список:\n");
                info_for_node(popped);
                delete_node(popped);
            }
            else {
                printf("Очередь пуста.\n\n");
            }
            break;
        }
        case 3:
            print_all(pr_q);
            break;
        case 4: {
            char buffer[256];
            printf("Введите данные для удаления: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            remove(pr_q, buffer);
            break;
        }

        case 5:
            printf("\nДо свидания!\n");
            while (pr_q->head) {
                delete_node(pop(pr_q));
            }
            free(pr_q);
            return;
        default:
            fprintf(stderr, "Введено некорректное значение, попробуйте снова!\n");
            break;
        }
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    start();
    return 0;
}