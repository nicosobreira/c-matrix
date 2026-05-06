#pragma once

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>

#include "errors.h"

#define MATRIX_SIZE 256

typedef int Type;

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

MatrixResult Matrix_From(Matrix *new, size_t lines, size_t columns, Type data[lines][columns]);

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
