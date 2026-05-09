#include "unity.h"

#include "matrix/matrix.h"

#include "determinant.h"
#include "operations.h"
#include "triangular.h"

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

    RUN_TEST(test_Matrix_Product_WrongDimensions);
    RUN_TEST(test_Matrix_Product_Correctness);
    RUN_TEST(test_Matrix_Product_CorrectnessVector);

    RUN_TEST(test_Matrix_Determinant_NotSquare);
    RUN_TEST(test_Matrix_Determinant_1x1);
    RUN_TEST(test_Matrix_Determinant_2x2);
    RUN_TEST(test_Matrix_Determinant_3x3);

    RUN_TEST(test_Matrix_TriangularSuperior_NullSwap);
    RUN_TEST(test_Matrix_TriangularSuperior_WithoutSwap);
    RUN_TEST(test_Matrix_TriangularSuperior_WithSwap);
    RUN_TEST(test_Matrix_TriangularSuperior_NotSquare);
    RUN_TEST(test_Matrix_TriangularSuperior_Correctness);
    RUN_TEST(test_Matrix_TriangularSuperior_DoNothing);

    return UNITY_END();
}
