//1142 Караблин Дмитрий pr4
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <conio.h>
typedef struct
{
	int val;
	int pos;
}pair;
void PrintStr(int n, pair* arr)
{
	for (int i = 0; i < n; i++)
	{

		printf("%d ", arr[i].val);		
	}
    printf("\n");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i].pos);
	}
	printf("\n");
}
void swap(int n, pair* arr)
{
	int g;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)




		{
			if (arr[i].val < arr[j].val)
			{
				g = arr[i].val;
				arr[i].val = arr[j].val;
				arr[j].val = g;
				g = arr[i].pos;
				arr[i].pos = arr[j].pos;
				arr[j].pos = g;
			}
		}
	}
}
int main()
{
	int n = 10;
	pair* arr = (pair*)malloc(n * sizeof(pair));
	arr[0].val = 6;
	arr[0].pos = 0;
	arr[1].val = 2;
	arr[1].pos = 1;
	arr[2].val = 5;
	arr[2].pos = 2;
	arr[3].val = 4;
	arr[3].pos = 3;
	arr[4].val = 1;
	arr[4].pos = 4;
	arr[5].val = 2;
	arr[5].pos = 5;
	arr[6].val = 0;
	arr[6].pos = 6;
	arr[7].val = 2;
	arr[7].pos = 7;
	arr[8].val = 6;
	arr[8].pos = 8;
	arr[9].val = 3;
	arr[9].pos = 9;
	PrintStr(n, arr);
	swap(n, arr);
	printf("\n\n");
	PrintStr(n, arr);
	getchar();
	free(arr);
}
