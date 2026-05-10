#include <stdio.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix/vector.h"

#include "ansi.h"
#include "app.h"

#define TOTAL 8
#define AXIS 3

#ifdef _WIN32
#include <windows.h>
#endif

void setup_terminal(void)
{
#ifdef _WIN32
    // ANSI support for Windows
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
        return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
        return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

void handle_sigint(int sig)
{
    (void)sig;

    printf(ANSI_BUFFER_OFF);
    printf(ANSI_CURSOR_ON);
    fflush(stdout);

    exit(0);
}

int main(void)
{
    setup_terminal();

    signal(SIGINT, handle_sigint);

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

    printf(ANSI_BUFFER_ON);
    printf(ANSI_CURSOR_OFF);

    App app = App_New();
    App_Loop(&app);

    printf(ANSI_BUFFER_OFF);
    printf(ANSI_CURSOR_ON);

    return 0;
}
