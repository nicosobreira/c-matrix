#include "matrix/core.h"
#include "matrix/linalg.h"

#include "../internal.h"

static inline Type det_1x1(const Matrix *self)
{
    return internal_Matrix_Get(self, 0, 0);
}

static inline Type det_2x2(const Matrix *self)
{
    const Type first = internal_Matrix_Get(self, 0, 0) * internal_Matrix_Get(self, 1, 1);
    const Type second = internal_Matrix_Get(self, 0, 1) * internal_Matrix_Get(self, 1, 0);

    return first - second;
}

static inline Type det_3x3(const Matrix *self)
{
    const Type aei =
        internal_Matrix_Get(self, 0, 0) * internal_Matrix_Get(self, 1, 1) * internal_Matrix_Get(self, 2, 2);
    const Type bfg =
        internal_Matrix_Get(self, 0, 1) * internal_Matrix_Get(self, 1, 2) * internal_Matrix_Get(self, 2, 0);
    const Type cdh =
        internal_Matrix_Get(self, 0, 2) * internal_Matrix_Get(self, 1, 0) * internal_Matrix_Get(self, 2, 1);

    const Type first = aei + bfg + cdh;

    const Type ceg =
        internal_Matrix_Get(self, 0, 2) * internal_Matrix_Get(self, 1, 1) * internal_Matrix_Get(self, 2, 0);
    const Type afh =
        internal_Matrix_Get(self, 0, 0) * internal_Matrix_Get(self, 1, 2) * internal_Matrix_Get(self, 2, 1);
    const Type bdi =
        internal_Matrix_Get(self, 0, 1) * internal_Matrix_Get(self, 1, 0) * internal_Matrix_Get(self, 2, 2);

    const Type second = ceg + afh + bdi;

    return first - second;
}

static inline MatrixResult det_nxn(const Matrix *self, Type *det)
{
    int line_swaps;
    Matrix triangular;
    MatrixResult r = Matrix_TriangularSuperior(&triangular, self, &line_swaps);
    if (r != MATRIX_OK)
    {
        return r;
    }

    Type result = 1;
    for (size_t i = 0; i < triangular.lines; ++i)
    {
        result *= internal_Matrix_Get(&triangular, i, i);
    }

    if (line_swaps % 2 == 1)
    {
        result *= -1;
    }

    *det = result;

    return MATRIX_OK;
}

MatrixResult Matrix_Determinant(const Matrix *self, Type *result)
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
    default: {
        MatrixResult r = det_nxn(self, result);
        return r;
    }
    }

    return MATRIX_OK;
}
