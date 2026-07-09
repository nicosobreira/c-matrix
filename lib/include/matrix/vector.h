#pragma once

#include "core.h"

typedef struct Vector
{
    size_t size;
    Type *data;
} Vector;

MatrixResult Vector_New(Vector *v, size_t size);
MatrixResult Vector_Clone(Vector *result, const Vector *from);
MatrixResult Vector_Load(Vector *result, size_t size, Type data[size]);

// ============================================================================

MatrixResult Vector_Get(const Vector *self, size_t i, Type *variable);

MatrixResult Vector_Set(Vector *self, size_t i, Type value);

// ============================================================================

Type Vector_DotProduct(const Vector *a, const Vector *b);
Type Vector_Norm(const Vector *v);
MatrixResult Vector_Normalize(Vector *result, const Vector *v);
