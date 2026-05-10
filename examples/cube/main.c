#include <stdio.h>

#include "matrix/vector.h"

#define TOTAL 8
#define AXIS 3

int main(void)
{
    // clang-format off
    Type vertices[TOTAL][AXIS] = {
        { -1, -1, -1},
        {  1, -1, -1},
        { -1,  1, -1},
        {  1,  1, -1},
        { -1, -1,  1},
        {  1, -1,  1},
        { -1,  1,  1},
        {  1,  1,  1},
    };
    // clang-format on

    Vector v[TOTAL];

    for (size_t i = 0; i < TOTAL; ++i)
    {
        Vector_Load(&v[i], AXIS, vertices[i]);
    }

    return 0;
}
