#pragma once

#include <matrix/core.h>

/// Is the column vector containing the index of the letters
typedef struct Encode
{
    Matrix data;
} Encode;

Encode Encode_New(Matrix *key, char a, char b);
void Encode_Print(Encode *self);
