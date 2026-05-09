#include "determinant.h"

#include "unity.h"

#include "matrix/determinant.h"
#include "matrix/matrix.h"

void test_Matrix_Determinant_NotSquare(void)
{
    Matrix a;

    Matrix_New(&a, 1, 2);

    Type det = 0;
    MatrixResult result = Matrix_Determinant(&a, &det);

    TEST_ASSERT_EQUAL(MATRIX_ERR_DIMENSIONS, result);
}

void test_Matrix_Determinant_1x1(void)
{
    Type expected = 3;

    Type matrix[1][1] = {{expected}};

    Matrix a;
    Matrix_From(&a, 1, 1, matrix);

    Type det = 0;
    MatrixResult result = Matrix_Determinant(&a, &det);

    TEST_ASSERT_EQUAL(MATRIX_OK, result);

    TEST_ASSERT_EQUAL(expected, det);
}

void test_Matrix_Determinant_2x2(void)
{
    Type expected = -21;

    Type matrix[2][2] = {{-2, 1}, {3, 9}};

    Matrix a;
    Matrix_From(&a, 2, 2, matrix);

    Type det = 0;
    MatrixResult result = Matrix_Determinant(&a, &det);

    TEST_ASSERT_EQUAL(MATRIX_OK, result);

    TEST_ASSERT_EQUAL(expected, det);
}

void test_Matrix_Determinant_3x3(void)
{
    Type expected = -12;

    Type matrix[3][3] = {{-4, 2, 1}, {-9, 3, 0}, {5, 1, 2}};

    Matrix a;
    Matrix_From(&a, 3, 3, matrix);

    Type det = 0;
    MatrixResult result = Matrix_Determinant(&a, &det);

    TEST_ASSERT_EQUAL(MATRIX_OK, result);

    TEST_ASSERT_EQUAL(expected, det);
}

void test_matrix_determinant_n(void);
