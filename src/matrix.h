#pragma once

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

#include "matrix_errors.h"

#define MATRIX_SIZE 256

typedef int Type;

typedef struct Matrix
{
    size_t lines;
    size_t columns;
    Type data[MATRIX_SIZE][MATRIX_SIZE];
} Matrix;

#define X(enum_name, error_string) enum_name,
typedef enum MatrixStatus
{
    MATRIX_ERRORS(X)
} MatrixStatus;
#undef X

// ============================================================================

MatrixStatus Matrix_New(size_t lines, size_t columns, Matrix *new);

MatrixStatus Matrix_Add(Matrix *a, Matrix *b, Matrix *result);

MatrixStatus Matrix_Product(Matrix *a, Matrix *b, Matrix *result);

MatrixStatus Matrix_Inverse(Matrix *self, Matrix *result);

MatrixStatus Matrix_Determinant(Matrix *self, int *result);

// ============================================================================

static inline Type Matrix_Get(Matrix *self, size_t i, size_t j)
{
    assert(i < self->lines && j < self->columns);

    return self->data[i][j];
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

const char *Matrix_GetErrorMsg(MatrixStatus status);
