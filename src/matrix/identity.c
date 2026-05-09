#include "identity.h"

static inline void zero_the_matrix(Matrix *self)
{
    for (size_t i = 0; i < self->lines; ++i)
    {
        for (size_t j = 0; j < self->columns; ++j)
        {
            Matrix_Set(self, i, j, 0);
        }
    }
}

MatrixResult Matrix_Identity(Matrix *result, size_t n)
{
    MatrixResult r = Matrix_New(result, n, n);

    if (r != MATRIX_OK)
    {
        return r;
    }

    zero_the_matrix(result);

    for (size_t i = 0; i < result->lines; ++i)
    {
        Matrix_Set(result, i, i, 1);
    }

    return MATRIX_OK;
}
