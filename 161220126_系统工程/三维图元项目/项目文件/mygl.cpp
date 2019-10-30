#include "mygl.h"

MyGl::MyGl(QWidget *parent) : QGLWidget(parent) {
    leftright = 0.0f;
    updown = 0.0f;
    scale = 1.0f;
    setWindowState(Qt::WindowMaximized);
    file = "d:\\";
}

MyGl::~MyGl() {}

void MyGl::keyPressEvent(QKeyEvent *event) {
    QString filePath;
    switch(event->key()) {
    case Qt::Key_F:
        filePath = QFileDialog::getOpenFileName(this, tr("打开文件"), file, tr("off (*.off)"));
        file = filePath;
        if (loadFile(file)) {
            paintGL();
        }
        break;
    case Qt::Key_A:
        leftright -= 1.5f;
        updateGL();
        break;
    case Qt::Key_D:
        leftright += 1.5f;
        updateGL();
        break;
    case Qt::Key_W:
        updown -= 1.5f;
        updateGL();
        break;
    case Qt::Key_S:
        updown += 1.5f;
        updateGL();
        break;
    case Qt::Key_O:
        scale *= 1.2f;
        updateGL();
        break;
    case Qt::Key_P:
        scale /= 1.2f;
        updateGL();
        break;
    }
}

bool MyGl::loadFile(QString filename) {
    vertexs.clear();
    planes.clear();
    ifstream fin;
    QTextCodec *code = QTextCodec::codecForName("GB2312");//解决中文路径问题
    std::string name = code->fromUnicode(filename).data();
    fin.open(name);
    if (!fin) {
        return false;
    }
    string str;
    getline(fin, str);
    if (str != "OFF") {
        //qDebug() << "load wrong file!" << endl;
        return false;
    }
    int vertex, plane, line;
    fin >> vertex >> plane >> line;
    double x, y, z;
    for (int i = 0; i < vertex; i++) {
        fin >> x>> y>> z;
        Vertex v(x, y, z);
        vertexs.push_back(v);
    }
    int *arr;
    for (int i = 0; i < plane; i++) {
        int num;
        fin >> num;
        arr = new int[num];
        for(int j = 0; j < num; j++) {
            fin >> arr[j];
        }
        Plane p(num, arr);
        planes.push_back(p);
    }
    return true;
}

void MyGl::initializeGL() {
    glClearColor(0.0, 0.0, 0.0, 0.0);                   //黑色背景
    glShadeModel(GL_SMOOTH);                            //启用阴影平滑
    glClearDepth(1.0);                                  //设置深度缓存
    glEnable(GL_DEPTH_TEST);                            //启用深度测试
    glDepthFunc(GL_LEQUAL);                             //所作深度测试的类型
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  //告诉系统对透视进行修正
}

void MyGl::resizeGL(int w, int h) {
    glViewport(0, 0, (GLint)w, (GLint)h);               //重置当前的视口
    glMatrixMode(GL_PROJECTION);                        //选择投影矩阵
    glLoadIdentity();                                   //重置投影矩阵
    gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 0.1, 100.0);//设置视口的大小
    glMatrixMode(GL_MODELVIEW);                         //选择模型观察矩阵
    glLoadIdentity();
}

void MyGl::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除屏幕和深度缓存
    glLoadIdentity();                                   //重置当前的模型观察矩阵
    glTranslatef(0.0, 0.0, -7.0);                    //左移1.5单位，并移入屏幕7.0单位
    glRotatef(leftright, 0.0, 1.0, 0.0);
    glRotatef(updown, 1.0, 0.0, 0.0);
    glScalef(scale, scale, scale);
    for (int i = 0; i < planes.size(); i++) {
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_TRIANGLES);                      //绘制面
        for(int j = 0; j < planes[i].num; j++) {
            glVertex3f(vertexs[planes[i].vertex[j]].x, vertexs[planes[i].vertex[j]].y, vertexs[planes[i].vertex[j]].z);
        }
        glEnd();
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINES);                          //绘制纹理
        for(int j = 0; j < planes[i].num; j++) {
            glVertex3f(vertexs[planes[i].vertex[j]].x, vertexs[planes[i].vertex[j]].y, vertexs[planes[i].vertex[j]].z);
        }
        for(int j = 0; j < planes[i].num; j++) {
            glVertex3f(vertexs[planes[i].vertex[j]].x, vertexs[planes[i].vertex[j]].y, vertexs[planes[i].vertex[j]].z);
        }
        glEnd();
    }
}
