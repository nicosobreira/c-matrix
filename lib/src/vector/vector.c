#include "matrix/vector.h"
#include "matrix/core.h"

#include <stdlib.h>

Type internal_Vector_Get(const Vector *self, size_t i)
{
    return self->data[i];
}

void internal_Vector_Set(Vector *self, size_t i, Type value)
{
    self->data[i] = value;
}

MatrixResult Vector_New(Vector *v, size_t size)
{
    v->data = (Type *)malloc(size * sizeof(Type));

    if (v->data == NULL)
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
        internal_Vector_Set(result, i, internal_Vector_Get(from, i));
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
        internal_Vector_Set(result, i, data[i]);
    }

    return MATRIX_OK;
}
