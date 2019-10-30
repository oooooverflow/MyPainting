#ifndef MYGL_H
#define MYGL_H

#include <QWidget>
#include <QGLWidget>
#include <glut.h>
#include <GL/glu.h>
#include <QKeyEvent>
#include <windows.h>
#include <vector>
#include <QFileDialog>
#include <fstream>
#include <string>
#include <iostream>
#include <QTextCodec>
using namespace std;

// 存储顶点坐标
struct Vertex {
    double x;   // 顶点坐标
    double y;
    double z;
    Vertex(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

// 存储构成一个面的顶点信息
struct Plane {
    int num;    // 顶点数
    int *vertex;    // 顶点数组
    Plane(int num, int *arr) {
        vertex = new int[num];
        this->num = num;
        for(int i = 0; i < num; i++) {
            vertex[i] = arr[i];
        }
    }
};

class MyGl : public QGLWidget {
    Q_OBJECT
public:
    explicit MyGl(QWidget *parent = 0);
    ~MyGl();

protected:
    void initializeGL();        //初始化当前的opengl环境
    void resizeGL(int w, int h);//主要用来对渲染区域的高度和宽度进行一些变化处理
    void paintGL();             //绘制
    void keyPressEvent(QKeyEvent *event);   //捕捉键盘事件以控制观察视角


private:
    GLfloat leftright;
    GLfloat updown;
    GLfloat scale;
    QString file;
    vector<Vertex> vertexs;
    vector<Plane> planes;
    bool loadFile(QString filename);
};


#endif // MYGL_H
