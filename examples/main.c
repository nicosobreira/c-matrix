#include <stdio.h>

#include "matrix/decomposition.h"
#include "matrix/matrix.h"
#include "matrix/operations.h"
#include "matrix/print.h"

int main(void)
{
    printf("Hello, World!\n");

    Type a_data[3][3] = {
        {1, 2, 3}, //
        {4, 5, 6}, //
        {7, 8, 9}  //
    };

    Matrix a;

    Matrix_From(&a, 3, 3, a_data);

    Matrix c;

    MatrixResult result = Matrix_TriangularSuperior(&c, &a, NULL);

    if (result == MATRIX_OK)
    {
        Matrix_Print(&c);
    }

    return 0;
}
