#include "inverse.h"

#include "unity.h"

#include "matrix/decomposition.h"
#include "matrix/identity.h"
#include "matrix/matrix.h"

#include "utils.h"

void test_Matrix_Inverse_2x2(void)
{
    Type original[2][2] = {{4, 7}, {2, 6}};
    Type expected[2][2] = {{0.6, -0.7}, {-0.2, 0.4}};

    Matrix a, inverse;

    Matrix_From(&a, 2, 2, original);

    MatrixResult r = Matrix_Inverse(&inverse, &a);

    TEST_ASSERT_EQUAL(MATRIX_OK, r);

    matrix_iter_assert(&inverse, 2, 2, expected);
}

void test_Matrix_Inverse_WithLineSwap(void)
{
    Type original[2][2] = {{0, 2}, {1, 3}};
    Type expected[2][2] = {{-1.5, 1}, {0.5, 0}};

    Matrix a, inverse;

    Matrix_From(&a, 2, 2, original);

    MatrixResult r = Matrix_Inverse(&inverse, &a);

    TEST_ASSERT_EQUAL(MATRIX_OK, r);

    matrix_iter_assert(&inverse, 2, 2, expected);
}

void test_Matrix_Inverse_NotInvertible(void)
{
    Type data[2][2] = {{1, 2}, {2, 4}};

    Matrix a, inverse;

    Matrix_From(&a, 2, 2, data);

    MatrixResult r = Matrix_Inverse(&inverse, &a);

    TEST_ASSERT_EQUAL(MATRIX_ERR_NOT_INVERTIBLE, r);
}

void test_Matrix_Inverse_NotSquare(void)
{
    Matrix a;
    Matrix_New(&a, 1, 4);

    Matrix inverse;
    MatrixResult r = Matrix_Inverse(&inverse, &a);

    TEST_ASSERT_EQUAL(MATRIX_ERR_DIMENSIONS, r);
}

void test_Matrix_Inverse_Identity(void)
{
    Type data[3][3] = {
        {1, 0, 0}, //
        {0, 1, 0}, //
        {0, 0, 1}, //
    };

    Matrix a, inverse;

    Matrix_From(&a, 3, 3, data);

    MatrixResult r = Matrix_Inverse(&inverse, &a);

    TEST_ASSERT_EQUAL(MATRIX_OK, r);

    matrix_iter_assert(&inverse, 3, 3, data);
}
