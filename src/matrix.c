#include "matrix.h"

#include <assert.h>

MatrixStatus Matrix_New(size_t lines, size_t columns, Matrix *new)
{
    if (lines > MATRIX_SIZE || columns > MATRIX_SIZE)
    {
        return MATRIX_ERR_ALLOCATION;
    }

    *new = (Matrix){0};

    new->lines = lines;
    new->columns = columns;

    return MATRIX_OK;
}

MatrixStatus Matrix_Add(Matrix *a, Matrix *b, Matrix *result)
{
    if (!Matrix_IsSizeEqual(a, b))
    {
        return MATRIX_ERR_DIMENSIONS;
    }

    size_t lines = a->lines;
    size_t columns = a->columns;

    MatrixStatus status = Matrix_New(lines, columns, result);

    if (status != MATRIX_OK)
    {
        return status;
    }

    for (size_t i = 0; i < lines; ++i)
    {
        for (size_t j = 0; j < columns; ++j)
        {
            result->data[i][j] = Matrix_Get(a, i, j) + Matrix_Get(b, i, j);
        }
    }

    return MATRIX_OK;
}

MatrixStatus Matrix_Product(Matrix *a, Matrix *b, Matrix *result);

MatrixStatus Matrix_Inverse(Matrix *self, Matrix *result);

MatrixStatus Matrix_Determinant(Matrix *self, int *result);

// ============================================================================

const char *Matrix_GetErrorMsg(MatrixStatus status);
