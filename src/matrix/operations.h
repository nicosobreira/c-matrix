#pragma once

#include "matrix.h"

MatrixResult Matrix_Add(Matrix *result, Matrix *a, Matrix *b);

MatrixResult Matrix_AddBy(Matrix *result, Matrix *self, Type value);

MatrixResult Matrix_Subtract(Matrix *result, Matrix *a, Matrix *b);

MatrixResult Matrix_SubtractBy(Matrix *result, Matrix *self, Type value);

MatrixResult Matrix_Product(Matrix *result, Matrix *a, Matrix *b);

MatrixResult Matrix_ProductBy(Matrix *result, Matrix *self, Type scalar);
