#pragma once

typedef struct Point
{
    double x;
    double y;
} Point;

void Point_New(Point *self, double x, double y);

void Point_Rotate(Point *self, double angle);
