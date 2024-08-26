#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QTimer>
#include <inputdialog.h>
#include <billinputdialog.h>
#include <QtPrintSupport/QPrinter>
#include <QPainter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <kanbanboard.h>
#include <salesandreports.h>
#include <customercare.h>
#include <staffmenu.h>
#include <medicinesmenu.h>
#include <signuppage.h>



class MainWindow : public QMainWindow
{
    Q_OBJECT
////1st Window
    SignUpPage *loginPage;
////List Menu Items
    QListWidget *listMenu;
    QPushButton * hideButton;
    QListWidgetItem *listItems;
    QListWidgetItem *item;
////List Menu Items
////Medicines Menu
    MedicinesMenu *medicinesMenu;
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
////Sales&Reports Menu
    SalesAndReports *salesMenu;
////Sales&Reports Menu
////CustomerCare Menu
    CustomerCare *customerCare;
////CustomerCare Menu
////Staff Menu
    StaffMenu *staffOption;
////Staff Menu
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void makeListMenu();
    void setListWidgetSize(QListWidget *listWidget);
    ////////////////////////////Medicine Menu
    void makeMedicinesMenu();
    ////////////////////////////Medicine Menu
    ////////////////////////////Bill Menu
    void billMenu();
    void padRight(QString& text);
    ////////////////////////////Bill Menu
    ////////////////////////////Orders&Delivery Menu
    void ordersAndDeliveryMenu();
    ////////////////////////////Orders&Delivery Menu
    ////////////////////////////Sales&Reports Menu
    void salesAndReportsMenu();
    ////////////////////////////Sales&Reports Menu
    ////////////////////////////CustomerCare Menu
    void customerCareMenu();
    ////////////////////////////CustomerCare Menu
    ////////////////////////////Staff Menu
    void staffMenu();
    ////////////////////////////Staff Menu
private slots:
    ////////////////////1st Window
    void onSignUpButtonClicked();
    void onSignUpLabelClicked();
    ////////////////////Medicine Menu

    ////////////////////Medicine Menu
    ////////////////////List Menu
    void handleHideButton();
    void currentMenu();
    ////////////////////List Menu
    ////////////////////Bill Menu
    void handleBillButton();
    void handleOrderButton();
    void handleLineEdits();
    void printReceipt(QString& receiptText);
    void handleReceiptButton();
    ////////////////////Bill Menu
    ////////////////////SalesAndReports Menu
    void handleDoneList();
    ////////////////////SalesAndReports Menu
};
#endif // MAINWINDOW_H
