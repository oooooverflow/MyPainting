#ifndef CUT_H
#define CUT_H

#include "line.h"

class Cut
{
public:
    Cut();
    void doCut(QImage* image, QPoint recMin, QPoint recMax, Shape* &shape, QColor* color);  // 可编辑矩形框裁剪
};

#endif // SHORTCUT_H
