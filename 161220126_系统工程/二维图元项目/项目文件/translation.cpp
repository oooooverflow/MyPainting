#include "translation.h"
#include <QDebug>

Translation::Translation()
{

}

Shape* Translation::translationTheShape(Shape* theShape, int currentShape, QPoint start, QPoint end, QImage* image, QColor* color) {
    QPoint distance = end-start;
    Shape* newShape;
    switch(currentShape) {          //绘制当前正在画的图形
        case 1: {
            newShape = new MyLine;
            newShape->setPoint(theShape->getStart()+distance, theShape->getEnd()+distance);
            newShape->drawMyself(image, color);
            break;
        }
        case 2: {
            newShape = new MyCircle;
            newShape->setPoint(theShape->getStart()+distance, theShape->getEnd()+distance);
            newShape->drawMyself(image, color);
            break;
        }
        case 3: {
            newShape = new MyEllipse(theShape->getAngle());
            newShape->setPoint(theShape->getStart()+distance, theShape->getEnd()+distance);
            newShape->drawMyself(image, color);
            break;
        }
        default:break;
    }
    return newShape;
}

MyPolygon* Translation::translationTheShape(MyPolygon* polygon, QPoint start, QPoint end, QImage* image, QColor* color) {
    MyPolygon* newpoly = new MyPolygon(polygon->angle);
    newpoly->isdone = true;
    QPoint distance = end-start;
    for(int i = 0; i < polygon->lines.size(); i++) {
        newpoly->lines.push_back(polygon->lines[i]+distance);
    }
    newpoly->drawTheTotal(image, color);
    return newpoly;
}

MyCurve* Translation::translationTheShape(MyCurve* curve, QPoint start, QPoint end, QImage* image, QColor* color) {
    MyCurve* newcurve = new MyCurve(curve->angle);
    QPoint distance = end-start;
    for(int i = 0; i < curve->anchors.size(); i++) {
        newcurve->anchors.push_back(curve->anchors[i]+distance);
    }
    newcurve->drawTheCurve(image, color);
    return newcurve;
}
