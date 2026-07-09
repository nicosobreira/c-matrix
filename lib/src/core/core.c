#include "matrix/core.h"

#include <stdlib.h>

#include "../internal.h"

MatrixResult Matrix_New(Matrix *new, size_t lines, size_t columns)
{
    const size_t size = lines * columns;

    new->data = (Type *)malloc(size * sizeof(Type));

    if (new->data == NULL)
    {
        Matrix_Free(new);

        return MATRIX_ERR_ALLOCATION;
    }

    new->lines = lines;
    new->columns = columns;

    return MATRIX_OK;
}

MatrixResult Matrix_Free(Matrix *self)
{
    if (self->data != NULL)
    {
        free(self->data);
    }

    *self = (Matrix){0};

    return MATRIX_OK;
}

MatrixResult Matrix_NewFrom(Matrix *result, const Matrix *from)
{
    MatrixResult r = Matrix_New(result, from->lines, from->columns);

    if (r != MATRIX_OK)
    {
        return r;
    }

    for (size_t i = 0; i < from->lines; ++i)
    {
        for (size_t j = 0; j < from->columns; ++j)
        {
            internal_Matrix_Set(result, i, j, internal_Matrix_Get(from, i, j));
        }
    }

    return MATRIX_OK;
}

MatrixResult Matrix_Load(Matrix *new, size_t lines, size_t columns, Type data[lines][columns])
{
    MatrixResult r = Matrix_New(new, lines, columns);

    if (r != MATRIX_OK)
    {
        return r;
    }

    for (size_t i = 0; i < lines; ++i)
    {
        for (size_t j = 0; j < columns; ++j)
        {
            internal_Matrix_Set(new, i, j, data[i][j]);
        }
    }

    return MATRIX_OK;
}

MatrixResult Matrix_Get(const Matrix *self, size_t i, size_t j, Type *variable)
{
    if (i >= self->lines || j >= self->columns)
    {
        return MATRIX_ERR_OUT_OF_BOUNDS;
    }

    *variable = internal_Matrix_Get(self, i, j);

    return MATRIX_OK;
}

MatrixResult Matrix_Set(Matrix *self, size_t i, size_t j, Type value)
{
    if (i >= self->lines || j >= self->columns)
    {
        return MATRIX_ERR_OUT_OF_BOUNDS;
    }

    internal_Matrix_Set(self, i, j, value);

    return MATRIX_OK;
}
const char *Matrix_GetErrorMsg(MatrixResult result)
{
#define X(enum_name, error_string) \
    case enum_name:                \
        return error_string;

    switch (result)
    {
        MATRIX_ERRORS(X)
    }
#undef X

    return "";
}
