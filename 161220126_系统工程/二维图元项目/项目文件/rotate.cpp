#include "rotate.h"
#include <qmath.h>
#include <QDebug>

Rotate::Rotate()
{

}

int Rotate::getNewX(int x, int xr, int y, int yr, double angle) {
    return (int)(xr+(x-xr)*qCos(angle)-(y-yr)*qSin(angle));
}

int Rotate::getNewY(int x, int xr, int y, int yr, double angle) {
    return (int)(yr+(x-xr)*qSin(angle)+(y-yr)*qCos(angle));
}

Shape* Rotate::rotateTheShape(Shape* theShape, int currentShape, QPoint start, QPoint end, QImage* image, QColor* color) {
    //qDebug() << (theShape->getStart().x()+theShape->getEnd().x())/2 << endl;
    int x1 = start.x()-((theShape->getStart().x()+theShape->getEnd().x())/2), x2 = end.x()-((theShape->getStart().x()+theShape->getEnd().x())/2), y1 = start.y()-((theShape->getStart().y()+theShape->getEnd().y())/2), y2 = end.y()-((theShape->getStart().y()+theShape->getEnd().y())/2);
    double angle = qAcos((x1*x2+y1*y2)/(sqrt(x1*x1+y1*y1)*sqrt(x2*x2+y2*y2)));
    int judge = x1*y2 - y1*x2;
    if(judge < 0)
        angle = -1*angle;
    int nX1 = getNewX(theShape->getStart().x(), (theShape->getStart().x()+theShape->getEnd().x())/2, theShape->getStart().y(), (theShape->getStart().y()+theShape->getEnd().y())/2, angle);
    int nY1 = getNewY(theShape->getStart().x(), (theShape->getStart().x()+theShape->getEnd().x())/2, theShape->getStart().y(), (theShape->getStart().y()+theShape->getEnd().y())/2, angle);
    int nX2 = getNewX(theShape->getEnd().x(), (theShape->getStart().x()+theShape->getEnd().x())/2, theShape->getEnd().y(), (theShape->getStart().y()+theShape->getEnd().y())/2, angle);
    int nY2 = getNewY(theShape->getEnd().x(), (theShape->getStart().x()+theShape->getEnd().x())/2, theShape->getEnd().y(), (theShape->getStart().y()+theShape->getEnd().y())/2, angle);
    Shape* newShape;
    switch(currentShape) {          //绘制当前正在画的图形
        case 1: {
            newShape = new MyLine;
            newShape->setPoint(QPoint(nX1, nY1), QPoint(nX2, nY2));
            newShape->drawMyself(image, color);
            break;
        }
        case 2: {
            newShape = new MyCircle;
            newShape->setPoint(QPoint(nX1, nY1), QPoint(nX2, nY2));
            newShape->drawMyself(image, color);
            break;
        }
        case 3: {
            newShape = new MyEllipse(theShape->getAngle() + angle);
            newShape->setPoint(theShape->getStart(), theShape->getEnd());
            newShape->drawMyself(image, color);
            break;
        }
        default:break;
    }
    return newShape;
}

MyPolygon* Rotate::rotateTheShape(MyPolygon* polygon, QPoint start, QPoint end, QImage* image, QColor* color) {
    MyPolygon* newpoly;
    int sumx = 0, sumy = 0;
    for(int i = 0; i < polygon->lines.size(); i++) {
        sumx += polygon->lines[i].x();
        sumy += polygon->lines[i].y();
    }
    int center_x = sumx / polygon->lines.size();
    int center_y = sumy / polygon->lines.size();
    int x1 = start.x()-center_x, x2 = end.x()-center_x, y1 = start.y()-center_y, y2 = end.y()-center_y;
    double angle = qAcos((x1*x2+y1*y2)/(sqrt(x1*x1+y1*y1)*sqrt(x2*x2+y2*y2)));
    int judge = x1*y2 - y1*x2;
    if(judge < 0)
        angle = -1*angle;
    newpoly = new MyPolygon(polygon->angle+angle);
    //qDebug() << newpoly->angle*180/3.1415926 << endl;
    for(int i = 0; i < polygon->lines.size(); i++) {
        newpoly->lines.push_back(polygon->lines[i]);
    }
    newpoly->isdone = true;
    newpoly->drawTheTotal(image, color);
    return newpoly;
}

MyCurve* Rotate::rotateTheShape(MyCurve* curve, QPoint start, QPoint end, QImage* image, QColor* color) {
    MyCurve* newcurve;
    int sumx = 0, sumy = 0;
    for(int i = 0; i < curve->anchors.size(); i++) {
        sumx += curve->anchors[i].x();
        sumy += curve->anchors[i].y();
    }
    int center_x = sumx / curve->anchors.size();
    int center_y = sumy / curve->anchors.size();
    int x1 = start.x()-center_x, x2 = end.x()-center_x, y1 = start.y()-center_y, y2 = end.y()-center_y;
    double angle = qAcos((x1*x2+y1*y2)/(sqrt(x1*x1+y1*y1)*sqrt(x2*x2+y2*y2)));
    int judge = x1*y2 - y1*x2;
    if(judge < 0)
        angle = -1*angle;
    newcurve = new MyCurve(curve->angle+angle);
    for(int i = 0; i < curve->anchors.size(); i++) {
        newcurve->anchors.push_back(curve->anchors[i]);
    }
    newcurve->drawTheCurve(image, color);
    return newcurve;
}
