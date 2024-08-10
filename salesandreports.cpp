#include "salesandreports.h"

SalesAndReports::SalesAndReports(QWidget *parent)
    : QWidget{parent}
{
    noOfPaidTransactions=0;
    noOfUnPaidTransactions=0;
    revenue=0.0;
    mainLayout = new QVBoxLayout(this);
    boardLayout = new QHBoxLayout();
    salesTable =new QTableWidget(0,5);
    salesTable->setGeometry(175,0,850,700);
    salesTable->setIconSize(QSize(50,40));
    salesTable->setFont(QFont("Times New Roman",14));
    QStringList headers={"Date","Customer","SalesType","Payment Status","Total"};
    salesTable->setHorizontalHeaderLabels(headers);
    for (int i = 0; i < salesTable->columnCount(); ++i) {
        salesTable->setColumnWidth(i,150);
    }
    totalRevenue =new QPushButton();
    totalRevenue->setMinimumHeight(200);
    totalRevenue->setMinimumWidth(200);
    totalRevenue->setIcon(QIcon(":/cash.ico"));
    totalRevenue->setIconSize(QSize(70,70));
    totalRevenue->setText("Total Revenue : "+QString::number(revenue)+"PKR"+"\n-----------------------\n"+"Paid = "+QString::number(noOfPaidTransactions)+"\n-----------------------\n"+"Unpaid = "+QString::number(noOfUnPaidTransactions));
    totalRevenue->setFont(QFont("Times New Roman",18));
    totalRevenue->setStyleSheet("color : green");
    boardLayout->addWidget(salesTable);
    boardLayout->addWidget(totalRevenue);
    mainLayout->addLayout(boardLayout);
    setLayout(mainLayout);
}

void SalesAndReports::addSalesRow(double total, bool physical, QString customerName)
{
    salesTable->setColumnWidth(0,170);
    salesTable->setColumnWidth(4,127);
    revenue+=total;
    QTime currentTime =QTime::currentTime();
    QDate currentDate =QDate::currentDate();
    QString date =currentDate.toString("dd/MMM/yyyy");
    QString time=currentTime.toString("hh:mm");
    salesTable->setRowCount(salesTable->rowCount()+1);
    tableItem =new QTableWidgetItem(QIcon(":/calender.ico"),time+"\n"+date);
    tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
    salesTable->setItem(salesTable->rowCount()-1,0,tableItem);
    tableItem =new QTableWidgetItem(QIcon(":/customer.ico"),customerName);
    tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
    salesTable->setItem(salesTable->rowCount()-1,1,tableItem);
    if(physical){
        tableItem =new QTableWidgetItem(QIcon(":/user.ico"),"Physical");
        tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
        salesTable->setItem(salesTable->rowCount()-1,2,tableItem);
        tableItem =new QTableWidgetItem(QIcon(":/done.ico"),"Paid");
        /////increasing counter
        ++noOfPaidTransactions;
        tableItem->setForeground(QColor(Qt::green));
        tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
        salesTable->setItem(salesTable->rowCount()-1,3,tableItem);
    }else{
        tableItem =new QTableWidgetItem(QIcon(":/delivery-bike.ico"),"Delivery");
        tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
        salesTable->setItem(salesTable->rowCount()-1,2,tableItem);
        tableItem =new QTableWidgetItem(QIcon(":/unpaid.ico"),"UnPaid");
        /////increasing counter
        ++noOfUnPaidTransactions;
        tableItem->setForeground(QColor(Qt::red));
        tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
        salesTable->setItem(salesTable->rowCount()-1,3,tableItem);
    }
    tableItem =new QTableWidgetItem(QIcon(":/growth.ico"),QString::number(total));
    tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
    salesTable->setItem(salesTable->rowCount()-1,4,tableItem);
    for (int i = 0; i < salesTable->rowCount(); ++i) {
        salesTable->setRowHeight(i,60);
    }
    totalRevenue->setText("Total Revenue : "+QString::number(revenue)+"PKR"+"\n-----------------------\n"+"Paid = "+QString::number(noOfPaidTransactions)+"\n-----------------------\n"+"Unpaid = "+QString::number(noOfUnPaidTransactions));

}

void SalesAndReports::removeRow(int row)
{
    salesTable->removeRow(row);
}

void SalesAndReports::setDeliveryStatus(QString customerName)
{
    for (int rows = 0; rows < salesTable->rowCount(); ++rows) {
        if(salesTable->item(rows,1)->text()==customerName){
            tableItem =new QTableWidgetItem(QIcon(":/done.ico"),"Paid");
            ///////MaintainingCounter
            ++noOfPaidTransactions;
            --noOfUnPaidTransactions;
            tableItem->setForeground(QColor(Qt::green));
            tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
            salesTable->setItem(rows,3,tableItem);
        }
    }
    totalRevenue->setText("Total Revenue : "+QString::number(revenue)+"PKR"+"\n-----------------------\n"+"Paid = "+QString::number(noOfPaidTransactions)+"\n-----------------------\n"+"Unpaid = "+QString::number(noOfUnPaidTransactions));
}

SalesAndReports::~SalesAndReports()
{
    delete mainLayout;
    delete boardLayout;
    delete salesTable;
    delete tableItem;
    delete totalRevenue;
}
