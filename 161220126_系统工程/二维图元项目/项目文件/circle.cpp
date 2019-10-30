#include "circle.h"

MyCircle::MyCircle(double angle)
{
    this->angle = angle;
}

void MyCircle::drawMyself(QImage *image, QColor* color) {     //Bresenham画圆算法的改进算法
    int x,y,p;
    int R = sqrt((getStart().x()-getEnd().x())*(getStart().x()-getEnd().x())+(getStart().y()-getEnd().y())*(getStart().y()-getEnd().y()))/2;
    int center_x = (getStart().x()+getEnd().x())/2;
    int center_y = (getStart().y()+getEnd().y())/2;
    x = 0;
    y = R;
    p = 3-2*R;  //起始P的值
    for(; x <= y; x++) {
        //一次打出八个点，分别属于各自的八分之一圆弧
        if(x+center_x >= 0 && x+center_x < image->width() && y+center_y >= 0 && y+center_y <= image->height())
            image->setPixelColor(x+center_x, y+center_y, (*color));
        if(y+center_x >= 0 && y+center_x < image->width() && x+center_y >= 0 && x+center_y <= image->height())
            image->setPixelColor(y+center_x, x+center_y, (*color));
        if(x+center_x >= 0 && x+center_x < image->width() && center_y-y >= 0 && center_y-y <= image->height())
            image->setPixelColor(x+center_x, center_y-y, (*color));
        if(y+center_x >= 0 && y+center_x < image->width() && center_y-x >= 0 && center_y-x <= image->height())
            image->setPixelColor(y+center_x, center_y-x, (*color));
        if(center_x-x >= 0 && center_x-x < image->width() && y+center_y >= 0 && y+center_y <= image->height())
            image->setPixelColor(center_x-x, y+center_y, (*color));
        if(center_x-y >= 0 && center_x-y < image->width() && x+center_y >= 0 && x+center_y <= image->height())
            image->setPixelColor(center_x-y, x+center_y, (*color));
        if(center_x-y >= 0 && center_x-y < image->width() && center_y-x >= 0 && center_y-x <= image->height())
            image->setPixelColor(center_x-y, center_y-x, (*color));
        if(center_x-x >= 0 && center_x-x < image->width() && center_y-y >= 0 && center_y-y <= image->height())
            image->setPixelColor(center_x-x, center_y-y, (*color));
        if(p >= 0) {
            p += 4*(x-y)+10;
            y--;
        }
        else {
            p += 4*x+6;
        }
    }
}
