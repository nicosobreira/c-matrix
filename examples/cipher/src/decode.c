#include "decode.h"

#include "alphabet.h"
#include "utils.h"

Decode Decode_New(Matrix *inverse, Encode *from)
{
    Decode new;

    HANDLE_ERROR(Matrix_Product(&new.data, inverse, &from->data));

    HANDLE_ERROR(Matrix_ModuleBy(&new.data, SIZE));

    return new;
}

void Decode_Print(Decode *self)
{
    size_t lines = self->data.lines;
    size_t columns = self->data.columns;

    for (size_t i = 0; i < lines; ++i)
    {
        for (size_t j = 0; j < columns; ++j)
        {
            Type value;
            HANDLE_ERROR(Matrix_Get(&self->data, i, j, &value));
            printf("%c", 'a' + (char)value);
        }
    }

    printf(" ");
}
