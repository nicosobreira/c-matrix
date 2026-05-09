#pragma once

#include "matrix.h"

MatrixResult Matrix_Add(Matrix *result, Matrix *a, Matrix *b);

MatrixResult Matrix_Product(Matrix *result, Matrix *a, Matrix *b);

MatrixResult Matrix_Inverse(Matrix *self, Matrix *result);
