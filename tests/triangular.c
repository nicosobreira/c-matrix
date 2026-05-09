#include "triangular.h"

#include "unity.h"

#include "matrix/decomposition.h"

#include "utils.h"

void test_Matrix_TriangularSuperior_NullSwap(void)
{
    Matrix original;
    Matrix_New(&original, 2, 2);

    Matrix triangular;
    MatrixResult r = Matrix_TriangularSuperior(&triangular, &original, NULL);

    TEST_ASSERT_EQUAL(MATRIX_OK, r);
}

void test_Matrix_TriangularSuperior_WithoutSwap(void)
{
    Type original_data[2][2] = {{2, 4}, {1, 5}};

    Matrix original;
    Matrix_From(&original, 2, 2, original_data);

    int line_swaps;
    Matrix triangular;
    MatrixResult r = Matrix_TriangularSuperior(&triangular, &original, &line_swaps);

    TEST_ASSERT_EQUAL(MATRIX_OK, r);
    TEST_ASSERT_EQUAL(0, line_swaps);
}

void test_Matrix_TriangularSuperior_WithSwap(void)
{
    Type original_data[2][2] = {{0, 1}, {2, 3}};

    Matrix original;
    Matrix_From(&original, 2, 2, original_data);

    int line_swaps;
    Matrix triangular;
    MatrixResult r = Matrix_TriangularSuperior(&triangular, &original, &line_swaps);

    TEST_ASSERT_EQUAL(MATRIX_OK, r);
    TEST_ASSERT_EQUAL(1, line_swaps);
}

void test_Matrix_TriangularSuperior_NotSquare(void)
{
    Matrix original;
    Matrix_New(&original, 1, 5);

    Matrix triangular;
    MatrixResult r = Matrix_TriangularSuperior(&triangular, &original, NULL);

    TEST_ASSERT_EQUAL(MATRIX_ERR_DIMENSIONS, r);
}

void test_Matrix_TriangularSuperior_Correctness(void)
{
    Type original_data[3][3] = {
        {1, 2, 3}, //
        {4, 5, 6}, //
        {7, 8, 9}, //
    };

    Type expected_data[3][3] = {
        {1, 2, 3},   //
        {0, -3, -6}, //
        {0, 0, 0},   //
    };

    Matrix original;
    Matrix_From(&original, 3, 3, original_data);

    Matrix triangular;
    MatrixResult r = Matrix_TriangularSuperior(&triangular, &original, NULL);

    TEST_ASSERT_EQUAL(MATRIX_OK, r);

    matrix_iter_assert(&triangular, 3, 3, expected_data);
}

void test_Matrix_TriangularSuperior_DoNothing(void)
{
    Type original_data[3][3] = {
        {3, 4, 2}, //
        {0, 0, 0}, //
        {0, 0, 3}, //
    };

    Matrix original;
    Matrix_From(&original, 3, 3, original_data);

    Matrix triangular;
    MatrixResult r = Matrix_TriangularSuperior(&triangular, &original, NULL);

    TEST_ASSERT_EQUAL(MATRIX_OK, r);

    matrix_iter_assert(&triangular, 3, 3, original_data);
}
