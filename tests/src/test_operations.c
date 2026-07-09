#include "unity.h"

#include "matrix/core.h"

#include "utils.h"

void setUp(void)
{
}
void tearDown(void)
{
}

static void test_Matrix_Add_DiferentSizes(void)
{
    Matrix a;
    Matrix b;

    Matrix_New(&a, 4, 4);
    Matrix_New(&b, 2, 2);

    Matrix r;

    MatrixResult result = Matrix_Add(&r, &a, &b);

    Matrix_Free(&a);
    Matrix_Free(&b);
    Matrix_Free(&r);

    TEST_ASSERT_EQUAL(MATRIX_ERR_DIMENSIONS, result);
}

static void test_Matrix_Add_Correctness(void)
{
#define N 2

    Type a_data[N][N] = {{1, 2}, {3, 4}};
    Type b_data[N][N] = {{0, -1}, {3, 5}};
    Type c_data[N][N] = {{1, 1}, {6, 9}};

    Matrix a;
    Matrix b;

    Matrix_Load(&a, N, N, a_data);
    Matrix_Load(&b, N, N, b_data);

    Matrix r;

    Matrix_Add(&r, &a, &b);

    matrix_iter_assert(&r, N, N, c_data);

    Matrix_Free(&a);
    Matrix_Free(&b);
    Matrix_Free(&r);
#undef N
}

static void test_Matrix_Product_WrongDimensions(void)
{
    Matrix a;
    Matrix b;

    Matrix_New(&a, 1, 4);
    Matrix_New(&b, 2, 2);

    Matrix r;

    MatrixResult result = Matrix_Product(&r, &a, &b);

    Matrix_Free(&a);
    Matrix_Free(&b);
    Matrix_Free(&r);

    TEST_ASSERT_EQUAL(MATRIX_ERR_DIMENSIONS, result);
}

static void test_Matrix_Product_Correctness(void)
{
#define M 3
#define N 3
#define P 2

    Type a_data[M][N] = {{1, -2, 3}, {9, -8, 7}, {0, 1, -1}};
    Type b_data[N][P] = {{4, 5}, {6, 5}, {4, 6}};

    Type c_data[M][P] = {{4, 13}, {16, 47}, {2, -1}};

    Matrix a;
    Matrix b;

    Matrix_Load(&a, M, N, a_data);
    Matrix_Load(&b, N, P, b_data);

    Matrix c;

    MatrixResult result = Matrix_Product(&c, &a, &b);

    TEST_ASSERT_EQUAL(MATRIX_OK, result);

    matrix_iter_assert(&c, M, P, c_data);

    Matrix_Free(&a);
    Matrix_Free(&b);
    Matrix_Free(&c);

#undef M
#undef N
#undef P
}

static void test_Matrix_Product_CorrectnessVector(void)
{
#define M 3
#define N 3
#define P 1

    Type a_data[M][N] = {{1, -2, 3}, {9, -8, 7}, {0, 1, -1}};
    Type b_data[N][P] = {{4}, {6}, {-2}};

    Type p_data[M][P] = {{-14}, {-26}, {8}};

    Matrix a;
    Matrix b;

    Matrix_Load(&a, M, N, a_data);
    Matrix_Load(&b, N, P, b_data);

    Matrix product;

    MatrixResult result = Matrix_Product(&product, &a, &b);

    TEST_ASSERT_EQUAL(MATRIX_OK, result);

    matrix_iter_assert(&product, M, P, p_data);

    Matrix_Free(&a);
    Matrix_Free(&b);
    Matrix_Free(&product);

#undef M
#undef N
#undef P
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_Matrix_Add_DiferentSizes);
    RUN_TEST(test_Matrix_Add_Correctness);
    RUN_TEST(test_Matrix_Product_WrongDimensions);
    RUN_TEST(test_Matrix_Product_Correctness);
    RUN_TEST(test_Matrix_Product_CorrectnessVector);

    return UNITY_END();
}
