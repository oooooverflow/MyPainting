#include "mypainter.h"
#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QColorDialog>

mypainter::mypainter(QWidget *parent) : QWidget(parent) {
    currentShape = 0;
    currentFunc = 0;
    image = new QImage(800, 600, QImage::Format_ARGB32);
    fill = new Fill();
    translation = new Translation;
    rotate = new Rotate;
    zoom = new Zoom;
    edit = new Edit;
    theShape = new Shape;
    newImage = new QImage();
    bufferImage = new QImage();
    (*newImage) = image->copy();
    (*bufferImage) = image->copy();
    isAnchor = 0;
    isModified = false;
    cut = new Cut();
    curve = new MyCurve();
    color = new QColor(0, 0, 0);
}

void mypainter::mousePressEvent(QMouseEvent *event) {
    start = event->pos();
    if(event->button() == Qt::LeftButton) {
        if((isAnchor = judgeIsAnchor(start)) != 0 && currentFunc == 5) {    // 判断是否为控制点
            this->setCursor(Qt::SizeHorCursor);     // 尺寸型
        }
        else if(currentFunc == 6)
            this->setCursor(Qt::CrossCursor);       // 十字型
        else if(currentFunc == 0)
            (*image) = (*bufferImage);
        else
            this->setCursor(Qt::ArrowCursor);       // 箭头型
    }
    else if(event->button() == Qt::RightButton) {   //右击鼠标则完成该图形绘制与编辑，此后不可修改该图元
        (*image) = (*bufferImage);
        (*newImage) = (*image);
        currentFunc = -1;
        theShape = new Shape();
        update();
    }
}

void mypainter::mouseReleaseEvent(QMouseEvent *event) {
    end = event->pos();
    switch(currentFunc) {          //其他功能
        case 0: {
            if(!isModified)
                isModified = true;
            //(*newImage) = (*image);
            break;
        }
        case 1: {
            if(!isModified)
                isModified = true;
            (*newImage) = (*image);
            fill->fillTheArea(start, newImage, color);
            (*bufferImage) = (*newImage);
            (*image) = (*bufferImage);
            break;
        }
        case 2: {
            if(!isModified)
                isModified = true;
            (*newImage) = (*image);
            if(currentShape == 4)
                polygon = translation->translationTheShape(polygon, start, end, newImage, color);
            else if(currentShape == 5)
                curve = translation->translationTheShape(curve, start, end, newImage, color);
            else
                theShape = translation->translationTheShape(theShape, currentShape, start, end, newImage, color);
            (*bufferImage) = (*newImage);
            break;
        }
        case 3: {
            if(!isModified)
                isModified = true;
            (*newImage) = (*image);
            if(currentShape == 4)
                polygon = rotate->rotateTheShape(polygon, start, end, newImage, color);
            else if(currentShape == 5)
                curve = rotate->rotateTheShape(curve, start, end, newImage, color);
            else
                theShape = rotate->rotateTheShape(theShape, currentShape, start, end, newImage, color);
            (*bufferImage) = (*newImage);
            break;
        }
        case 4: {
            if(!isModified)
                isModified = true;
            (*newImage) = (*image);
            if(currentShape == 4)
                polygon = zoom->zoomTheShape(polygon, start, end, newImage, color);
            else if(currentShape == 5)
                curve = zoom->zoomTheShape(curve, start, end, newImage, color);
            else
                theShape = zoom->zoomTheShape(theShape, currentShape, start, end, newImage, color);
            (*bufferImage) = (*newImage);
            break;
        }
        case 5: {
            if(isAnchor != 0) {
                if(!isModified)
                    isModified = true;
                (*newImage) = (*image);
                if(currentShape == 4)
                    polygon = edit->editTheShape(polygon, newImage, end, isAnchor, color);
                else if(currentShape == 5)
                    curve = edit->editTheShape(curve, newImage, end, isAnchor, color);
                else
                    theShape = edit->editTheShape(theShape, currentShape, newImage, end, isAnchor, color);
                (*bufferImage) = (*newImage);
                drawTheAnchor();
            }
            break;
        }
        case 6: {
            if(!polygon->isdone && polygon->lines.size() != 0) {
                if(!isModified)
                    isModified = true;
                (*newImage) = (*bufferImage);
                int distance = sqrt((end.x()-polygon->lines[0].x())*(end.x()-polygon->lines[0].x())+(end.y()-polygon->lines[0].y())*(end.y()-polygon->lines[0].y()));
                if(distance <= 3) {
                    polygon->isdone = true;
                }
                else
                    polygon->lines.push_back(end);
                polygon->drawMyself(newImage, color);
                (*bufferImage) = (*newImage);
                if(!polygon->isdone)
                    drawTheAnchor();
            }
            else if(polygon->isdone) {
                (*newImage) = (*bufferImage);
                polygon = new MyPolygon();
                polygon->isdone = false;
                polygon->lines.push_back(end);
                drawTheAnchor();
            }
            else {
                (*newImage) = (*image);
                (*bufferImage) = (*newImage);
                polygon->lines.push_back(end);
                drawTheAnchor();
            }
            break;
        }
        case 7: {
            if(currentShape == 1) {
                int x1 = start.x() < end.x() ? start.x() : end.x();
                int x2 = start.x() > end.x() ? start.x() : end.x();
                int y1 = start.y() < end.y() ? start.y() : end.y();
                int y2 = start.y() > end.y() ? start.y() : end.y();
                (*newImage) = (*image);
                cut->doCut(newImage, QPoint(x1, y1), QPoint(x2, y2), theShape, color);
                (*bufferImage) = (*newImage);
            }
            break;
        }
        case 8: {
            (*newImage) = (*image);
            if(!isModified)
                isModified = true;
            curve->anchors.push_back(end);
            if(curve->anchors.size() > 1)
                curve->drawTheCurve(newImage, color);
            (*bufferImage) = (*newImage);
            break;
        }
        default:break;
    }
    update();
}

void mypainter::mouseMoveEvent(QMouseEvent *event) {
    end = event->pos();
    //this->setCursor(Qt::CrossCursor);
    switch(currentFunc) {          //其他功能
        case 0: {
            (*newImage) = image->copy();
            //(*newImage) = (*bufferImage);
            switch(currentShape) {          //绘制当前正在画的图形
                case 1: {
                    theShape = new MyLine;
                    theShape->setPoint(start, end);
                    theShape->drawMyself(newImage, color);
                    (*bufferImage) = (*newImage);
                    break;
                }
                case 2: {
                    theShape = new MyCircle;
                    theShape->setPoint(start, end);
                    theShape->drawMyself(newImage, color);
                    (*bufferImage) = (*newImage);
                    break;
                }
                case 3: {
                    theShape = new MyEllipse;
                    theShape->setPoint(start, end);
                    theShape->drawMyself(newImage, color);
                    (*bufferImage) = (*newImage);
                    break;
                }
                default: {
                    break;
                }
            }
            break;
        }
        case 1: {
            return;
        }
        case 2: {
            (*newImage) = image->copy();
            if(currentShape == 4)
                translation->translationTheShape(polygon, start, end, newImage, color);
            else if(currentShape == 5)
                translation->translationTheShape(curve, start, end, newImage, color);
            else
                translation->translationTheShape(theShape, currentShape, start, end, newImage, color);
            (*bufferImage) = (*newImage);
            break;
        }
        case 3: {
            (*newImage) = image->copy();
            if(currentShape == 4)
                rotate->rotateTheShape(polygon, start, end, newImage, color);
            else if(currentShape == 5)
                rotate->rotateTheShape(curve, start, end, newImage, color);
            else
                rotate->rotateTheShape(theShape, currentShape, start, end, newImage, color);
            (*bufferImage) = (*newImage);
            break;
        }
        case 4: {
            (*newImage) = image->copy();
            if(currentShape == 4)
                zoom->zoomTheShape(polygon, start, end, newImage, color);
            else if(currentShape == 5)
                zoom->zoomTheShape(curve, start, end, newImage, color);
            else
                zoom->zoomTheShape(theShape, currentShape, start, end, newImage, color);
            (*bufferImage) = (*newImage);
            break;
        }
        case 5: {
            if(isAnchor != 0) {
                (*newImage) = image->copy();
                if(currentShape == 4)
                    polygon = edit->editTheShape(polygon, newImage, end, isAnchor, color);
                else if(currentShape == 5)
                    curve = edit->editTheShape(curve, newImage, end, isAnchor, color);
                else
                    theShape = edit->editTheShape(theShape, currentShape, newImage, end, isAnchor, color);
                (*bufferImage) = (*newImage);
                drawTheAnchor();
            }
            break;
        }
        case 6: {
            break;
        }
        case 7: {
            (*newImage) = (*bufferImage);
            MyLine* tmp = new MyLine();
            tmp->setPoint(start, QPoint(end.x(), start.y()));
            tmp->drawMyself(newImage, color);
            tmp->setPoint(QPoint(end.x(), start.y()), end);
            tmp->drawMyself(newImage, color);
            tmp->setPoint(start, QPoint(start.x(), end.y()));
            tmp->drawMyself(newImage, color);
            tmp->setPoint(QPoint(start.x(), end.y()), end);
            tmp->drawMyself(newImage, color);
            //(*bufferImage) = (*newImage);
            break;
        }
        case 8: {
            break;
        }
        default:break;
    }
    update();
}

void mypainter::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), *newImage);
}

void mypainter::changeShapeToLine() {
    this->setCursor(Qt::CrossCursor);
    currentShape = 1;
    currentFunc = 0;
    (*image) = (*bufferImage);
}

void mypainter::changeShapeToCircle() {
    this->setCursor(Qt::CrossCursor);
    currentShape = 2;
    currentFunc = 0;
    (*image) = (*bufferImage);
}

void mypainter::changeShapeToEllipse() {
    this->setCursor(Qt::CrossCursor);
    currentShape = 3;
    currentFunc = 0;
    (*image) = (*bufferImage);
}

void mypainter::changeFuncToFill() {
    this->setCursor(Qt::PointingHandCursor);
    currentShape = 0;
    currentFunc = 1;
    (*image) = (*bufferImage);
}

void mypainter::changeFuncToTranslation() {
    currentFunc = 2;
}

void mypainter::changeFuncToRotate() {
    currentFunc = 3;
}

void mypainter::changeFuncToZoom() {
    currentFunc = 4;
}

void mypainter::changeFuncToEdit() {
    currentFunc = 5;
    if(currentShape != 0)
        drawTheAnchor();
    update();
}

void mypainter::changeFuncToPolygon() {
    this->setCursor(Qt::CrossCursor);
    currentFunc = 6;
    currentShape = 4;
    polygon = new MyPolygon();
    polygon->isdone = false;
    (*image) = (*bufferImage);
}

void mypainter::changeFuncToCut() {
    currentFunc = 7;
}

void mypainter::changeFuncToCurve() {
    currentFunc = 8;
    currentShape = 5;
    (*image) = (*bufferImage);
}

void mypainter::changeFuncToColor() {   // 选择画笔颜色
    QColor pre = (*color);  // 先存储先前的颜色
    (*color) = QColorDialog::getColor(Qt::black, this, tr("颜色选择"), QColorDialog::ShowAlphaChannel); // 用户选择颜色
    if(!color->isValid()) { // 获取的颜色是否有效
        (*color) = pre;     // 无效则将之前的颜色赋值给color
    }
}

void mypainter::open() {    // 打开图片
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg *.png)"));   // 获取文件选择对话框
    if(path.length() == 0) {    // 文件名为空
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    } else {                    // 加载文件并赋值给项目中的QImage类对象
        image->load(path);
        (*newImage) = (*image);
        (*bufferImage) = (*image);
        update();               // 调用update绘制该图片
    }
}

void mypainter::save() {    // 保存图片
    QString Filename = QFileDialog::getSaveFileName(this,tr("Save Image"),"",tr("*.png;;*.jpg"));   // 获取文件选择的对话框
    if (Filename.isEmpty()) {   // 文件名为空
        QMessageBox::information(this, tr("Failed to save the image"), tr("Failed to save the image!"));
    }
    else {                      // 保存图片
        (*image) = (*bufferImage);
        image->save(Filename, "PNG", 100);
        QMessageBox::information(this, tr("Save successfully"), tr("Save successfully"));
        isModified = false;
        update();
    }
}

void mypainter::drawTheAnchor() {
    if(currentShape == 4) {
        for(int i = 0; i < polygon->lines.size(); i++) {
            int x = polygon->lines[i].x(), y = polygon->lines[i].y();
            for(int j = x-1; j <= x+1; j++) {
                for(int k = y-1; k <= y+1; k++)
                    newImage->setPixelColor(j, k, (*color));
            }
        }
    }
    else if(currentShape == 5) {
        for(int i = 0; i < curve->anchors.size(); i++) {
            int x = curve->anchors[i].x(), y = curve->anchors[i].y();
            for(int j = x-1; j <= x+1; j++) {
                for(int k = y-1; k <= y+1; k++)
                    newImage->setPixelColor(j, k, (*color));
            }
        }
    }
    else {
        int x1 = theShape->getStart().x(), x2 = theShape->getEnd().x(), y1 = theShape->getStart().y(), y2 = theShape->getEnd().y();
        int nX1 = x1, nX2 = x2, nY1 = y1, nY2 = y2;
        double angle = theShape->getAngle();
        if(angle != 0) {
            nX1 = rotate->getNewX(x1, (x1+x2)/2, y1, (y1+y2)/2, angle);
            nY1 = rotate->getNewY(x1, (x1+x2)/2, y1, (y1+y2)/2, angle);
            nX2 = rotate->getNewX(x2, (x1+x2)/2, y2, (y1+y2)/2, angle);
            nY2 = rotate->getNewY(x2, (x1+x2)/2, y2, (y1+y2)/2, angle);
        }
        for(int i = nX1-1; i <= nX1+1; i++) {
            for(int j = nY1-1; j <= nY1+1; j++)
                newImage->setPixelColor(i, j, (*color));
        }
        for(int i = nX2-1; i <= nX2+1; i++) {
            for(int j = nY2-1; j <= nY2+1; j++)
                newImage->setPixelColor(i, j, (*color));
        }
    }
}

int mypainter::judgeIsAnchor(QPoint point) {
    if(currentShape == 4) {
        for(int i = 0; i < polygon->lines.size(); i++) {
            int distance = sqrt((point.x()-polygon->lines[i].x())*(point.x()-polygon->lines[i].x())+(point.y()-polygon->lines[i].y())*(point.y()-polygon->lines[i].y()));
            if(distance <= 3)
                return i+1;
        }
        return 0;
    }
    else if(currentShape == 5) {
        for(int i = 0; i < curve->anchors.size(); i++) {
            int distance = sqrt((point.x()-curve->anchors[i].x())*(point.x()-curve->anchors[i].x())+(point.y()-curve->anchors[i].y())*(point.y()-curve->anchors[i].y()));
            if(distance <= 3)
                return i+1;
        }
        return 0;
    }
    else {
        int x1 = theShape->getStart().x(), x2 = theShape->getEnd().x(), y1 = theShape->getStart().y(), y2 = theShape->getEnd().y();
        int nX1 = x1, nX2 = x2, nY1 = y1, nY2 = y2;
        double angle = theShape->getAngle();
        if(angle != 0) {
            nX1 = rotate->getNewX(x1, (x1+x2)/2, y1, (y1+y2)/2, angle);
            nY1 = rotate->getNewY(x1, (x1+x2)/2, y1, (y1+y2)/2, angle);
            nX2 = rotate->getNewX(x2, (x1+x2)/2, y2, (y1+y2)/2, angle);
            nY2 = rotate->getNewY(x2, (x1+x2)/2, y2, (y1+y2)/2, angle);
        }
        QPoint sta = QPoint(nX1, nY1);
        QPoint en = QPoint(nX2, nY2);
        int distance1 = sqrt((point.x()-sta.x())*(point.x()-sta.x())+(point.y()-sta.y())*(point.y()-sta.y()));
        int distance2 = sqrt((point.x()-en.x())*(point.x()-en.x())+(point.y()-en.y())*(point.y()-en.y()));
        if(distance1 <= 3)
            return 1;
        else if(distance2 <= 3)
            return 2;
        return 0;
    }
}

void mypainter::closeEvent(QCloseEvent *event) {
    QMessageBox msgBox;
    if(isModified){
        msgBox.setText("The Image has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
            case QMessageBox::Save:
                save();
                break;
            case QMessageBox::Discard:
                // Don't Save was clicked
                break;
            case QMessageBox::Cancel:
                return;
                // Cancel was clicked
                break;
            default:
                // should never be reached
                break;
        }
            exit(0);
    }
    else
        exit(0);
}
