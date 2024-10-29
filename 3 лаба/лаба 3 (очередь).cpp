#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <limits>

struct node
{
	char inf[256];
	struct node* next;
};


struct node* head = NULL, * last = NULL, * f = NULL; // указатели на первый и последний элементы списка
int dlinna = 0;

void spstore(void), review(void), del(char* name);

char find_el[256];
struct node* find(char* name); // функция нахождения элемента
struct node* get_struct(void); // функция создания элемента



struct node* get_struct(void)
{
	struct node* p = NULL;
	char s[256];

	if ((p = (node*)malloc(sizeof(struct node))) == NULL)  // выделяем память под новый элемент списка
	{
		printf("Ошибка при распределении памяти\n");
		exit(1);
	}

	printf("Введите название объекта: \n");   // вводим данные
	scanf("%s", s);
	if (*s == 0)
	{
		printf("Запись не была произведена\n");
		return NULL;
	}
	strcpy(p->inf, s);

	p->next = NULL;

	return p;		// возвращаем указатель на созданный элемент
}

/* Последовательное добавление в список элемента (в конец)*/
void spstore(void)
{
	struct node* p = NULL;
	p = get_struct();
	if (head == NULL && p != NULL)	// если списка нет, то устанавливаем голову списка
	{
		head = p;
		last = p;
	}
	else if (head != NULL && p != NULL)
	{
		p->next = head;
		head = p;
	}
	return;
}


/* Просмотр содержимого списка. */
void review(void)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		printf("Имя - %s, \n", struc->inf);
		struc = struc->next;
	}
	return;
}




/* Поиск элемента по содержимому. */
struct node* find(char* name)
{
	struct node* struc = head;
	if (head == NULL)
	{
		printf("Список пуст\n");
	}
	while (struc)
	{
		if (strcmp(name, struc->inf) == 0)
		{
			return struc;
		}
		struc = struc->next;
	}
	printf("Элемент не найден\n");
	return NULL;
}

/* Удаление элемента по содержимому. */
void del(char* name)
{
	struct node* struc = head;
	struct node* temp;
	int flag = 0;

	if (head == NULL)
	{
		printf("Список пуст\n");
		return;
	}

	if (strcmp(name, struc->inf) == 0)
	{
		flag = 1;
		temp = struc;
		head = struc->next;
		free(temp);
		return;
	}

	while (struc->next)
	{
		if (strcmp(name, struc->next->inf) == 0)
		{
			flag = 1;
			temp = struc->next;
			struc->next = struc->next->next;
			free(temp);
			return;
		}
		struc = struc->next;
	}

	if (flag == 0)
	{
		printf("Элемент не найден\n");
		return;
	}
}


struct node* pop() {
	if (!head) {
		return nullptr;
	}

	if (!head->next) {
		node* temp = head;
		head = nullptr;
		return temp;
	}

	node* temp = head;
	while (temp->next->next != nullptr) {
		temp = temp->next;
	}

	node* last = temp->next;
	temp->next = nullptr;
	return last;
}

void print_queue() {
	struct node* struc = head;
	if (head == NULL) {
		printf("Очередь пуста\n");
	}
	else {
		printf("Содержимое очереди:\n");
		while (struc) {
			printf("Имя - %s, \n", struc->inf);
			struc = struc->next;
		}
	}
}

void queue()
{
	while (true)
	{
		printf("Выберите предложенное действие!\n");
		printf("1 - Добавление элемента\n");
		printf("2 - Извлечение элемента\n");
		printf("3 - Вывод элементов\n");
		printf("4 - Выход\n");
		printf("Введите номер выбранного действия: ");

		int choice;
		scanf("%d", &choice);

		printf("\n");

		if (choice == 1)
		{
			spstore();
		}
		else if (choice == 2)
		{
			struct node* popped = pop();
			if (popped == nullptr)
			{
				printf("Очередь пуста\n\n");
			}
			else
			{
				printf("Последний элемент удален. Имя удаленного элемента - ", popped->inf, "\n");
			}
		}
		else if (choice == 3)
		{
			print_queue();
		}
		else if (choice == 4)
		{
			return;
		}
		else
		{
			printf("Некорректная операция\n\n");
		}

	}
}

int main()
{
	setlocale(LC_ALL, "RUS");
	queue();
	exit(0);
}