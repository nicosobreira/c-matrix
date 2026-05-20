#include "matrix/linalg.h"

static inline void Matrix_SwapLines(Matrix *self, size_t line_a, size_t line_b)
{
    for (size_t j = 0; j < self->columns; ++j)
    {
        Type temp = Matrix_Get(self, line_b, j);

        Matrix_Set(self, line_b, j, Matrix_Get(self, line_a, j));

        Matrix_Set(self, line_a, j, temp);
    }
}

static inline void Matrix_MultiplyLineBy(Matrix *self, size_t target_line, Type scalar, size_t start_col)
{
    for (size_t j = start_col; j < self->columns; ++j)
    {
        Type value = scalar * Matrix_Get(self, target_line, j);

        Matrix_Set(self, target_line, j, value);
    }
}

static inline void Matrix_AddLineByMultiple(Matrix *self, size_t source_line, size_t target_line, Type scalar,
                                            size_t start_col)
{
    for (size_t j = start_col; j < self->columns; ++j)
    {
        Type value = Matrix_Get(self, target_line, j) + scalar * Matrix_Get(self, source_line, j);

        Matrix_Set(self, target_line, j, value);
    }
}

MatrixResult Matrix_TriangularSuperior(Matrix *result, const Matrix *from, int *line_swaps)
{
    if (!Matrix_IsSquare(from))
    {
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
        if (Matrix_Get(result, pivot, pivot) == 0)
        {
            for (size_t current = pivot + 1; current < n; ++current)
            {
                if (Matrix_Get(result, current, pivot) == 0)
                {
                    continue;
                }

                Matrix_SwapLines(result, current, pivot);

                if (line_swaps != NULL)
                {
                    *line_swaps += 1;
                }

                break;
            }
        }

        // If the pivot is still zero after the swap, then go to the next pivot
        if (Matrix_Get(result, pivot, pivot) == 0)
        {
            continue;
        }

        // Transform the numbers bellow pivot to zero
        for (size_t current = pivot + 1; current < n; ++current)
        {
            if (Matrix_Get(result, current, pivot) == 0)
            {
                continue;
            }

            Type k = Matrix_Get(result, current, pivot) / Matrix_Get(result, pivot, pivot);

            Matrix_AddLineByMultiple(result, pivot, current, -k, pivot);
        }
    }

    return MATRIX_OK;
}

MatrixResult Matrix_Inverse(Matrix *result, const Matrix *from)
{
    if (!Matrix_IsSquare(from))
    {
        return MATRIX_ERR_DIMENSIONS;
    }

    size_t n = from->lines;

    MatrixResult r = Matrix_Identity(result, n);
    if (r != MATRIX_OK)
    {
        return r;
    }

    Matrix copy;
    Matrix_NewFrom(&copy, from);

    for (size_t pivot = 0; pivot < n; ++pivot)
    {
        // If the pivot is zero, then search for another line to swap
        if (Matrix_Get(&copy, pivot, pivot) == 0)
        {
            for (size_t current = pivot + 1; current < n; ++current)
            {
                if (Matrix_Get(&copy, current, pivot) == 0)
                {
                    continue;
                }

                Matrix_SwapLines(&copy, current, pivot);
                Matrix_SwapLines(result, current, pivot);

                break;
            }
        }

        if (Matrix_Get(&copy, pivot, pivot) == 0)
        {
            return MATRIX_ERR_NOT_INVERTIBLE;
        }

        if (Matrix_Get(&copy, pivot, pivot) != 1)
        {
            Type scalar = 1.0 / Matrix_Get(&copy, pivot, pivot);

            Matrix_MultiplyLineBy(&copy, pivot, scalar, 0);
            Matrix_MultiplyLineBy(result, pivot, scalar, 0);
        }

        // Transform the numbers bellow and above the pivot to zero
        for (size_t current = 0; current < n; ++current)
        {
            if (current == pivot)
            {
                continue;
            }

            if (Matrix_Get(&copy, current, pivot) == 0)
            {
                continue;
            }

            // The pivot is already 1
            Type k = Matrix_Get(&copy, current, pivot) / 1.0;

            Matrix_AddLineByMultiple(&copy, pivot, current, -k, pivot);
            Matrix_AddLineByMultiple(result, pivot, current, -k, 0);
        }
    }

    return MATRIX_OK;
}
