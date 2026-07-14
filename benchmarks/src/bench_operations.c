#include "bench.h"

#include "matrix/core.h"

static inline void sum(Matrix a, Matrix b)
{
    Matrix r;
    Matrix_Add(&r, &a, &b);

    Matrix_Free(&r);
}

int main(void)
{
    Matrix a;
    Matrix b;

    Matrix_New(&a, 100, 100);
    Matrix_New(&b, 100, 100);

    BENCHMARK("Sum", 100, 100000, sum(a, b));
}
