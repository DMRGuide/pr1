//1142 Караблин Дмитрий pr2
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#define N 9
#define M 9
void prop1(int A[N][M])
{
	srand(time(0));
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
		{
			A[i][j] = rand() % 2 ? 0 : rand() % 2;
			A[i][0] = 1;
			A[i][M - 1] = 1;
			A[0][j] = 1;
			A[N - 1][j] = 1;
		}
}
void prop2(int A[N][M])
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
			printf("%d", A[i][j]);
		printf("\n");
	}

}
void prop3(int A[N][M], int x, int i, int j)
{


	if (i < N && j < M)
	{
		if (A[i][j] == 0)
		{
			A[i][j] = x;
			prop3(A, x, i, j + 1);
			prop3(A, x, i, j - 1);
			prop3(A, x, i - 1, j);
			prop3(A, x, i + 1, j);
		}
		else if (A[i][j] == 1)
		{
			return;
		}
	}
}
int main()
{
	setlocale(LC_ALL, "Rus");
	int A[N][M];
	int x;
	int i;
	int j;
	printf("Создан массив:\n");
	prop1(A);
	prop2(A);
	printf("Введите число заливки:");
	scanf("%d", &x);
	printf("Введите первую координату для массива:");
	scanf("%d", &i);
	printf("Введите вторую координату для массива:");
	scanf("%d", &j);
	printf("Массив:\n");
	prop3(A, x, i, j);
	prop2(A);
	getchar();
}
