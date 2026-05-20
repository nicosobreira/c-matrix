#pragma once

#include <matrix/core.h>

#include "encode.h"

typedef struct Decode
{
    Matrix data;
} Decode;

Decode Decode_New(Matrix *inverse, Encode *from);

void Decode_Print(Decode *self);
