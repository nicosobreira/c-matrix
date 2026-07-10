#include "unity.h"

#include "matrix/core.h"
#include "matrix/linalg.h"

#include "unity_internals.h"
#include "utils.h"

void setUp(void)
{
}
void tearDown(void)
{
}

static void test_Matrix_Identity_1x1(void)
{
    Type expected[1][1] = {{1}};

    Matrix i;
    MatrixResult r = Matrix_Identity(&i, 1);
    TEST_ASSERT_EQUAL(MATRIX_OK, r);

    matrix_iter_assert(&i, 1, 1, expected);

    Matrix_Free(&i);
}

static void test_Matrix_Identity_3x3(void)
{
    Type expected[3][3] = {
        {1, 0, 0}, //
        {0, 1, 0}, //
        {0, 0, 1}, //
    };

    Matrix i;
    MatrixResult r = Matrix_Identity(&i, 3);
    TEST_ASSERT_EQUAL(MATRIX_OK, r);

    matrix_iter_assert(&i, 3, 3, expected);

    Matrix_Free(&i);
}

static void test_Matrix_Identity_4x4(void)
{
    Type expected[4][4] = {
        {1, 0, 0, 0}, //
        {0, 1, 0, 0}, //
        {0, 0, 1, 0}, //
        {0, 0, 0, 1}, //
    };

    Matrix i;
    MatrixResult r = Matrix_Identity(&i, 4);
    TEST_ASSERT_EQUAL(MATRIX_OK, r);

    matrix_iter_assert(&i, 4, 4, expected);

    Matrix_Free(&i);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_Matrix_Identity_1x1);
    RUN_TEST(test_Matrix_Identity_3x3);
    RUN_TEST(test_Matrix_Identity_4x4);

    return UNITY_END();
}
