#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QIcon icon(":/icons/icons/coding-1961531-1659721.png");
    w.setWindowIcon(icon);
    w.show();
    return a.exec();
}
