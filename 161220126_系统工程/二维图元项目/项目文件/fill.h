#ifndef FILL_H
#define FILL_H

#include <QImage>
#include <QVector>

class Fill
{
private:
    QVector<QPoint> pointStack;     //存储每段待填充线段的起始点

public:
    Fill();
    void fillTheArea(QPoint point, QImage* image, QColor* color);   // 调度
    QPoint fillTheLine(QPoint start, QRgb origin, QImage* image, QColor* color);    // 填充线段
    void checkTheLine(QPoint start, QPoint end, QRgb origin, QImage* image);        // 检查每行找出起始点
};

#endif // FILL_H
