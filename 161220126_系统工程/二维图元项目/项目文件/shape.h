#ifndef SHAPE_H
#define SHAPE_H

#include <QPoint>
#include <QPainter>
#include <QImage>

class Shape
{
protected:
    QPoint start, end;

public:
    double angle;
    Shape();
    void setPoint(QPoint sstart, QPoint eend);
    QPoint getStart();
    QPoint getEnd();
    void setAngle(double angle);
    double getAngle();
    virtual void drawMyself(QImage *image, QColor* color); // 虚函数，动态绑定

signals:

public slots:
};

#endif // SHAPE_H
