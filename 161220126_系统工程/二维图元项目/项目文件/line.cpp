#include "line.h"
#include "circle.h"

MyLine::MyLine(double angle)
{
    this->angle = angle;
}

void MyLine::drawMyself(QImage *image, QColor* color) {   //DDA算法
    int x1 = getStart().x(), y1 = getStart().y(), x2 = getEnd().x(), y2 = getEnd().y();
    double dx, dy, e, x, y;
    dx = x2-x1;
    dy = y2-y1;
    e=(fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);    //计算主坐标轴
    dx /= e;
    dy /= e;
    x = x1;
    y = y1;
    for(int i = 1; i <= e; i++) {
        if((int)(x+0.5) >= 0 && (int)(x+0.5) < image->width() && (int)(y+0.5) >= 0 && (int)(y+0.5) <= image->height()) {
                image->setPixelColor((int)(x+0.5), (int)(y+0.5), (*color));  //在离直线最近的像素点打点
        }
        x += dx;
        y += dy;
    }
}
