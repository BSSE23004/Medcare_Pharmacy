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
class SalesAndReports : public QWidget
{
    Q_OBJECT
    QVBoxLayout *mainLayout;
    QHBoxLayout *boardLayout;
    QTableWidget *salesTable;
    QTableWidgetItem *tableItem;
    QLabel *totalRevenue;
    double revenue;


public:
    explicit SalesAndReports(QWidget *parent = nullptr);
    void addSalesRow(double total=0.0,bool physical=true,QString customerName="N/A");
    void removeRow(int row);
    ~SalesAndReports();

signals:
};

#endif // SALESANDREPORTS_H
