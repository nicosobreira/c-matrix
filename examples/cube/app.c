#include "app.h"

#include <stdbool.h>
#include <stdio.h>

#include "ansi.h"
#include "time.h"

App App_New(void)
{
    return (App){
        .buffer = Buffer_New(),
        .point = {.x = 1, .y = 0},
    };
}

void App_Update(App *self)
{
    Point_Rotate(&self->point, 0.5);
}

void App_Draw(App *self)
{
    Buffer *buf = &self->buffer;

    printf(ANSI_RESET_CURSOR);
    printf(ANSI_CLEAR_SCREEN);

    Buffer_Clear(buf);

    Buffer_SetPixel(buf, &self->point);

    Buffer_Render(buf);
}

void App_Loop(App *self)
{
    double previousTime = getTimeMs();
    double lag = 0.0;
    while (true)
    {
        double currentTime = getTimeMs();
        double elapsedTime = currentTime - previousTime;
        previousTime = currentTime;
        lag += elapsedTime;

        while (lag >= MS_PER_UPDATE)
        {
            App_Update(self);
            lag -= MS_PER_UPDATE;
        }

        App_Draw(self);

        double frameEndTime = getTimeMs();
        double frameDuration = frameEndTime - currentTime;

        if (frameDuration < MS_PER_UPDATE)
        {
            sleep_ms((int)(MS_PER_UPDATE - frameDuration));
        }
    }
}
