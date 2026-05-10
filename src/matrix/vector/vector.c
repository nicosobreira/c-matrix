#include "matrix/vector.h"

MatrixResult Vector_New(Vector *v, size_t size)
{
    if (size == 0 || size > MATRIX_SIZE)
    {
        return MATRIX_ERR_ALLOCATION;
    }

    v->size = size;

    return MATRIX_OK;
}

MatrixResult Vector_Clone(Vector *result, const Vector *from)
{
    MatrixResult r = Vector_New(result, from->size);
    if (r != MATRIX_OK)
    {
        return MATRIX_ERR_ALLOCATION;
    }

    for (size_t i = 0; i < result->size; ++i)
    {
        Vector_Set(result, i, Vector_Get(from, i));
    }

    return MATRIX_OK;
}

MatrixResult Vector_Load(Vector *result, size_t size, Type data[size])
{
    MatrixResult r = Vector_New(result, size);
    if (r != MATRIX_OK)
    {
        return MATRIX_ERR_ALLOCATION;
    }

    for (size_t i = 0; i < result->size; ++i)
    {
        Vector_Set(result, i, data[i]);
    }

    return MATRIX_OK;
}
