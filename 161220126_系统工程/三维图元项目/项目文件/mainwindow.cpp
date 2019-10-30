#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mygl.h"
#include<QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("3D 图元观察"));
    QPushButton *button = new QPushButton(this);
    button->setGeometry(QRect(100,80,200,100));
    button->setText("开始工作");
    connect(button, SIGNAL(clicked(bool)), this, SLOT(threeDShowTime()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::threeDShowTime() {
    MyGl* mygl = new MyGl;
    mygl->resize(800, 600);
    mygl->setWindowModality(Qt::ApplicationModal);
    mygl->show();
}
