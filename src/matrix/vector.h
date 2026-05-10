#pragma once

#include "core.h"

typedef struct Vector
{
    size_t size;
    Type data[MATRIX_SIZE];
} Vector;

MatrixResult Vector_New(Vector *v, size_t size);
MatrixResult Vector_Clone(Vector *result, const Vector *from);
MatrixResult Vector_Load(Vector *result, size_t size, Type data[size]);

// ============================================================================

static inline Type Vector_Get(const Vector *self, size_t i)
{
    return self->data[i];
}

static inline void Vector_Set(Vector *self, size_t i, Type value)
{
    self->data[i] = value;
}

// ============================================================================

Type Vector_DotProduct(const Vector *a, const Vector *b); // Produto Escalar
Type Vector_Norm(const Vector *v);                        // Norma/Magnitude
MatrixResult Vector_Normalize(Vector *result, const Vector *v);
