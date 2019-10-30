#ifndef LINE_H
#define LINE_H

#include "shape.h"

class MyLine : public Shape
{
public:
    MyLine(double angle = 0);
    void drawMyself(QImage *image, QColor* color);
    //void rotateMyself(QPoint sstart, QPoint eend, QImage *image);
};

#endif // LINE_H
