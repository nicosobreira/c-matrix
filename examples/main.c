#include <stdio.h>

#include "matrix/matrix.h"
#include "matrix/operations.h"
#include "matrix/print.h"

#define M 3
#define N 3
#define P 2

int main(void)
{
    printf("Hello, World!\n");

    int a_data[M][N] = {{1, -2, 3}, {9, -8, 7}, {0, 1, -1}};
    int b_data[N][P] = {{4, 5}, {6, 5}, {4, 6}};

    Matrix a;
    Matrix b;

    Matrix_From(&a, M, N, a_data);
    Matrix_From(&b, N, P, b_data);

    Matrix c;

    MatrixResult result = Matrix_Product(&c, &a, &b);

    if (result == MATRIX_OK)
    {
        Matrix_Print(&c);
    }

    return 0;
}
