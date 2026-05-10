#pragma once

#include "buffer.h"
#include "point.h"

#define MS_PER_UPDATE (1000.0 / 15.0)

typedef struct App
{
    Buffer buffer;
    Point point;
} App;

App App_New(void);

void App_Update(App *self);
void App_Draw(App *self);

void App_Loop(App *self);
