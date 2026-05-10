#include "point.h"

#include <assert.h>
#include <math.h>

void Point_New(Point *self, double x, double y)
{
    assert(x >= -1 && x <= 1);
    assert(y >= -1 && y <= 1);

    self->x = x;
    self->y = y;
}

void Point_Rotate(Point *self, double angle)
{
    double new_x = self->x * cos(angle) - self->y * sin(angle);
    double new_y = self->x * sin(angle) + self->y * cos(angle);

    Point_New(self, new_x, new_y);
}
