#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QMovie>
#include <QPushButton>
#include <QMenu>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QRadioButton>
#include <QCheckBox>
#include <QSpinBox>
#include <QLCDNumber>
#include <QTime>
#include <QTimer>
#include <QComboBox>
#include <QSlider>
#include <QListWidget>
#include <QFontComboBox>
#include <QTextEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSizePolicy>
#include <QCalendarWidget>
#include <QInputDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QSizeGrip>
#include <QSizePolicy>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QVBoxLayout *vbox;
    QListWidget *listMenu;
    QPushButton * hideButton;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void makeListMenu();
    void setListWidgetSize(QListWidget *listWidget);

private slots:
    void handleHideButton();
    void changeProfileButton();
};
#endif // MAINWINDOW_H
