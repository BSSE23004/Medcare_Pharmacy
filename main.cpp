#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Pharmacy");
    w.setWindowOpacity(0.97);
    w.setWindowIcon(QIcon(":/pharmacy.ico"));
    w.showMaximized();
    w.setMinimumSize(600,600);
    return a.exec();
}
