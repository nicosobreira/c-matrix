#pragma once

#include "matrix.h"

/** Transform a matrix to it's triangular superior using Gaussian Elimination
 * @retval MATRIX_OK The operation was a success
 * @retval MATRIX_ERR_DIMENSIONS The matrix `from` isn't square
 * @retval MATRIX_ERR_ALLOCATION Couldn't allocate a new `result`
 */
MatrixResult Matrix_TriangularSuperior(Matrix *result, Matrix *from, int *line_swaps);

/** Transform a matrix to it's inverse using the Gauss-Jordan method
 * @retval MATRIX_OK The operation was a success
 * @retval MATRIX_ERR_DIMENSIONS The matrix `from` isn't square
 * @retval MATRIX_ERR_ALLOCATION Couldn't allocate a new `result` or a internal
 * identity matrix
 * @retval MATRIX_ERR_NOT_INVERTIBLE The determinant of `from` is equal to zero
 */
MatrixResult Matrix_Inverse(Matrix *result, Matrix *from);
