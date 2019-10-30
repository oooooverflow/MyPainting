#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <QImage>
#include "line.h"
#include "circle.h"
#include "ellipse.h"
#include "fill.h"
#include "translation.h"
#include "rotate.h"
#include "zoom.h"
#include "edit.h"
#include "polygon.h"
#include "cut.h"
#include "curve.h"


struct LineInfo {
    QPoint start;
    QPoint end;
};

class mypainter : public QWidget
{
    Q_OBJECT

private:
    QPoint start, end;
    Shape* theShape;
    MyPolygon* polygon;
    MyCurve* curve;
    int currentShape;
    int currentFunc;
    QImage* image;
    QImage* newImage;
    QImage* bufferImage;
    Fill* fill;
    Translation* translation;
    Rotate* rotate;
    Zoom* zoom;
    Edit* edit;
    Cut* cut;
    int isAnchor;
    bool isModified;
    QColor* color;

public:
    explicit mypainter(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void drawTheAnchor();
    int judgeIsAnchor(QPoint point);
    void closeEvent(QCloseEvent *event);

signals:

public slots:
    void changeShapeToLine();
    void changeShapeToCircle();
    void changeShapeToEllipse();
    void changeFuncToFill();
    void changeFuncToTranslation();
    void changeFuncToRotate();
    void changeFuncToZoom();
    void changeFuncToEdit();
    void changeFuncToPolygon();
    void open();
    void save();
    void changeFuncToCut();
    void changeFuncToCurve();
    void changeFuncToColor();
};

#endif // MYPAINTER_H
