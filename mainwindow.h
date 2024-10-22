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
#include <profilemenu.h>
#include <sliderdialog.h>
#include <QFontDialog>
#include <QVector>



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
    QString profileName;
    QString email;
////List Menu Items
////Profile Menu
    ProfileMenu *profileMenu;
    SliderDialog *sliderDialog;
////Profile Menu
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
    static QStringList orderedMedicinesName;
    static QStringList  orderedMedicinesQuantity;
////Orders&Delivery Menu
    KanbanBoard *kanbanBoard;
////Orders&Delivery Menu
////Sales&Reports Menu
    SalesAndReports *salesMenu;
    static QString order;
    static double totalForSalesAndReports;
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
    ////////////////////////////Profile Menu
    void makeProfileMenu();
    ////////////////////////////Profile Menu
    ////////////////////////////Medicine Menu
    void makeMedicinesMenu();
    ////////////////////////////Medicine Menu
    ////////////////////////////Bill Menu
    void billMenu();
    void padRight(QString& text);
    ////////////////////////////Bill Menu
    void maintainMedicinesTable(QStringList &,QStringList &);
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
    ////////////////////Profile Menu
    void handleSetFontButton();
    void handleSetOpacityButton();
    void handleSetOpacity();
    ////////////////////Profile Menu
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
