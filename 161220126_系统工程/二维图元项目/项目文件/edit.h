#ifndef EDIT_H
#define EDIT_H

#include "line.h"
#include "circle.h"
#include "ellipse.h"
#include "polygon.h"
#include "curve.h"

class Edit
{
public:
    Edit();
    Shape* editTheShape(Shape* theShape, int currentShape, QImage* image, QPoint end, int index, QColor* color);    // 基本图元编辑
    MyPolygon* editTheShape(MyPolygon* polygon, QImage* image, QPoint end, int index, QColor* color);               // 多边形编辑
    MyCurve* editTheShape(MyCurve* polygon, QImage* image, QPoint end, int index, QColor* color);                   // 曲线编辑
    int getNewX(int x, int xr, int y, int yr, double angle);
    int getNewY(int x, int xr, int y, int yr, double angle);
};

#endif // EDIT_H
