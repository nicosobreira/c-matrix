#include "decomposition.h"

static void Matrix_SwapLines(Matrix *self, size_t line_a, size_t line_b)
{
    for (size_t j = 0; j < self->columns; ++j)
    {
        Type temp = Matrix_Get(self, line_b, j);

        Matrix_Set(self, line_b, j, Matrix_Get(self, line_a, j));

        Matrix_Set(self, line_a, j, temp);
    }
}

MatrixResult Matrix_TriangularSuperior(Matrix *result, Matrix *from, int *line_swaps)
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

            for (size_t j = pivot; j < n; ++j)
            {
                Type value = Matrix_Get(result, current, j) - k * Matrix_Get(result, pivot, j);

                Matrix_Set(result, current, j, value);
            }
        }
    }

    return MATRIX_OK;
}
