#ifndef SALESANDREPORTS_H
#define SALESANDREPORTS_H

#include <QWidget>
#include <QTableWidget>
#include <QTime>
#include <QStringList>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidgetItem>
#include <QDate>
#include <QPushButton>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <custompushbutton.h>
#include <QMultiMap>
#include <QSizePolicy>


class SalesAndReports : public QWidget
{
    Q_OBJECT
    QVBoxLayout *mainLayout;
    QVBoxLayout *buttonLayout;
    QHBoxLayout *boardLayout;
    QTableWidget *salesTable;
    QTableWidgetItem *tableItem;
    QPushButton *totalRevenue;
    QPushButton *topSellings;
    CustomPushButton *customer;
    QTableWidget *medicinesTable;
    int nOfTopSellings;


public:
    explicit SalesAndReports(QWidget *parent = nullptr,QTableWidget *newMedicinesTable=nullptr);
    void addSalesRow(double total=0.0,bool physical=true,QString customerName="N/A",QString phoneNumber="N/A",QString address="N/A",QString order="",QString orderID="N/A");
    void addSalesRowFromJSon(double total=0.0,bool physical=true,QString customerName="N/A",QString order="",QString dateAndTime="N/A",QString paymentStatus="N/A");
    void removeRow(int row);
    void setDeliveryStatus(QString customerName,QString customerOrder);
    int getNumberOfPaidTransactions();
    int getNumberOfUnPaidTransactions();
    double getTotalDuePayment();
    double getTotalPaidPayment();
    QMultiMap<int,QString> getMedicineSales();
    QString getTopSellingMedicines(int topN);
    void readFromJson();
    void writeToJson();

signals:
};

#endif // SALESANDREPORTS_H
