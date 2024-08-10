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


class SalesAndReports : public QWidget
{
    Q_OBJECT
    QVBoxLayout *mainLayout;
    QHBoxLayout *boardLayout;
    QTableWidget *salesTable;
    QTableWidgetItem *tableItem;
    QPushButton *totalRevenue;
    double revenue;
    int noOfPaidTransactions;
    int noOfUnPaidTransactions;

public:
    explicit SalesAndReports(QWidget *parent = nullptr);
    void addSalesRow(double total=0.0,bool physical=true,QString customerName="N/A");
    void removeRow(int row);
    void setDeliveryStatus(QString customerName);
    ~SalesAndReports();

signals:
};

#endif // SALESANDREPORTS_H
