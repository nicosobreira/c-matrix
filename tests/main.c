#include "unity.h"

#include "matrix/matrix.h"

#include "determinant.h"
#include "operations.h"

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

    TEST_ASSERT_EQUAL(MATRIX_ERR_ALLOCATION, result);
}

void test_matrix_new_allocation_zero(void)
{
    Matrix a;

    MatrixResult result = Matrix_New(&a, 0, 1);

    TEST_ASSERT_EQUAL(MATRIX_ERR_ALLOCATION, result);
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
    RUN_TEST(test_matrix_determinant_not_square);
    RUN_TEST(test_matrix_determinant_1);
    RUN_TEST(test_matrix_determinant_2);
    RUN_TEST(test_matrix_determinant_3);

    return UNITY_END();
}
