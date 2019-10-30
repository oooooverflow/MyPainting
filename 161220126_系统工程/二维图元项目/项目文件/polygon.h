#ifndef POLYGON_H
#define POLYGON_H

#include "line.h"
#include <QVector>

class MyPolygon
{
public:
    bool isdone;
    double angle;
    QVector<QPoint> lines;                              // 控制点容器
    MyPolygon(double angle = 0);
    void drawMyself(QImage *image, QColor* color);      // 绘制每一段
    void drawTheTotal(QImage *image, QColor* color);    // 绘制整体多边形
    int getNewX(int x, int xr, int y, int yr, double angle);
    int getNewY(int x, int xr, int y, int yr, double angle);
};

#endif // POLYGON_H
