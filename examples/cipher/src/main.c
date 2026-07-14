#include <stdio.h>
#include <string.h>

#include <matrix/core.h>
#include <matrix/linalg.h>
#include <matrix/print.h>

#include "alphabet.h"
#include "decode.h"
#include "encode.h"
#include "utils.h"

int main(void)
{
    double k[2][2] = {{2, 9}, {8, 7}};

    Matrix key;
    HANDLE_ERROR(Matrix_Load(&key, 2, 2, k));

    return 0;
}
