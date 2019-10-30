#include "edit.h"
#include <qmath.h>

Edit::Edit()
{

}

Shape* Edit::editTheShape(Shape* theShape, int currentShape, QImage* image, QPoint end, int index, QColor* color) {
    Shape* newShape;
    switch(currentShape) {
        case 1: {
            newShape = new MyLine;
            if(index == 1)
                newShape->setPoint(end, theShape->getEnd());
            else
                newShape->setPoint(theShape->getStart(), end);
            newShape->drawMyself(image, color);
            break;
        }
        case 2: {
            newShape = new MyCircle;
            if(index == 1)
                newShape->setPoint(end, theShape->getEnd());
            else
                newShape->setPoint(theShape->getStart(), end);
            newShape->drawMyself(image, color);
            break;
        }
        case 3: {
            double angle = theShape->getAngle();
            int x1 = theShape->getStart().x(), x2 = theShape->getEnd().x(), y1 = theShape->getStart().y(), y2 = theShape->getEnd().y();
            int nX1, nX2, nY1, nY2;
            int newx1, newx2, newy1, newy2;
            int center_x, center_y;
            int a, b, c, d;
            double newangle;
            int judge;
            if(index == 1) {
                newx2 = getNewX(x2, (x1+x2)/2, y2, (y1+y2)/2, angle);
                newy2 = getNewY(x2, (x1+x2)/2, y2, (y1+y2)/2, angle);
                newx1 = end.x();
                newy1 = end.y();
                center_x = (newx1 + newx2)/2;
                center_y = (newy1 + newy2)/2;
                a = x2-center_x, b = newx2-center_x, c = y2-center_y, d = newy2-center_y;
                newangle = qAcos((a*b+c*d)/(sqrt(a*a+c*c)*sqrt(b*b+d*d)));
                judge = a*d - c*b;
                if(judge < 0)
                    newangle = -1*newangle;
                newShape = new MyEllipse(newangle);
                nX1 = getNewX(newx1, (newx1+newx2)/2, newy1, (newy1+newy2)/2, -1*newangle);
                nY1 = getNewY(newx1, (newx1+newx2)/2, newy1, (newy1+newy2)/2, -1*newangle);
                end = QPoint(nX1, nY1);
                newShape->setPoint(end, theShape->getEnd());
            }
            else {
                newx1 = getNewX(x1, (x1+x2)/2, y1, (y1+y2)/2, angle);
                newy1 = getNewY(x1, (x1+x2)/2, y1, (y1+y2)/2, angle);
                newx2 = end.x();
                newy2 = end.y();
                center_x = (newx1 + newx2)/2;
                center_y = (newy1 + newy2)/2;
                a = x1-center_x, b = newx1-center_x, c = y1-center_y, d = newy1-center_y;
                newangle = qAcos((a*b+c*d)/(sqrt(a*a+c*c)*sqrt(b*b+d*d)));
                judge = a*d - c*b;
                if(judge < 0)
                    newangle = -1*newangle;
                newShape = new MyEllipse(newangle);
                nX2 = getNewX(newx2, (newx1+newx2)/2, newy2, (newy1+newy2)/2, -1*newangle);
                nY2 = getNewY(newx2, (newx1+newx2)/2, newy2, (newy1+newy2)/2, -1*newangle);
                end = QPoint(nX2, nY2);
                newShape->setPoint(theShape->getStart(), end);
            }
            newShape->drawMyself(image, color);
            break;
        }
        default:break;
    }
    return newShape;
}

MyPolygon* Edit::editTheShape(MyPolygon* polygon, QImage* image, QPoint end, int index, QColor* color) {
    MyPolygon* newpoly = new MyPolygon(polygon->angle);
    newpoly->isdone = true;
    for(int i = 0; i < polygon->lines.size(); i++) {
        if(i == index-1)
            newpoly->lines.push_back(end);
        else
            newpoly->lines.push_back(polygon->lines[i]);
    }
    newpoly->drawTheTotal(image, color);
    return newpoly;
}

MyCurve* Edit::editTheShape(MyCurve* curve, QImage* image, QPoint end, int index, QColor* color) {
    MyCurve* newcurve = new MyCurve(curve->angle);
    for(int i = 0; i < curve->anchors.size(); i++) {
        if(i == index-1)
            newcurve->anchors.push_back(end);
        else
            newcurve->anchors.push_back(curve->anchors[i]);
    }
    newcurve->drawTheCurve(image, color);
    return newcurve;
}

int Edit::getNewX(int x, int xr, int y, int yr, double angle) {
    return (int)(xr+(x-xr)*qCos(angle)-(y-yr)*qSin(angle));
}

int Edit::getNewY(int x, int xr, int y, int yr, double angle) {
    return (int)(yr+(x-xr)*qSin(angle)+(y-yr)*qCos(angle));
}
