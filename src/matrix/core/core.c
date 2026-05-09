#include "matrix/core.h"

#include <assert.h>

static bool checkSize(size_t lines, size_t columns)
{
    if (lines == 0 || lines > MATRIX_SIZE)
    {
        return false;
    }

    if (columns == 0 || columns > MATRIX_SIZE)
    {
        return false;
    }

    return true;
}

MatrixResult Matrix_New(Matrix *new, size_t lines, size_t columns)
{
    if (!checkSize(lines, columns))
    {
        return MATRIX_ERR_ALLOCATION;
    }

    new->lines = lines;
    new->columns = columns;

    return MATRIX_OK;
}

MatrixResult Matrix_NewFrom(Matrix *result, Matrix *from)
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
            Matrix_Set(result, i, j, Matrix_Get(from, i, j));
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
            Matrix_Set(new, i, j, data[i][j]);
        }
    }

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
