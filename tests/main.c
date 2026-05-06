#include "unity.h"

#include "matrix/matrix.h"
#include "matrix/operations.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_matrix_new_allocation_overflow(void)
{
    Matrix a;

    MatrixResult result = Matrix_New(&a, MATRIX_SIZE + 1, 1);

    TEST_ASSERT_EQUAL(result, MATRIX_ERR_ALLOCATION);
}

void test_matrix_new_allocation_zero(void)
{
    Matrix a;

    MatrixResult result = Matrix_New(&a, 0, 1);

    TEST_ASSERT_EQUAL(result, MATRIX_ERR_ALLOCATION);
}

void test_matrix_add_diferent_sizes(void)
{
    Matrix a;
    Matrix b;

    Matrix_New(&a, 4, 4);
    Matrix_New(&b, 2, 2);

    Matrix c;

    MatrixResult result = Matrix_Add(&a, &b, &c);

    TEST_ASSERT_EQUAL(result, MATRIX_ERR_DIMENSIONS);
}

void test_matrix_add_correctness(void)
{
#define N 2

    int a_data[N][N] = {{1, 2}, {3, 4}};
    int b_data[N][N] = {{0, -1}, {3, 5}};
    int c_data[N][N] = {{1, 1}, {6, 9}};

    Matrix a;
    Matrix b;

    Matrix_From(&a, N, N, a_data);
    Matrix_From(&b, N, N, b_data);

    Matrix c;

    Matrix_Add(&c, &a, &b);

    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            TEST_ASSERT_EQUAL(Matrix_Get(&c, i, j), c_data[i][j]);
        }
    }

#undef N
}

void test_matrix_product_wrong_dimensions(void)
{
    Matrix a;
    Matrix b;

    Matrix_New(&a, 1, 4);
    Matrix_New(&b, 2, 2);

    Matrix c;

    MatrixResult result = Matrix_Product(&c, &a, &b);

    TEST_ASSERT_EQUAL(result, MATRIX_ERR_DIMENSIONS);
}

void test_matrix_product_correctness(void)
{
#define M 3
#define N 3
#define P 2

    int a_data[M][N] = {{1, -2, 3}, {9, -8, 7}, {0, 1, -1}};
    int b_data[N][P] = {{4, 5}, {6, 5}, {4, 6}};

    int c_data[M][P] = {{4, 13}, {16, 47}, {2, -1}};

    Matrix a;
    Matrix b;

    Matrix_From(&a, M, N, a_data);
    Matrix_From(&b, N, P, b_data);

    Matrix c;

    MatrixResult result = Matrix_Product(&c, &a, &b);

    TEST_ASSERT_EQUAL(result, MATRIX_OK);

    for (size_t i = 0; i < M; ++i)
    {
        for (size_t j = 0; j < P; ++j)
        {
            TEST_ASSERT_EQUAL(Matrix_Get(&c, i, j), c_data[i][j]);
        }
    }

#undef M
#undef N
#undef P
}

void test_matrix_product_correctness_vector(void)
{
#define M 3
#define N 3
#define P 1

    int a_data[M][N] = {{1, -2, 3}, {9, -8, 7}, {0, 1, -1}};
    int v_data[N][P] = {{4}, {6}, {-2}};

    int c_data[M][P] = {{-14}, {-26}, {8}};

    Matrix a;
    Matrix v;

    Matrix_From(&a, M, N, a_data);
    Matrix_From(&v, N, P, v_data);

    Matrix c;

    MatrixResult result = Matrix_Product(&c, &a, &v);

    TEST_ASSERT_EQUAL(result, MATRIX_OK);

    for (size_t i = 0; i < M; ++i)
    {
        for (size_t j = 0; j < P; ++j)
        {
            TEST_ASSERT_EQUAL(Matrix_Get(&c, i, j), c_data[i][j]);
        }
    }

#undef M
#undef N
#undef P
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_matrix_new_allocation_overflow);
    RUN_TEST(test_matrix_new_allocation_zero);
    RUN_TEST(test_matrix_add_diferent_sizes);
    RUN_TEST(test_matrix_add_correctness);
    RUN_TEST(test_matrix_product_wrong_dimensions);
    RUN_TEST(test_matrix_product_correctness);
    RUN_TEST(test_matrix_product_correctness_vector);

    return UNITY_END();
}
