#include "fill.h"

Fill::Fill() {

}

void Fill::fillTheArea(QPoint point, QImage* image, QColor* color) {
    QRgb origin = image->pixel(point);
    int x = point.x();
    int y = point.y();
    int i;
    for(i = x; ; i--) {
        if(i < 0 || image->pixel(i, y) != origin)
            break;
    }
    i++;
    pointStack.push_back(QPoint(i, y)); // 将每一个填充段的起始点压入栈中
    QPoint end;
    while(!pointStack.empty()) {    // 栈为空说明填充完毕
        i = pointStack.back().x();
        y = pointStack.back().y();
        pointStack.pop_back();
        end = fillTheLine(QPoint(i, y), origin, image, color);
        checkTheLine(QPoint(i, y-1), end, origin, image);   //检查相邻两行
        checkTheLine(QPoint(i, y+1), end, origin, image);
    }
}

QPoint Fill::fillTheLine(QPoint start, QRgb origin, QImage* image, QColor* color) {
    int x1 = start.x(), x, y = start.y();
    for(x = x1; ; x++) {
        if(x >= image->width()) // 越界检查
            break;
        if(image->pixel(x, y) == origin) {  // 与起初鼠标点击位置颜色不一样则涂色
            image->setPixelColor(x, y, (*color));
        }
        else
            break;
    }
    return QPoint(x-1, y);  // 返回结束点位置
}

void Fill::checkTheLine(QPoint start, QPoint end, QRgb origin, QImage* image) {
    int x1 = start.x(), x2 = end.x(), y = start.y();
    if(x1 < 0 || x2 >= image->width() || y < 0 || y >= image->height())
        return;
    int i;
    for(i = x1; i <= x2; i++) {
        if(image->pixel(i, y) == origin)
            break;
    }
    if(i == x2+1)
        return;
    for(i = x1; ; i--) {
        if(i < 0 || image->pixel(i, y) != origin)   // 找到一个起始点
            break;
    }
    i++;
    pointStack.push_back(QPoint(i, y));             // 压栈
    for(; i <= x2; i++) {                           // 从该点继续向右寻找
        if(image->pixel(i, y) != origin) {
            for(; i <= x2; i++) {
                if(image->pixel(i, y) == origin) {
                    pointStack.push_back(QPoint(i, y)); // 压栈
                    break;
                }
            }
        }
    }
}
