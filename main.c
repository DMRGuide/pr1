//1142 Караблин Дмитрий pr2
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <conio.h>
#define for_i for(int i = 0; i < r; i++)
void swap(int* a, int* b)
{
	int z = *a;
	*a = *b;
	*b = z;

}
void sort(int r, int* v)
{
	setlocale(LC_ALL, "Rus");
	int q = 0;
	for (int i = 0; i < r; i++)
	{
		for (int j = 1; j < (r - i); j++)
		{

			if (v[j] < v[j - 1])
			{
				swap(&v[j], &v[j - 1]);
			}
			q++;
		}

	}
	printf("Мы сравнили %d раз",q);
}
int main()
{
	setlocale(LC_ALL, "Rus");
	int r;
	printf("Введите размер массива - ");
	scanf("%d", &r);
	int* v = (int*)calloc(r, sizeof(int));
	printf("Массив - ");
	for_i
	{
	v[i] = r - i;
	printf("%d ", v[i]);
	}
	printf("\n");
	sort(r, v);
	printf("Результат сортировки - ");
	for_i
	{
	printf("%d ", v[i]);
	}
	free(v);
}
