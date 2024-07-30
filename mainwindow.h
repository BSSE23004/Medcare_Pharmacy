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
#include <fstream>
#include "inputdialog.h"
#include "nlohmann/json.hpp"
#include <QJsonArray>
#include <QJsonObject>
#include "billinputdialog.h"
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QtPrintSupport/QPrintDialog>
#include <QString>
#include <QApplication>
#include <QPrinter>
#include <QPainter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include "kanbanboard.h"


using namespace nlohmann;

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
    QPushButton *removeButton;
    QTableWidgetItem *name;
    QTableWidgetItem *company;
    QTableWidgetItem *mg;
    QTableWidgetItem *price;
    QTableWidgetItem *quantity;
    InputDialog *inputMedicine;
////Medicines Menu
////Bill Menu
    QPushButton *generateBillButton;
    QPushButton *generateReceiptButton;
    BillInputDialog *billInput;
    QTimer *checkTimer;
    QString receiptText;
    double total;
////Bill Menu
////Orders&Delivery Menu
    KanbanBoard *kanbanBoard;

////Orders&Delivery Menu


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void makeListMenu();
    void setListWidgetSize(QListWidget *listWidget);
    ////////////////////////////Medicine Menu
    void medicinesMenu();
    void filterTable(const QString &text);
    void writeMedicinesTableToJson();
    void readMedicineTableFromJson();
    ////////////////////////////Medicine Menu
    ////////////////////////////Bill Menu
    void billMenu();
    void padRight(QString& text);
    ////////////////////////////Bill Menu
    ////////////////////////////Orders&Delivery Menu
    void ordersAndDeliveryMenu();
    ////////////////////////////Orders&Delivery Menu
private slots:
    ////////////////////Medicine Menu
    void handleSearchBarAndButton();
    void handleRemoveRowButton();
    void handleAddRowButton();
    ////////////////////Medicine Menu
    ////////////////////List Menu
    void handleHideButton();
    void currentMenu();
    ////////////////////List Menu
    ////////////////////Bill Menu
    void handleBillButton();
    void handleLineEdits();
    void printReceipt(QString& receiptText);
    void handleReceiptButton();
    ////////////////////Bill Menu
};
#endif // MAINWINDOW_H
