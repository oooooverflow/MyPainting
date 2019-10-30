#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class MyCircle : public Shape
{
public:
    MyCircle(double angle = 0);
    void drawMyself(QImage *image, QColor* color);
    //void rotateMyself(QPoint sstart, QPoint eend, QImage *image);
};

#endif // CIRCLE_H
