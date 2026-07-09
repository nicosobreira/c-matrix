#include "matrix/core.h"
#include "matrix/linalg.h"

#include "../internal.h"

static inline void swap_lines(Matrix *self, size_t line_a, size_t line_b)
{
    for (size_t j = 0; j < self->columns; ++j)
    {
        Type temp = internal_Matrix_Get(self, line_b, j);

        internal_Matrix_Set(self, line_b, j, internal_Matrix_Get(self, line_a, j));

        internal_Matrix_Set(self, line_a, j, temp);
    }
}

static inline void multiply_line_by(Matrix *self, size_t target_line, Type scalar, size_t start_col)
{
    for (size_t j = start_col; j < self->columns; ++j)
    {
        Type value = scalar * internal_Matrix_Get(self, target_line, j);

        internal_Matrix_Set(self, target_line, j, value);
    }
}

static inline void add_line_by_multiple(Matrix *self, size_t source_line, size_t target_line, Type scalar,
                                        size_t start_col)
{
    for (size_t j = start_col; j < self->columns; ++j)
    {
        Type value = internal_Matrix_Get(self, target_line, j) + scalar * internal_Matrix_Get(self, source_line, j);

        internal_Matrix_Set(self, target_line, j, value);
    }
}

MatrixResult Matrix_TriangularSuperior(Matrix *result, const Matrix *from, int *line_swaps)
{
    if (!Matrix_IsSquare(from))
    {
        *result = (Matrix){0};

        return MATRIX_ERR_DIMENSIONS;
    }

    MatrixResult r = Matrix_NewFrom(result, from);
    if (r != MATRIX_OK)
    {
        return r;
    }

    if (line_swaps != NULL)
    {
        *line_swaps = 0;
    }

    size_t n = result->lines;

    for (size_t pivot = 0; pivot < n; ++pivot)
    {
        // If the pivot is zero, then search for another line to swap
        if (internal_Matrix_Get(result, pivot, pivot) == 0)
        {
            for (size_t current = pivot + 1; current < n; ++current)
            {
                if (internal_Matrix_Get(result, current, pivot) == 0)
                {
                    continue;
                }

                swap_lines(result, current, pivot);

                if (line_swaps != NULL)
                {
                    *line_swaps += 1;
                }

                break;
            }
        }

        // If the pivot is still zero after the swap, then go to the next pivot
        if (internal_Matrix_Get(result, pivot, pivot) == 0)
        {
            continue;
        }

        // Transform the numbers bellow pivot to zero
        for (size_t current = pivot + 1; current < n; ++current)
        {
            if (internal_Matrix_Get(result, current, pivot) == 0)
            {
                continue;
            }

            Type k = internal_Matrix_Get(result, current, pivot) / internal_Matrix_Get(result, pivot, pivot);

            add_line_by_multiple(result, pivot, current, -k, pivot);
        }
    }

    return MATRIX_OK;
}

MatrixResult Matrix_Inverse(Matrix *result, const Matrix *from)
{
    if (!Matrix_IsSquare(from))
    {
        *result = (Matrix){0};
        return MATRIX_ERR_DIMENSIONS;
    }

    size_t n = from->lines;

    MatrixResult r;

    r = Matrix_Identity(result, n);
    if (r != MATRIX_OK)
    {
        return r;
    }

    Matrix copy;
    r = Matrix_NewFrom(&copy, from);
    if (r != MATRIX_OK)
    {
        return r;
    }

    r = Matrix_New(result, from->lines, from->columns);
    if (r != MATRIX_OK)
    {
        return r;
    }

    for (size_t pivot = 0; pivot < n; ++pivot)
    {
        // If the pivot is zero, then search for another line to swap
        if (internal_Matrix_Get(&copy, pivot, pivot) == 0)
        {
            for (size_t current = pivot + 1; current < n; ++current)
            {
                if (internal_Matrix_Get(&copy, current, pivot) == 0)
                {
                    continue;
                }

                swap_lines(&copy, current, pivot);
                swap_lines(result, current, pivot);

                break;
            }
        }

        if (internal_Matrix_Get(&copy, pivot, pivot) == 0)
        {
            Matrix_Free(&copy);

            return MATRIX_ERR_NOT_INVERTIBLE;
        }

        if (internal_Matrix_Get(&copy, pivot, pivot) != 1)
        {
            Type scalar = 1.0 / internal_Matrix_Get(&copy, pivot, pivot);

            multiply_line_by(&copy, pivot, scalar, 0);
            multiply_line_by(result, pivot, scalar, 0);
        }

        // Transform the numbers bellow and above the pivot to zero
        for (size_t current = 0; current < n; ++current)
        {
            if (current == pivot)
            {
                continue;
            }

            if (internal_Matrix_Get(&copy, current, pivot) == 0)
            {
                continue;
            }

            // The pivot is already 1
            Type k = internal_Matrix_Get(&copy, current, pivot) / 1.0;

            add_line_by_multiple(&copy, pivot, current, -k, pivot);
            add_line_by_multiple(result, pivot, current, -k, 0);
        }
    }

    Matrix_Free(&copy);

    return MATRIX_OK;
}
