#include "mainwindow.h"
//#include "mypainter.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow myWindow;
    myWindow.show();

    return a.exec();
}
