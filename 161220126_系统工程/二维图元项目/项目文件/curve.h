#ifndef CURVE_H
#define CURVE_H

#include <QImage>
#include <QPoint>
#include <QVector>

class MyCurve
{
public:
    double tension;                 // 张量参数
    double Mc[16];
    int grain;                      // 每段采样点个数
    double angle;
    QVector<QPoint> anchors;        // 控制点容器
    QVector<QPoint> points;
    QVector<double> alpha;
    MyCurve(double angle = 0);
    void drawTheCurve(QImage* image, QColor* color);       // 绘制函数
    double Matrix(double p0, double p1, double p2, double p3, double u);    // 获取与Cardinal矩阵相乘结果
    int getNewX(int x, int xr, int y, int yr, double angle);
    int getNewY(int x, int xr, int y, int yr, double angle);
};

#endif // CURVE_H
