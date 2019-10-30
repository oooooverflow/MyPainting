#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("My Drawing Board"));
    Painter = new mypainter;
    Painter->setMaximumSize(800, 600);
    Painter->setMinimumSize(800, 600);
    QPalette pal(Painter->palette());
    pal.setColor(QPalette::Background, Qt::white);
    Painter->setAutoFillBackground(true);
    Painter->setPalette(pal);
    setCentralWidget(Painter);
    QToolBar *myToolBar = this->addToolBar("Tools");
    QAction *changeToLine = new QAction(QIcon(":/MyImages/images/Line.png"), tr("Line"), this);
    myToolBar->addAction(changeToLine);
    QAction *changeToCircle = new QAction(QIcon(":/MyImages/images/Circle.png"), tr("Circle"), this);
    myToolBar->addAction(changeToCircle);
    QAction *changeToEllipse = new QAction(QIcon(":/MyImages/images/Ellipse.png"), tr("Ellipse"), this);
    myToolBar->addAction(changeToEllipse);
    QAction *changeFuncToPolygon = new QAction(QIcon(":/MyImages/images/Polygon.png"), tr("Polygon"), this);
    myToolBar->addAction(changeFuncToPolygon);
    QAction *changeFuncToCurve = new QAction(QIcon(":/MyImages/images/Curve.png"), tr("Curve"), this);
    myToolBar->addAction(changeFuncToCurve);
    QAction *changeFuncToFill = new QAction(QIcon(":/MyImages/images/Fill.png"), tr("Fill"), this);
    myToolBar->addAction(changeFuncToFill);
    QAction *changeFuncToTranslation = new QAction(QIcon(":/MyImages/images/Translation.png"), tr("Translation"), this);
    myToolBar->addAction(changeFuncToTranslation);
    QAction *changeFuncToRotate = new QAction(QIcon(":/MyImages/images/Rotate.png"), tr("Rotate"), this);
    myToolBar->addAction(changeFuncToRotate);
    QAction *changeFuncToZoom = new QAction(QIcon(":/MyImages/images/Zoom.png"), tr("Zoom"), this);
    myToolBar->addAction(changeFuncToZoom);
    QAction *changeFuncToEdit = new QAction(QIcon(":/MyImages/images/Edit.png"), tr("Edit"), this);
    myToolBar->addAction(changeFuncToEdit);  
    QAction *open = new QAction(QIcon(":/MyImages/images/Open.png"), tr("Open"), this);
    myToolBar->addAction(open);
    QAction *save = new QAction(QIcon(":/MyImages/images/Save.png"), tr("Save"), this);
    myToolBar->addAction(save);
    QAction *changeFuncToCut = new QAction(QIcon(":/MyImages/images/Cut.png"), tr("Cut"), this);
    myToolBar->addAction(changeFuncToCut);
    QAction *changeFuncToColor = new QAction(QIcon(":/MyImages/images/Color.png"), tr("Color"), this);
    myToolBar->addAction(changeFuncToColor);
    connect(changeToLine, SIGNAL(triggered()), Painter, SLOT(changeShapeToLine()));
    connect(changeToCircle, SIGNAL(triggered()), Painter, SLOT(changeShapeToCircle()));
    connect(changeToEllipse, SIGNAL(triggered()), Painter, SLOT(changeShapeToEllipse()));
    connect(changeFuncToFill, SIGNAL(triggered()), Painter, SLOT(changeFuncToFill()));
    connect(changeFuncToTranslation, SIGNAL(triggered()), Painter, SLOT(changeFuncToTranslation()));
    connect(changeFuncToRotate, SIGNAL(triggered()), Painter, SLOT(changeFuncToRotate()));
    connect(changeFuncToZoom, SIGNAL(triggered()), Painter, SLOT(changeFuncToZoom()));
    connect(changeFuncToEdit, SIGNAL(triggered()), Painter, SLOT(changeFuncToEdit()));
    connect(changeFuncToPolygon, SIGNAL(triggered()), Painter, SLOT(changeFuncToPolygon()));
    connect(open, SIGNAL(triggered()), Painter, SLOT(open()));
    connect(save, SIGNAL(triggered()), Painter, SLOT(save()));
    connect(changeFuncToCut, SIGNAL(triggered()), Painter, SLOT(changeFuncToCut()));
    connect(changeFuncToCurve, SIGNAL(triggered()), Painter, SLOT(changeFuncToCurve()));
    connect(changeFuncToColor, SIGNAL(triggered()), Painter, SLOT(changeFuncToColor()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    Painter->closeEvent(event);
}
