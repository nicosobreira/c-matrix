#pragma once

#include <assert.h>

#include "matrix/core.h"

/// Internal Matrix Get
/// Doesn't check indexes
static inline Type internal_Matrix_Get(const Matrix *self, size_t i, size_t j)
{
    assert(i < self->lines);
    assert(j < self->columns);

    return self->data[i * self->columns + j];
}

/// Internal Matrix Set
/// Doesn't check indexes
static inline void internal_Matrix_Set(Matrix *self, size_t i, size_t j, Type value)
{
    assert(i < self->lines);
    assert(j < self->columns);

    self->data[i * self->columns + j] = value;
}
