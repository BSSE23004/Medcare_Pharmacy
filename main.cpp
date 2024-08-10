#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("Fusion");
    MainWindow w;
    w.setWindowTitle("Pharmacy");
    w.setWindowOpacity(0.9);
    w.setWindowIcon(QIcon(":/pharmacy.ico"));
    w.showMaximized();
    w.setMinimumSize(600,600);
    return a.exec();
}
