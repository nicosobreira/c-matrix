#include "matrix/core.h"

typedef Type (*Operation)(Type x, Type y);

static inline Type add(Type x, Type y)
{
    return x + y;
}

static inline Type subtract(Type x, Type y)
{
    return x - y;
}

static inline Type product(Type x, Type y)
{
    return x * y;
}

static inline MatrixResult Matrix_Operation(Matrix *result, const Matrix *a, const Matrix *b, Operation func)
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
            Type value = func(Matrix_Get(a, i, j), Matrix_Get(b, i, j));
            Matrix_Set(result, i, j, value);
        }
    }

    return MATRIX_OK;
}

static inline MatrixResult Matrix_OperationBy(Matrix *result, const Matrix *self, Type value, Operation func)
{
    MatrixResult r = Matrix_New(result, self->lines, self->columns);

    if (r != MATRIX_OK)
    {
        return r;
    }

    for (size_t i = 0; i < result->lines; ++i)
    {
        for (size_t j = 0; j < result->columns; ++j)
        {
            Type new = func(value, Matrix_Get(self, i, j));

            Matrix_Set(result, i, j, new);
        }
    }

    return MATRIX_OK;
}

MatrixResult Matrix_Add(Matrix *result, const Matrix *a, const Matrix *b)
{
    return Matrix_Operation(result, a, b, add);
}

MatrixResult Matrix_AddBy(Matrix *result, const Matrix *self, Type value)
{
    return Matrix_OperationBy(result, self, value, add);
}

MatrixResult Matrix_Subtract(Matrix *result, const Matrix *a, const Matrix *b)
{
    return Matrix_Operation(result, a, b, subtract);
}

MatrixResult Matrix_SubtractBy(Matrix *result, const Matrix *self, Type value)
{
    return Matrix_OperationBy(result, self, value, subtract);
}

MatrixResult Matrix_Product(Matrix *result, const Matrix *a, const Matrix *b)
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

MatrixResult Matrix_ProductBy(Matrix *result, const Matrix *self, Type scalar)
{
    return Matrix_OperationBy(result, self, scalar, product);
}
