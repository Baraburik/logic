#include "FirstFunc.h"


struct Node
{
	int data;
	Node* left;
	Node* right;

};

struct Node* root;

struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
	if (r == NULL)
	{
		r = (struct Node*)malloc(sizeof(struct Node));
		if (r == NULL)
		{
			printf("Error allocate memory");
			exit(0);
		}

		r->left = NULL;
		r->right = NULL;
		r->data = data;
		if (root == NULL) return r;

		if (data > root->data)	root->left = r;
		else root->right = r;
		return r;
	}

	if (data > r->data)
		CreateTree(r, r->left, data);
	else
		CreateTree(r, r->right, data);

	return root;
}

void print_tree(struct Node* r, int l)
{

	if (r == NULL)
	{
		return;
	}

	print_tree(r->right, l + 1);
	for (int i = 0; i < l; i++)
	{
		printf(" ");
	}

	printf("%d\n", r->data);
	print_tree(r->left, l + 1);
}

bool find_value(Node* root, int value)
{
	if (!root)
	{
		return false;
	}
	else if (root->data == value)
	{
		return true;
	}

	return find_value(root->right, value) || find_value(root->left, value);
}


int find_count_value(Node* root, int value, int counter = 0)
{

	if (!root)
	{
		return counter;
	}
	else if (root->data == value)
	{
		counter++;
	}
	counter = find_count_value(root->right, value, counter);
	counter = find_count_value(root->left, value, counter);

	return counter;
}


void start()
{
	int D, start = 1;

	root = NULL;
	printf("Заполните дерево (для выхода введите '0')\n");
	while (start)
	{
		printf("Введите число: ");
		scanf_s("%d", &D);
		if (D == 0)
		{
			printf("\nСоздание дерева завершено!\nДерево:\n\n");
			start = 0;
		}
		else
			root = CreateTree(root, root, D);

	}
	print_tree(root, 0);
}


void finder()
{
	printf("Введите число, которое желаете найти: ");
	int value;
	scanf("%d", &value);
	printf("\n");

	if (find_value(root, value))
	{
		printf("Число найдено\n\n");
	}
	else
	{
		printf("Число не найдено\n\n");
	}
}


void counter() 
{
	printf("Введите число, которое желаете найти: ");
	int value;
	scanf("%d", &value);
	printf("\n");

	if (find_value(root, value))
	{
		printf("Чсило входит %d раз\n\n", find_count_value(root, value));
	}
	else
	{
		printf("Число не найдено\n\n");
	}
}