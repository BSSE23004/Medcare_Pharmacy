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
// #include <QTabWidget>
#include <QPushButton>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <nlohmann/json.hpp>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <custompushbutton.h>

using namespace nlohmann;

class SalesAndReports : public QWidget
{
    Q_OBJECT
    QVBoxLayout *mainLayout;
    QHBoxLayout *boardLayout;
    QTableWidget *salesTable;
    QTableWidgetItem *tableItem;
    QPushButton *totalRevenue;
    QPushButton *customer;


public:
    explicit SalesAndReports(QWidget *parent = nullptr);
    void addSalesRow(double total=0.0,bool physical=true,QString customerName="N/A",QString phoneNumber="N/A",QString address="N/A",QString order="",QString orderID="N/A");
    void addSalesRowFromJSon(double total=0.0,bool physical=true,QString customerName="N/A",QString order="",QString dateAndTime="N/A",QString paymentStatus="N/A");
    void removeRow(int row);
    void setDeliveryStatus(QString customerName,QString customerAddress,QString customerPhoneNumber);
    int getNumberOfPaidTransactions();
    int getNumberOfUnPaidTransactions();
    double getTotalDuePayment();
    double getTotalPaidPayment();
    void readFromJson();
    void writeToJson();
    ~SalesAndReports();

signals:
};

#endif // SALESANDREPORTS_H
