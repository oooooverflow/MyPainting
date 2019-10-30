#include "cut.h"

Cut::Cut()
{

}

void Cut::doCut(QImage* image, QPoint recMin, QPoint recMax, Shape* &shape, QColor* color) {    // 梁友栋-Barsky参数裁剪算法
    // 获取裁剪框边界信息
    int recMin_x = recMin.x(), recMin_y = recMin.y(), recMax_x = recMax.x(), recMax_y = recMax.y();
    int x1 = shape->getStart().x(), y1 = shape->getStart().y(), x2 = shape->getEnd().x(), y2 = shape->getEnd().y();
    double u1 = 0, u2 = 1, r;
    int p[4], q[4];
    bool flag = false;
    // 计算p, q的值
    p[0] = x1 - x2;
    p[1] = x2 - x1;
    p[2] = y1 - y2;
    p[3] = y2 - y1;
    q[0] = x1 - recMin_x;
    q[1] = recMax_x - x1;
    q[2] = y1 - recMin_y;
    q[3] = recMax_y - y1;
    for(int i = 0; i < 4; i++) {
        r = (double)(q[i])/(double)(p[i]);
        if(p[i] < 0) {
            u1 = u1 > r ? u1 : r;
            if(u1 > u2) {
                flag = true;
            }
        }
        else if(p[i] > 0) {
            u2 = u2 < r ? u2 : r;
            if(u1 > u2) {
                flag = true;
            }
        }
        else if(p[i] == 0 && q[i] < 0) {
            flag = true;
        }
        else
            ;
    }
    if(flag) {
        //shape->drawMyself(image, color);
        // 直线不在裁剪框内
        return;
    }
    int nX1 = x1+u1*(x2-x1);   // 否则确定在框内的直线端点坐标
    int nX2 = x1+u2*(x2-x1);
    int nY1 = y1+u1*(y2-y1);
    int nY2 = y1+u2*(y2-y1);
    shape->setPoint(QPoint(nX1, nY1), QPoint(nX2, nY2));
    shape->drawMyself(image, color);
}
