// #include "matrix.h"
#include "unity.h"

// O Unity exige que essas funções existam (mesmo que vazias)
void setUp(void)
{
    // Executado antes de cada teste
}

void tearDown(void)
{
    // Executado depois de cada teste
}

// Uma função de teste
void test_soma_deve_retornar_valor_correto(void)
{
    TEST_ASSERT_EQUAL_INT(5, 5);
}

int main(void)
{
    UNITY_BEGIN(); // Inicializa o framework

    RUN_TEST(test_soma_deve_retornar_valor_correto); // Roda o seu teste

    return UNITY_END(); // Retorna o resultado para o sistema (usado pelo CTest)
}
