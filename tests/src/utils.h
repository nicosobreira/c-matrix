#pragma once

#include "unity.h"

#include "matrix/core.h"

static inline void matrix_iter_assert(Matrix *a, size_t l, size_t c, Type b[l][c])
{
    TEST_ASSERT_EQUAL_size_t(l, a->lines);
    TEST_ASSERT_EQUAL_size_t(c, a->columns);

    for (size_t i = 0; i < l; ++i)
    {
        for (size_t j = 0; j < c; ++j)
        {
            Type value;
            MatrixResult r = Matrix_Get(a, i, j, &value);
            TEST_ASSERT_EQUAL(MATRIX_OK, r);

            TEST_ASSERT_EQUAL(b[i][j], value);
        }
    }
}
