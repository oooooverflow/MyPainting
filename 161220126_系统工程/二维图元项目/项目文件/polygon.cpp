#include "polygon.h"
#include <qmath.h>
#include <QDebug>

MyPolygon::MyPolygon(double angle)
{
    this->angle = angle;
}

void MyPolygon::drawMyself(QImage *image, QColor* color) {
    MyLine *tmp = new MyLine();
    if(isdone)  // 如果完成闭合，则连接最后一个点与第一个点
        tmp->setPoint(lines[lines.size()-1], lines[0]);
    else        // 闭合未完成，连接当前点与上一个点
        tmp->setPoint(lines[lines.size()-2], lines[lines.size()-1]);
    tmp->drawMyself(image, color);
}

void MyPolygon::drawTheTotal(QImage *image, QColor* color) {
    int x1, x2, y1, y2;
    int sumx = 0, sumy = 0;
    MyLine* tmp = new MyLine();
    for(int i = 0; i < lines.size(); i++) {
        sumx += lines[i].x();
        sumy += lines[i].y();
    }
    int center_x = sumx / lines.size();
    int center_y = sumy / lines.size();
    for(int i = 0; i < lines.size(); i++) {
        if(i == lines.size()-1) {
            x1 = getNewX(lines[i].x(), center_x, lines[i].y(), center_y, angle);
            y1 = getNewY(lines[i].x(), center_x, lines[i].y(), center_y, angle);
            x2 = getNewX(lines[0].x(), center_x, lines[0].y(), center_y, angle);
            y2 = getNewY(lines[0].x(), center_x, lines[0].y(), center_y, angle);
        }
        else {
            x1 = getNewX(lines[i].x(), center_x, lines[i].y(), center_y, angle);
            y1 = getNewY(lines[i].x(), center_x, lines[i].y(), center_y, angle);
            x2 = getNewX(lines[i+1].x(), center_x, lines[i+1].y(), center_y, angle);
            y2 = getNewY(lines[i+1].x(), center_x, lines[i+1].y(), center_y, angle);
        }
        tmp->setPoint(QPoint(x1,y1), QPoint(x2,y2));
        tmp->drawMyself(image, color);
    }
}

int MyPolygon::getNewX(int x, int xr, int y, int yr, double angle) {
    return (int)(xr+(x-xr)*qCos(angle)-(y-yr)*qSin(angle));
}

int MyPolygon::getNewY(int x, int xr, int y, int yr, double angle) {
    return (int)(yr+(x-xr)*qSin(angle)+(y-yr)*qCos(angle));
}

