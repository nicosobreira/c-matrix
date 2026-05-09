#include "matrix/core.h"

#include <stdio.h>

void Matrix_Print(const Matrix *self)
{
    for (size_t i = 0; i < self->lines; ++i)
    {
        for (size_t j = 0; j < self->columns; ++j)
        {
            printf("%.2f ", Matrix_Get(self, i, j));
        }

        printf("\n");
    }
}
