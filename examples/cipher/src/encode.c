#include "encode.h"

#include "alphabet.h"
#include "utils.h"

Encode Encode_New(Matrix *key, char a, char b)
{
    Matrix temp;

    HANDLE_ERROR(Matrix_New(&temp, 2, 1));

    Matrix_Set(&temp, 0, 0, a - 'a');
    Matrix_Set(&temp, 1, 0, b - 'a');

    Encode self;
    HANDLE_ERROR(Matrix_Product(&self.data, key, &temp));

    HANDLE_ERROR(Matrix_ModuleBy(&self.data, SIZE));

    return self;
}

void Encode_Print(Encode *self)
{
    size_t lines = self->data.lines;
    size_t columns = self->data.columns;

    for (size_t i = 0; i < lines; ++i)
    {
        for (size_t j = 0; j < columns; ++j)
        {
            printf("%c", 'a' + (int)Matrix_Get(&self->data, i, j));
        }
    }

    printf(" ");
}
