#include "shape.h"

Shape::Shape()
{

}

void Shape::drawMyself(QImage *image, QColor* color) {

}

void Shape::setPoint(QPoint sstart, QPoint eend) {
    start = sstart;
    end = eend;
}

QPoint Shape::getStart() {
    return start;
}

QPoint Shape::getEnd() {
    return end;
}

void Shape::setAngle(double angle) {
    this->angle = angle;
}

double Shape::getAngle() {
    return angle;
}
