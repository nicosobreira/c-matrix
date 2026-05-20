#include <stdio.h>

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

    Encode first = Encode_New(&key, 'c', 'a');
    Encode second = Encode_New(&key, 'l', 'o');

    Encode_Print(&first);
    Encode_Print(&second);
    printf("\n");

    Matrix inverse;
    HANDLE_ERROR(Matrix_Inverse(&inverse, &key));
    HANDLE_ERROR(Matrix_ModuleBy(&inverse, SIZE));

    Decode f = Decode_New(&inverse, &first);
    Decode s = Decode_New(&inverse, &second);

    Decode_Print(&f);
    Decode_Print(&s);
    printf("\n");
    return 0;
}
