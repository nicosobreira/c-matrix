#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <matrix/core.h>

#define HANDLE_ERROR(Matrix_Func)                                   \
    do                                                              \
    {                                                               \
        MatrixResult _r = (Matrix_Func);                            \
        if (_r != MATRIX_OK)                                        \
        {                                                           \
            fprintf(stderr, "ERROR: %s\n", Matrix_GetErrorMsg(_r)); \
            exit(_r);                                               \
        }                                                           \
    } while (0);
