//1142 Караблин Дмитрий pr1
#include <stdio.h>
#include <stdlib.h>
#define N 5
#define M 5
int main()
{
    int A[N][M];
    srand(time(NULL));
    {
        for (int i = 0; i < N; i++) 
        {
            for (int j = 0; j < M; j++)
            {
                A[i][0] = 1;
                A[i][4] = 1;
                A[0][j] = 1;
                A[4][j] = 1;
                A[1][1] = rand()%2;
                A[2][1] = rand()%2;
                A[3][1] = rand()%2;
                A[1][2] = rand()%2;
                A[2][2] = rand()%2;
                A[3][2] = rand()%2;
                A[1][3] = rand()%2;
                A[2][3] = rand()%2;
                A[3][3] = rand()%2; 
                printf("%d",A[i][j]);
            }
            printf("\n");
        }
    }
    getchar();
}
