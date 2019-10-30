#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"

class MyEllipse : public Shape
{
private:

public:
    MyEllipse(double angel = 0);
    void drawMyself(QImage *image, QColor* color);
    int getNewX(int x, int xr, int y, int yr, double angle);
    int getNewY(int x, int xr, int y, int yr, double angle);
    //void rotateMyself(QPoint sstart, QPoint eend, QImage *image);
};

#endif // ELLIPSE_H
