#pragma once

#include "matrix.h"

/** Transform a matrix to it's triangular superior using Gaussian Elimination
 * @retval MATRIX_OK The operation was a success
 * @retval MATRIX_ERR_DIMENSIONS The matrix `from` isn't square
 * @retval MATRIX_ERR_ALLOCATION Couldn't allocate a new `result`
 */
MatrixResult Matrix_TriangularSuperior(Matrix *result, Matrix *from, int *line_swaps);
