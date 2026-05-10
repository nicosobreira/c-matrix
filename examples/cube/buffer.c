#include "buffer.h"

#include <stdio.h>
#include <string.h>

Buffer Buffer_New(void)
{
    Buffer self;
    self.width = WIDTH;
    self.height = HEIGHT;

    memset(self.data, ' ', BUFFER_SIZE);

    for (int y = 0; y < HEIGHT; y++)
    {
        Buffer_Set(&self, self.width, y, '\n');
    }

    return self;
}

void Buffer_Clear(Buffer *self)
{
    for (size_t y = 0; y < self->height; ++y)
    {
        for (size_t x = 0; x < self->width; ++x)
        {
            Buffer_Set(self, x, y, ' ');
        }
    }
}

void Buffer_Render(Buffer *self)
{
    printf("%.*s", BUFFER_SIZE, self->data);
}

void Buffer_SetPixel(Buffer *self, Point *p)
{
    // -1 .. 1 => 0 .. 2 => 0 .. 1 => 0 .. size

    int new_x = (size_t)((p->x + 1.0) / 2.0 * self->width);
    int new_y = (size_t)((1 - (p->y + 1.0) / 2.0) * self->height);

    Buffer_Set(self, new_x, new_y, '#');
}
