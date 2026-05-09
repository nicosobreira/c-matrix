#include "unity.h"

#include "matrix/matrix.h"

#include "determinant.h"
#include "inverse.h"
#include "operations.h"
#include "triangular.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Matrix_New_AllocationOverflow(void)
{
    Matrix a;

    MatrixResult result = Matrix_New(&a, MATRIX_SIZE + 1, 1);

    TEST_ASSERT_EQUAL(MATRIX_ERR_ALLOCATION, result);
}

void test_Matrix_New_AllocationZero(void)
{
    Matrix a;

    MatrixResult result = Matrix_New(&a, 0, 1);

    TEST_ASSERT_EQUAL(MATRIX_ERR_ALLOCATION, result);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_Matrix_New_AllocationOverflow);
    RUN_TEST(test_Matrix_New_AllocationZero);

    RUN_TEST(test_Matrix_Add_DiferentSizes);
    RUN_TEST(test_Matrix_Add_Correctness);

    RUN_TEST(test_Matrix_Product_WrongDimensions);
    RUN_TEST(test_Matrix_Product_Correctness);
    RUN_TEST(test_Matrix_Product_CorrectnessVector);

    RUN_TEST(test_Matrix_Determinant_NotSquare);
    RUN_TEST(test_Matrix_Determinant_1x1);
    RUN_TEST(test_Matrix_Determinant_2x2);
    RUN_TEST(test_Matrix_Determinant_3x3);
    RUN_TEST(test_Matrix_Determinant_4x4);

    RUN_TEST(test_Matrix_TriangularSuperior_NullSwap);
    RUN_TEST(test_Matrix_TriangularSuperior_WithoutSwap);
    RUN_TEST(test_Matrix_TriangularSuperior_WithSwap);
    RUN_TEST(test_Matrix_TriangularSuperior_NotSquare);
    RUN_TEST(test_Matrix_TriangularSuperior_Correctness);
    RUN_TEST(test_Matrix_TriangularSuperior_DoNothing);

    RUN_TEST(test_Matrix_Inverse_2x2);
    RUN_TEST(test_Matrix_Inverse_WithLineSwap);
    RUN_TEST(test_Matrix_Inverse_NotInvertible);
    RUN_TEST(test_Matrix_Inverse_NotSquare);
    RUN_TEST(test_Matrix_Inverse_Identity);

    return UNITY_END();
}
