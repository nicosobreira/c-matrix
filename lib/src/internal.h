#pragma once

#include "matrix/core.h"

/// Internal Matrix Get
/// Doesn't check indexes
static inline Type internal_Matrix_Get(const Matrix *self, size_t i, size_t j)
{
    return self->data[i * self->columns + j];
}

/// Internal Matrix Set
/// Doesn't check indexes
static inline void internal_Matrix_Set(Matrix *self, size_t i, size_t j, Type value)
{
    self->data[i * self->columns + j] = value;
}
