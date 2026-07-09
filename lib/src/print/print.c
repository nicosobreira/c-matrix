#include "matrix/print.h"

#include <stdio.h>

#include "../internal.h"

void Matrix_Print(const Matrix *self)
{
    for (size_t i = 0; i < self->lines; ++i)
    {
        printf("|");
        for (size_t j = 0; j < self->columns; ++j)
        {
            printf(" %g ", internal_Matrix_Get(self, i, j));
        }

        printf("|");
        printf("\n");
    }
}
