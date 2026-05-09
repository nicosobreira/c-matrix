#pragma once

#include "unity.h"

#include "matrix/matrix.h"

static inline void matrix_iter_assert(Matrix *a, size_t l, size_t c, Type b[l][c])
{
    for (size_t i = 0; i < l; ++i)
    {
        for (size_t j = 0; j < c; ++j)
        {
            TEST_ASSERT_EQUAL(b[i][j], Matrix_Get(a, i, j));
        }
    }
}
