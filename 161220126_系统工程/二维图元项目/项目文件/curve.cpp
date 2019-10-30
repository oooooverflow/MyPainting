#include "curve.h"
#include <qmath.h>

MyCurve::MyCurve(double angle) {
    this->angle = angle;
    tension = 0.5;
    grain = 500;
    Mc[0] = -tension;
    Mc[1] = 2-tension;
    Mc[2] = tension-2;
    Mc[3] = tension;
    Mc[4] = 2*tension;
    Mc[5] = tension-3;
    Mc[6]=  3-2*tension;
    Mc[7]=  -tension;
    Mc[8] = -tension;
    Mc[9] = 0;
    Mc[10]  = tension;
    Mc[11]  = 0;
    Mc[12]  = 0;
    Mc[13]  = 1;
    Mc[14]  = 0;
    Mc[15]  = 0;
    for (int i = 0; i < grain; i++) {
        alpha.push_back(i*1.0/grain);
    }
}

void MyCurve::drawTheCurve(QImage* image, QColor* color) {
    // 控制点旋转
    int sumx = 0, sumy = 0;
    for(int i = 0; i < anchors.size(); i++) {
        sumx += anchors[i].x();
        sumy += anchors[i].y();
    }
    int center_x = sumx / anchors.size();
    int center_y = sumy / anchors.size();
    points.clear();
    int x = getNewX(anchors[0].x(), center_x, anchors[0].y(), center_y, angle);
    int y = getNewY(anchors[0].x(), center_x, anchors[0].y(), center_y, angle);
    points.push_back(QPoint(x, y));
    for (int i = 0; i < anchors.size(); i++) {
        x = getNewX(anchors[i].x(), center_x, anchors[i].y(), center_y, angle);
        y = getNewY(anchors[i].x(), center_x, anchors[i].y(), center_y, angle);
        points.push_back(QPoint(x, y));
    }
    x = getNewX(anchors[anchors.size()-1].x(), center_x, anchors[anchors.size()-1].y(), center_y, angle);
    y = getNewY(anchors[anchors.size()-1].x(), center_x, anchors[anchors.size()-1].y(), center_y, angle);
    points.push_back(QPoint(x, y));
    int kml = 0;
    int k0 = 1;
    int k1 = 2;
    int k2 = 3;
    for(int i = 1; i < anchors.size(); i++){
        for(int j = 0; j < grain; j++){
            // 与Cardinal矩阵相乘计算出点坐标，并绘制该点
            double cpx = Matrix(points[kml].x(), points[k0].x(), points[k1].x(), points[k2].x(), alpha[j]);
            double cpy = Matrix(points[kml].y(), points[k0].y(), points[k1].y(), points[k2].y(), alpha[j]);
            image->setPixelColor(cpx, cpy, (*color));
        }
        kml++; k0++; k1++; k2++;
    }
}

double MyCurve::Matrix(double p0, double p1, double p2, double p3, double u) {
    double a = Mc[0]*p0+Mc[1]*p1+Mc[2]*p2+Mc[3]*p3;
    double b = Mc[4]*p0+Mc[5]*p1+Mc[6]*p2+Mc[7]*p3;
    double c = Mc[8]*p0+Mc[9]*p1+Mc[10]*p2+Mc[11]*p3;
    double d = Mc[12]*p0+Mc[13]*p1+Mc[14]*p2+Mc[15]*p3;
    return (d+u*(c+u*(b+u*a)));
}

int MyCurve::getNewX(int x, int xr, int y, int yr, double angle) {
    return (int)(xr+(x-xr)*qCos(angle)-(y-yr)*qSin(angle));
}

int MyCurve::getNewY(int x, int xr, int y, int yr, double angle) {
    return (int)(yr+(x-xr)*qSin(angle)+(y-yr)*qCos(angle));
}

