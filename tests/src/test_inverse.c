#include "unity.h"

#include "matrix/core.h"
#include "matrix/linalg.h"

#include "utils.h"

void setUp(void)
{
}
void tearDown(void)
{
}

static void test_Matrix_Inverse_2x2(void)
{
    Type original[2][2] = {{4, 7}, {2, 6}};
    Type expected[2][2] = {{0.6, -0.7}, {-0.2, 0.4}};

    Matrix a, inverse;

    Matrix_Load(&a, 2, 2, original);

    MatrixResult r = Matrix_Inverse(&inverse, &a);

    TEST_ASSERT_EQUAL(MATRIX_OK, r);

    matrix_iter_assert(&inverse, 2, 2, expected);

    Matrix_Free(&a);
    Matrix_Free(&inverse);
}

static void test_Matrix_Inverse_WithLineSwap(void)
{
    Type original[2][2] = {{0, 2}, {1, 3}};
    Type expected[2][2] = {{-1.5, 1}, {0.5, 0}};

    Matrix a, inverse;

    Matrix_Load(&a, 2, 2, original);

    MatrixResult r = Matrix_Inverse(&inverse, &a);

    TEST_ASSERT_EQUAL(MATRIX_OK, r);

    matrix_iter_assert(&inverse, 2, 2, expected);

    Matrix_Free(&a);
    Matrix_Free(&inverse);
}

static void test_Matrix_Inverse_NotInvertible(void)
{
    Type data[2][2] = {{1, 2}, {2, 4}};

    Matrix a, inverse;

    Matrix_Load(&a, 2, 2, data);

    MatrixResult r = Matrix_Inverse(&inverse, &a);

    TEST_ASSERT_EQUAL(MATRIX_ERR_NOT_INVERTIBLE, r);

    Matrix_Free(&a);
    Matrix_Free(&inverse);
}

static void test_Matrix_Inverse_NotSquare(void)
{
    Matrix a;
    Matrix_New(&a, 1, 4);

    Matrix inverse;
    MatrixResult r = Matrix_Inverse(&inverse, &a);

    TEST_ASSERT_EQUAL(MATRIX_ERR_DIMENSIONS, r);

    Matrix_Free(&a);
    Matrix_Free(&inverse);
}

static void test_Matrix_Inverse_Identity(void)
{
    Type data[3][3] = {
        {1, 0, 0}, //
        {0, 1, 0}, //
        {0, 0, 1}, //
    };

    Matrix a, inverse;

    Matrix_Load(&a, 3, 3, data);

    MatrixResult r = Matrix_Inverse(&inverse, &a);

    TEST_ASSERT_EQUAL(MATRIX_OK, r);

    matrix_iter_assert(&inverse, 3, 3, data);

    Matrix_Free(&a);
    Matrix_Free(&inverse);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_Matrix_Inverse_2x2);
    RUN_TEST(test_Matrix_Inverse_WithLineSwap);
    RUN_TEST(test_Matrix_Inverse_NotInvertible);
    RUN_TEST(test_Matrix_Inverse_NotSquare);
    RUN_TEST(test_Matrix_Inverse_Identity);

    return UNITY_END();
}
