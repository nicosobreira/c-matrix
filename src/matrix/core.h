#pragma once

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

#include "core/errors.h"

#define MATRIX_SIZE 256

typedef double Type;

typedef struct Matrix
{
    size_t lines;
    size_t columns;
    Type data[MATRIX_SIZE][MATRIX_SIZE];
} Matrix;

#define X(enum_name, error_string) enum_name,
typedef enum MatrixResult
{
    MATRIX_ERRORS(X)
} MatrixResult;
#undef X

// ============================================================================

MatrixResult Matrix_New(Matrix *new, size_t lines, size_t columns);

MatrixResult Matrix_NewFrom(Matrix *new, Matrix *base);

MatrixResult Matrix_Load(Matrix *new, size_t lines, size_t columns, Type data[lines][columns]);

// ============================================================================

static inline Type Matrix_Get(Matrix *self, size_t i, size_t j)
{
    return self->data[i][j];
}

static inline void Matrix_Set(Matrix *self, size_t i, size_t j, Type value)
{
    self->data[i][j] = value;
}

static inline bool Matrix_IsSquare(Matrix *self)
{
    return (self->lines == self->columns);
}

/** Check if the dimensions of the matrices are equal
 */
static inline bool Matrix_IsSizeEqual(Matrix *a, Matrix *b)
{
    return (a->lines == b->lines && a->columns == b->columns);
}

// ============================================================================

const char *Matrix_GetErrorMsg(MatrixResult status);

// ============================================================================

MatrixResult Matrix_Add(Matrix *result, Matrix *a, Matrix *b);

MatrixResult Matrix_AddBy(Matrix *result, Matrix *self, Type value);

MatrixResult Matrix_Subtract(Matrix *result, Matrix *a, Matrix *b);

MatrixResult Matrix_SubtractBy(Matrix *result, Matrix *self, Type value);

MatrixResult Matrix_Product(Matrix *result, Matrix *a, Matrix *b);

MatrixResult Matrix_ProductBy(Matrix *result, Matrix *self, Type scalar);

// ============================================================================

void Matrix_Print(Matrix *self);
