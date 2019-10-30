#ifndef TRANSLATION_H
#define TRANSLATION_H

#include "line.h"
#include "circle.h"
#include "ellipse.h"
#include "polygon.h"
#include "curve.h"

class Translation
{
public:
    Translation();
    Shape* translationTheShape(Shape* theShape, int currentShape, QPoint start, QPoint end, QImage* image, QColor* color);  // 基本图元平移
    MyPolygon* translationTheShape(MyPolygon* polygon, QPoint start, QPoint end, QImage* image, QColor* color);             // 多边形平移
    MyCurve* translationTheShape(MyCurve* curve, QPoint start, QPoint end, QImage* image, QColor* color);                   // 曲线平移
};

#endif // TRANSLATION_H
