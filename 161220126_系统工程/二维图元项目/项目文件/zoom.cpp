#include "zoom.h"
#include <qmath.h>

Zoom::Zoom()
{

}

Shape* Zoom::zoomTheShape(Shape* theShape, int currentShape, QPoint start, QPoint end, QImage* image, QColor* color) {
    QPoint center = (theShape->getStart() + theShape->getEnd()) / 2;
    double distance1 = sqrt((start.x()-center.x())*(start.x()-center.x())+(start.y()-center.y())*(start.y()-center.y()));
    double distance2 = sqrt((end.x()-center.x())*(end.x()-center.x())+(end.y()-center.y())*(end.y()-center.y()));
    double multiple = distance2/distance1;
    Shape* newShape;
    int x1, x2, y1, y2;
    x1 = center.x()+(theShape->getStart().x()-center.x())*multiple;
    y1 = center.y()+(theShape->getStart().y()-center.y())*multiple;
    x2 = center.x()+(theShape->getEnd().x()-center.x())*multiple;
    y2 = center.y()+(theShape->getEnd().y()-center.y())*multiple;
    switch(currentShape) {          //绘制当前正在画的图形
        case 1: {
            newShape = new MyLine;
            newShape->setPoint(QPoint(x1, y1), QPoint(x2, y2));
            newShape->drawMyself(image, color);
            break;
        }
        case 2: {
            newShape = new MyCircle;
            newShape->setPoint(QPoint(x1, y1), QPoint(x2, y2));
            newShape->drawMyself(image, color);
            break;
        }
        case 3: {
            newShape = new MyEllipse(theShape->angle);
            newShape->setPoint(QPoint(x1, y1), QPoint(x2, y2));
            newShape->drawMyself(image, color);
            break;
        }
        default:break;
    }
    return newShape;
}

MyPolygon* Zoom::zoomTheShape(MyPolygon* polygon, QPoint start, QPoint end, QImage* image, QColor* color) {
    MyPolygon* newpoly = new MyPolygon(polygon->angle);
    newpoly->isdone = true;
    int sumx = 0, sumy = 0;
    for(int i = 0; i < polygon->lines.size(); i++) {
        sumx += polygon->lines[i].x();
        sumy += polygon->lines[i].y();
    }
    QPoint center = QPoint(sumx / polygon->lines.size(), sumy / polygon->lines.size());
    double distance1 = sqrt((start.x()-center.x())*(start.x()-center.x())+(start.y()-center.y())*(start.y()-center.y()));
    double distance2 = sqrt((end.x()-center.x())*(end.x()-center.x())+(end.y()-center.y())*(end.y()-center.y()));
    double multiple = distance2/distance1;
    int x, y;
    for(int i = 0; i < polygon->lines.size(); i++) {
        x = center.x()+(polygon->lines[i].x()-center.x())*multiple;
        y = center.y()+(polygon->lines[i].y()-center.y())*multiple;
        newpoly->lines.push_back(QPoint(x, y));
    }
    newpoly->drawTheTotal(image, color);
    return newpoly;
}

MyCurve* Zoom::zoomTheShape(MyCurve* curve, QPoint start, QPoint end, QImage* image, QColor* color) {
    MyCurve* newcurve = new MyCurve(curve->angle);
    int sumx = 0, sumy = 0;
    for(int i = 0; i < curve->anchors.size(); i++) {
        sumx += curve->anchors[i].x();
        sumy += curve->anchors[i].y();
    }
    QPoint center = QPoint(sumx / curve->anchors.size(), sumy / curve->anchors.size());
    double distance1 = sqrt((start.x()-center.x())*(start.x()-center.x())+(start.y()-center.y())*(start.y()-center.y()));
    double distance2 = sqrt((end.x()-center.x())*(end.x()-center.x())+(end.y()-center.y())*(end.y()-center.y()));
    double multiple = distance2/distance1;
    int x, y;
    for(int i = 0; i < curve->anchors.size(); i++) {
        x = center.x()+(curve->anchors[i].x()-center.x())*multiple;
        y = center.y()+(curve->anchors[i].y()-center.y())*multiple;
        newcurve->anchors.push_back(QPoint(x, y));
    }
    newcurve->drawTheCurve(image, color);
    return newcurve;
}
