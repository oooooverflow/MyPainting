#ifndef ZOOM_H
#define ZOOM_H

#include "line.h"
#include "circle.h"
#include "ellipse.h"
#include "polygon.h"
#include "curve.h"

class Zoom
{
public:
    Zoom();
    Shape* zoomTheShape(Shape* theShape, int currentShape, QPoint start, QPoint end, QImage* image, QColor* color); // 基本图元缩放
    MyPolygon* zoomTheShape(MyPolygon* polygon, QPoint start, QPoint end, QImage* image, QColor* color);            // 多边形缩放
    MyCurve* zoomTheShape(MyCurve* curve, QPoint start, QPoint end, QImage* image, QColor* color);                  // 曲线缩放
};

#endif // ZOOM_H
