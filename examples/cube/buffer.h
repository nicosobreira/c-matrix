#pragma once

#include <stddef.h>

#include "point.h"

#define WIDTH 80
#define HEIGHT 40

#define BUFFER_SIZE ((WIDTH + 1) * HEIGHT)

typedef struct Buffer
{
    char data[BUFFER_SIZE];
    size_t width;
    size_t height;
} Buffer;

static inline size_t Buffer_GetIndex(Buffer *self, size_t x, size_t y)
{
    return y * (self->width + 1) + x;
}

static inline void Buffer_Set(Buffer *self, size_t x, size_t y, char value)
{
    self->data[Buffer_GetIndex(self, x, y)] = value;
}

Buffer Buffer_New(void);

void Buffer_Clear(Buffer *self);

void Buffer_Render(Buffer *self);

void Buffer_SetPixel(Buffer *self, Point *p);
