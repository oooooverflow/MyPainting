#ifndef ROTATE_H
#define ROTATE_H

#include "line.h"
#include "circle.h"
#include "ellipse.h"
#include "polygon.h"
#include "curve.h"

class Rotate
{
public:
    Rotate();
    Shape* rotateTheShape(Shape* theShape, int currentShape, QPoint start, QPoint end, QImage* image, QColor* color);   // 基本图元旋转
    MyPolygon* rotateTheShape(MyPolygon* polygon, QPoint start, QPoint end, QImage* image, QColor* color);              // 多边形旋转
    MyCurve* rotateTheShape(MyCurve* curve, QPoint start, QPoint end, QImage* image, QColor* color);                    // 曲线旋转
    int getNewX(int x, int xr, int y, int yr, double angle);
    int getNewY(int x, int xr, int y, int yr, double angle);
};

#endif // ROTATE_H
