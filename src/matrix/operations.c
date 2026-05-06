#include "operations.h"

MatrixResult Matrix_Add(Matrix *result, Matrix *a, Matrix *b)
{
    if (!Matrix_IsSizeEqual(a, b))
    {
        return MATRIX_ERR_DIMENSIONS;
    }

    size_t lines = a->lines;
    size_t columns = a->columns;

    MatrixResult r = Matrix_New(result, lines, columns);

    if (r != MATRIX_OK)
    {
        return r;
    }

    for (size_t i = 0; i < lines; ++i)
    {
        for (size_t j = 0; j < columns; ++j)
        {
            Type value = Matrix_Get(a, i, j) + Matrix_Get(b, i, j);
            Matrix_Set(result, i, j, value);
        }
    }

    return MATRIX_OK;
}

MatrixResult Matrix_Product(Matrix *result, Matrix *a, Matrix *b)
{
    if (a->columns != b->lines)
    {
        return MATRIX_ERR_DIMENSIONS;
    }

    MatrixResult r = Matrix_New(result, a->lines, b->columns);

    if (r != MATRIX_OK)
    {
        return r;
    }

    size_t n = a->columns;

    for (size_t i = 0; i < a->lines; ++i)
    {
        for (size_t j = 0; j < b->columns; ++j)
        {
            Type value = 0;

            for (size_t k = 0; k < n; ++k)
            {
                value += Matrix_Get(a, i, k) * Matrix_Get(b, k, j);
            }

            Matrix_Set(result, i, j, value);
        }
    }
    return MATRIX_OK;
}

MatrixResult Matrix_Inverse(Matrix *self, Matrix *result);

MatrixResult Matrix_Determinant(Matrix *self, int *result)
{
    if (!Matrix_IsSquare(self))
    {
        return MATRIX_ERR_DIMENSIONS;
    }

    size_t n = self->lines;

    if (n == 1)
    {
        *result = Matrix_Get(self, 0, 0);
        return MATRIX_OK;
    }

    if (n == 2)
    {
        Type first = Matrix_Get(self, 0, 0) * Matrix_Get(self, 1, 1);
        Type second = Matrix_Get(self, 0, 1) * Matrix_Get(self, 1, 0);

        *result = first - second;
        return MATRIX_OK;
    }

    if (n == 3)
    {
        // Continue
    }

    return MATRIX_OK;
}
