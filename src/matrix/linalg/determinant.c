#include "matrix/linalg.h"

static inline Type det_1x1(Matrix *self)
{
    return Matrix_Get(self, 0, 0);
}

static inline Type det_2x2(Matrix *self)
{
    Type first = Matrix_Get(self, 0, 0) * Matrix_Get(self, 1, 1);
    Type second = Matrix_Get(self, 0, 1) * Matrix_Get(self, 1, 0);

    return first - second;
}

static inline Type det_3x3(Matrix *self)
{
    Type aei = Matrix_Get(self, 0, 0) * Matrix_Get(self, 1, 1) * Matrix_Get(self, 2, 2);
    Type bfg = Matrix_Get(self, 0, 1) * Matrix_Get(self, 1, 2) * Matrix_Get(self, 2, 0);
    Type cdh = Matrix_Get(self, 0, 2) * Matrix_Get(self, 1, 0) * Matrix_Get(self, 2, 1);

    Type first = aei + bfg + cdh;

    Type ceg = Matrix_Get(self, 0, 2) * Matrix_Get(self, 1, 1) * Matrix_Get(self, 2, 0);
    Type afh = Matrix_Get(self, 0, 0) * Matrix_Get(self, 1, 2) * Matrix_Get(self, 2, 1);
    Type bdi = Matrix_Get(self, 0, 1) * Matrix_Get(self, 1, 0) * Matrix_Get(self, 2, 2);

    Type second = ceg + afh + bdi;

    return first - second;
}

static inline Type det_nxn(Matrix *self)
{
    int line_swaps;
    Matrix triangular;
    Matrix_TriangularSuperior(&triangular, self, &line_swaps);

    Type result = 1;
    for (size_t i = 0; i < triangular.lines; ++i)
    {
        result *= Matrix_Get(&triangular, i, i);
    }

    if (line_swaps % 2 == 1)
    {
        result *= -1;
    }

    return result;
}

MatrixResult Matrix_Determinant(Matrix *self, Type *result)
{
    if (!Matrix_IsSquare(self))
    {
        return MATRIX_ERR_DIMENSIONS;
    }

    size_t n = self->lines;

    switch (n)
    {
    case 1:
        *result = det_1x1(self);
        break;
    case 2:
        *result = det_2x2(self);
        break;
    case 3:
        *result = det_3x3(self);
        break;
    default:
        *result = det_nxn(self);
        break;
    }

    return MATRIX_OK;
}
