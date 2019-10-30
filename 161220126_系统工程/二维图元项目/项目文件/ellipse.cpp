#include "ellipse.h"
#include <qmath.h>

MyEllipse::MyEllipse(double angle) {
    this->angle = angle;
}

int MyEllipse::getNewX(int x, int xr, int y, int yr, double angle) {
    return (int)(xr+(x-xr)*qCos(angle)-(y-yr)*qSin(angle));
}

int MyEllipse::getNewY(int x, int xr, int y, int yr, double angle) {
    return (int)(yr+(x-xr)*qSin(angle)+(y-yr)*qCos(angle));
}

void MyEllipse::drawMyself(QImage *image, QColor* color) {
    int center_x = (getStart().x()+getEnd().x())/2;
    int center_y = (getStart().y()+getEnd().y())/2;
    int a = abs((getEnd().x()-getStart().x())/2);
    int b = abs((getEnd().y()-getStart().y())/2);
    int sqa = a * a;
    int sqb = b * b;
    int x = 0;
    int y = b;
    int d = 2 * sqb - 2 * b * sqa + sqa;
    int xx = getNewX(x+center_x, center_x, y+center_y, center_y, angle);
    int yy = getNewY(x+center_x, center_x, y+center_y, center_y, angle);
    if(xx >= 0 && xx < image->width() && yy >= 0 && yy <= image->height()) {
        image->setPixelColor(xx, yy, (*color));
        if(xx+1 < image->width())
            image->setPixelColor(xx+1, yy, (*color));
        if(yy+1 <= image->height())
            image->setPixelColor(xx, yy+1, (*color));
    }
    xx = getNewX(center_x-x, center_x, y+center_y, center_y, angle);
    yy = getNewY(center_x-x, center_x, y+center_y, center_y, angle);
    if(xx >= 0 && xx < image->width() && yy >= 0 && yy <= image->height()) {
        image->setPixelColor(xx, yy, (*color));
        if(xx+1 < image->width())
            image->setPixelColor(xx+1, yy, (*color));
        if(yy+1 <= image->height())
            image->setPixelColor(xx, yy+1, (*color));
    }
    xx = getNewX(center_x-x, center_x, center_y-y, center_y, angle);
    yy = getNewY(center_x-x, center_x, center_y-y, center_y, angle);
    if(xx >= 0 && xx < image->width() && yy >= 0 && yy <= image->height()) {
        image->setPixelColor(xx, yy, (*color));
        if(xx+1 < image->width())
            image->setPixelColor(xx+1, yy, (*color));
        if(yy+1 <= image->height())
            image->setPixelColor(xx, yy+1, (*color));
    }
    xx = getNewX(x+center_x, center_x, center_y-y, center_y, angle);
    yy = getNewY(x+center_x, center_x, center_y-y, center_y, angle);
    if(xx >= 0 && xx < image->width() && yy >= 0 && yy <= image->height()) {
        image->setPixelColor(xx, yy, (*color));
        if(xx+1 < image->width())
            image->setPixelColor(xx+1, yy, (*color));
        if(yy+1 <= image->height())
            image->setPixelColor(xx, yy+1, (*color));
    }
    int P_x = int((double)sqa/sqrt((double)(sqa+sqb)));
    while(x <= P_x) {
        if(d < 0) {
            d += 2 * sqb * (2 * x + 3);
        }
        else {
            d += 2 * sqb * (2 * x + 3) - 4 * sqa * (y - 1);
        y--;
        }
        x++;
        xx = getNewX(x+center_x, center_x, y+center_y, center_y, angle);
        yy = getNewY(x+center_x, center_x, y+center_y, center_y, angle);
        if(xx >= 0 && xx < image->width() && yy >= 0 && yy <= image->height()) {
            image->setPixelColor(xx, yy, (*color));
            if(xx+1 < image->width())
                image->setPixelColor(xx+1, yy, (*color));
            if(yy+1 <= image->height())
                image->setPixelColor(xx, yy+1, (*color));
        }
        xx = getNewX(center_x-x, center_x, y+center_y, center_y, angle);
        yy = getNewY(center_x-x, center_x, y+center_y, center_y, angle);
        if(xx >= 0 && xx < image->width() && yy >= 0 && yy <= image->height()) {
            image->setPixelColor(xx, yy, (*color));
            if(xx+1 < image->width())
                image->setPixelColor(xx+1, yy, (*color));
            if(yy+1 <= image->height())
                image->setPixelColor(xx, yy+1, (*color));
        }
        xx = getNewX(center_x-x, center_x, center_y-y, center_y, angle);
        yy = getNewY(center_x-x, center_x, center_y-y, center_y, angle);
        if(xx >= 0 && xx < image->width() && yy >= 0 && yy <= image->height()) {
            image->setPixelColor(xx, yy, (*color));
            if(xx+1 < image->width())
                image->setPixelColor(xx+1, yy, (*color));
            if(yy+1 <= image->height())
                image->setPixelColor(xx, yy+1, (*color));
        }
        xx = getNewX(x+center_x, center_x, center_y-y, center_y, angle);
        yy = getNewY(x+center_x, center_x, center_y-y, center_y, angle);
        if(xx >= 0 && xx < image->width() && yy >= 0 && yy <= image->height()) {
            image->setPixelColor(xx, yy, (*color));
            if(xx+1 < image->width())
                image->setPixelColor(xx+1, yy, (*color));
            if(yy+1 <= image->height())
                image->setPixelColor(xx, yy+1, (*color));
        }
    }
    d = sqb * (x * x + x) + sqa * (y * y - y) - sqa * sqb;
    while(y >= 0) {
        xx = getNewX(x+center_x, center_x, y+center_y, center_y, angle);
        yy = getNewY(x+center_x, center_x, y+center_y, center_y, angle);
        if(xx >= 0 && xx < image->width() && yy >= 0 && yy <= image->height()) {
            image->setPixelColor(xx, yy, (*color));
            if(xx+1 < image->width())
                image->setPixelColor(xx+1, yy, (*color));
            if(yy+1 <= image->height())
                image->setPixelColor(xx, yy+1, (*color));
        }
        xx = getNewX(center_x-x, center_x, y+center_y, center_y, angle);
        yy = getNewY(center_x-x, center_x, y+center_y, center_y, angle);
        if(xx >= 0 && xx < image->width() && yy >= 0 && yy <= image->height()) {
            image->setPixelColor(xx, yy, (*color));
            if(xx+1 < image->width())
                image->setPixelColor(xx+1, yy, (*color));
            if(yy+1 <= image->height())
                image->setPixelColor(xx, yy+1, (*color));
        }
        xx = getNewX(center_x-x, center_x, center_y-y, center_y, angle);
        yy = getNewY(center_x-x, center_x, center_y-y, center_y, angle);
        if(xx >= 0 && xx < image->width() && yy >= 0 && yy <= image->height()) {
            image->setPixelColor(xx, yy, (*color));
            if(xx+1 < image->width())
                image->setPixelColor(xx+1, yy, (*color));
            if(yy+1 <= image->height())
                image->setPixelColor(xx, yy+1, (*color));
        }
        xx = getNewX(x+center_x, center_x, center_y-y, center_y, angle);
        yy = getNewY(x+center_x, center_x, center_y-y, center_y, angle);
        if(xx >= 0 && xx < image->width() && yy >= 0 && yy <= image->height()) {
            image->setPixel(xx, yy, qRgb(255, 0, 0));
            if(xx+1 < image->width())
                image->setPixelColor(xx+1, yy, (*color));
            if(yy+1 <= image->height())
                image->setPixelColor(xx, yy+1, (*color));
        }
        y--;
        if(d < 0) {
            x++;
            d = d - 2 * sqa * y - sqa + 2 * sqb * x + 2 * sqb;
        }
        else {
            d = d - 2 * sqa * y - sqa;
        }
    }
}
/*
void MyEllipse::rotateMyself(QPoint sstart, QPoint eend, QImage *image) {

}
*/
