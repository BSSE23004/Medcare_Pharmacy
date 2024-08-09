#include "salesandreports.h"

SalesAndReports::SalesAndReports(QWidget *parent)
    : QWidget{parent}
{
    revenue=0.0;
    mainLayout = new QVBoxLayout(this);
    boardLayout = new QHBoxLayout();
    salesTable =new QTableWidget(0,4);
    salesTable->setGeometry(175,0,850,700);
    QStringList headers={"Date","Customer","SalesType","Total"};
    salesTable->setHorizontalHeaderLabels(headers);
    for (int i = 0; i < salesTable->columnCount(); ++i) {
        salesTable->setColumnWidth(i,180);
    }
    totalRevenue =new QLabel();
    boardLayout->addWidget(salesTable);
    boardLayout->addWidget(totalRevenue);
    mainLayout->addLayout(boardLayout);
    setLayout(mainLayout);
}

void SalesAndReports::addSalesRow(double total, bool physical, QString customerName)
{
    revenue+=total;
    QTime currentTime =QTime::currentTime();
    QDate currentDate =QDate::currentDate();
    QString date =currentDate.toString("dd/mm/yyyy");
    QString time=currentTime.toString("hh:mm");
    salesTable->setRowCount(salesTable->rowCount()+1);
    tableItem =new QTableWidgetItem(QIcon(":/calender.ico"),time+" "+date);
    salesTable->setItem(salesTable->rowCount()-1,0,tableItem);
    tableItem =new QTableWidgetItem(QIcon(":/customer.ico"),customerName);
    salesTable->setItem(salesTable->rowCount()-1,1,tableItem);
    if(physical){
        tableItem =new QTableWidgetItem(QIcon(":/customer.ico"),"");
    }else{
        tableItem =new QTableWidgetItem(QIcon(":/delivery-bike.ico"),"");
    }
    salesTable->setItem(salesTable->rowCount()-1,2,tableItem);
    tableItem =new QTableWidgetItem(QIcon(":/cash.ico"),QString::number(total));
    salesTable->setItem(salesTable->rowCount()-1,3,tableItem);
    totalRevenue->setStyleSheet("color : green");
    totalRevenue->setText("<img src=':/cash.ico' /> Total Revenue : "+QString::number(revenue));
    totalRevenue->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

}

void SalesAndReports::removeRow(int row)
{
    salesTable->removeRow(row);
}

SalesAndReports::~SalesAndReports()
{
    delete mainLayout;
    delete boardLayout;
    delete salesTable;
    delete tableItem;
    delete totalRevenue;
}
