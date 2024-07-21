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
#include <QStringList>
#include <QFormLayout>
#include "inputdialog.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
    QHBoxLayout *hbox;
////List Menu Items
    QListWidget *listMenu;
    QPushButton * hideButton;
    QListWidgetItem *profile;
    QListWidgetItem *medicines;
    QListWidgetItem *ordersAndDelivery;
    QListWidgetItem *staff;
    QListWidgetItem *salesAndReports;
    QListWidgetItem *bills;
    QListWidgetItem *customers;
    QListWidgetItem *item;
////List Menu Items
////Medicines Menu
    QTableWidget *medicinesTable;
    QPushButton *searchButton;
    QLineEdit *searchBar;
    QTableWidgetItem *itemTable;
    QPushButton *addButton;
    QTableWidgetItem *name;
    QTableWidgetItem *company;
    QTableWidgetItem *mg;
    QTableWidgetItem *price;
    QTableWidgetItem *quantity;
    InputDialog *inputMedicine;
////Medicines Menu
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void makeListMenu();
    void setListWidgetSize(QListWidget *listWidget);
    void medicinesMenu();

private slots:
    void handleAddRowButton();
    void handleHideButton();
    void currentMenu();
};
#endif // MAINWINDOW_H
