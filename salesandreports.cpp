#include "salesandreports.h"

SalesAndReports::SalesAndReports(QWidget *parent)
    : QWidget{parent}
{
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
    totalRevenue->setText("Total Revenue : "+QString::number(getTotalDuePayment()+getTotalPaidPayment())+"PKR"+"\n-----------------------\n"+"Paid = "
                          +QString::number(getNumberOfPaidTransactions())+"\nPaid Amount = "
                          +QString::number(getTotalPaidPayment())+"\n-----------------------\n"+"Unpaid = "
                          +QString::number(getNumberOfUnPaidTransactions())+"\nUnPaid Amount = "+QString::number(getTotalDuePayment()));
    totalRevenue->setFont(QFont("Times New Roman",18));
    totalRevenue->setStyleSheet("color : DarkCyan");
    boardLayout->addWidget(salesTable);
    boardLayout->addWidget(totalRevenue);
    mainLayout->addLayout(boardLayout);
    setLayout(mainLayout);
}

void SalesAndReports::addSalesRow(double total, bool physical, QString customerName, QString phoneNumber, QString address, QString order, QString orderID)
{
    // Read existing data from Customers.json
    QFile fIn("Customers.json");
    QJsonArray customersArray;
    if (fIn.open(QIODevice::ReadOnly)) {
        QByteArray jsonData = fIn.readAll();
        fIn.close();

        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "Parse error: " << parseError.errorString()<<"  In addSalesRow()";

        }

        if (jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();
            if (jsonObj.contains("Customers") && jsonObj["Customers"].isArray()) {
                customersArray = jsonObj["Customers"].toArray();
            } else {
                qDebug() << "Invalid JSON structure.In addSalesRow()";

            }
        } else {
            qDebug() << "JSON is not an object.In addSalesRow()";
        }
    } else {
        qDebug() << "Unable to open file.In addSalesRow()";
    }

    // Prepare new customer data
    QJsonObject customerJson;
    customerJson["Name"] = customerName;
    customerJson["PhoneNumber"] = phoneNumber;
    customerJson["Total"] = total;
    customerJson["Address"] = address;
    customerJson["Order"] = order;
    customerJson["OrderID"] = orderID;
    customerJson["PaymentType"] = physical ? "Physical" : "Delivery";

    // Prepare table items
    salesTable->setColumnWidth(0, 170);
    salesTable->setColumnWidth(4, 127);
    QTime currentTime = QTime::currentTime();
    QDate currentDate = QDate::currentDate();
    QString date = currentDate.toString("dd/MMM/yyyy");
    QString time = currentTime.toString("hh:mm");
    salesTable->setRowCount(salesTable->rowCount() + 1);

    // Date & Time
    QTableWidgetItem *tableItem = new QTableWidgetItem(QIcon(":/calender.ico"), time + "\n" + date);
    tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
    salesTable->setItem(salesTable->rowCount() - 1, 0, tableItem);

    // Customer NAME


    // Sales Type
    if (physical) {
        tableItem = new QTableWidgetItem(QIcon(":/user.ico"), "Physical");
        tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
        salesTable->setItem(salesTable->rowCount() - 1, 2, tableItem);
        CustomPushButton *customer = new CustomPushButton(QIcon(":/customer.ico"), customerName,order,true);
        salesTable->setCellWidget(salesTable->rowCount() - 1, 1, customer);
        tableItem = new QTableWidgetItem(QIcon(":/done.ico"), "Paid");
        tableItem->setForeground(QColor(Qt::green));
        tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
        salesTable->setItem(salesTable->rowCount() - 1, 3, tableItem);
    } else {
        tableItem = new QTableWidgetItem(QIcon(":/delivery-bike.ico"), "Delivery");
        tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
        salesTable->setItem(salesTable->rowCount() - 1, 2, tableItem);
        CustomPushButton *customer = new CustomPushButton(QIcon(":/customer.ico"), customerName,order,false);
        salesTable->setCellWidget(salesTable->rowCount() - 1, 1, customer);
        tableItem = new QTableWidgetItem(QIcon(":/unpaid.ico"), "UnPaid");
        tableItem->setForeground(QColor(Qt::red));
        tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
        salesTable->setItem(salesTable->rowCount() - 1, 3, tableItem);
    }

    tableItem = new QTableWidgetItem(QIcon(":/growth.ico"), QString::number(total));
    tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
    salesTable->setItem(salesTable->rowCount() - 1, 4, tableItem);

    // Append new customer to array
    customersArray.append(customerJson);

    // Write updated data back to Customers.json
    QJsonObject rootObj;
    rootObj["Customers"] = customersArray;
    QJsonDocument saveDoc(rootObj);

    QFile fOut("Customers.json");
    if (fOut.open(QIODevice::WriteOnly)) {
        fOut.write(saveDoc.toJson(QJsonDocument::Indented));
        fOut.close();
    } else {
        qDebug() << "Unable to open file for writing.In addSalesRow()";
    }
    for (int i = 0; i < salesTable->rowCount(); ++i) {
        salesTable->setRowHeight(i,60);
    }
    totalRevenue->setText("Total Revenue : "+QString::number(getTotalDuePayment()+getTotalPaidPayment())+"PKR"+"\n-----------------------\n"+"Paid = "
                          +QString::number(getNumberOfPaidTransactions())+"\nPaid Amount = "
                          +QString::number(getTotalPaidPayment())+"\n-----------------------\n"+"Unpaid = "
                          +QString::number(getNumberOfUnPaidTransactions())+"\nUnPaid Amount = "+QString::number(getTotalDuePayment()));
}


void SalesAndReports::removeRow(int row)
{
    salesTable->removeRow(row);
}

void SalesAndReports::setDeliveryStatus(QString customerName, QString customerAddress, QString customerPhoneNumber)
{
    QJsonObject jsonObj;
    QFile fIn("Customers.json");
    if (fIn.open(QIODevice::ReadOnly)) {
        QByteArray jsonData = fIn.readAll();
        fIn.close();

        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "Parse error: " << parseError.errorString()<<" In setDeliveryStatus()";
        }

        if (!jsonDoc.isObject()) {
            qDebug() << "JSON is not an object.In setDeliveryStatus()";
        }

        jsonObj = jsonDoc.object();

        if (!jsonObj.contains("Customers") || !jsonObj["Customers"].isArray()) {
            qDebug() << "Invalid JSON structure.In setDeliveryStatus()";
        }
    }

    QJsonArray customersJSONArray = jsonObj["Customers"].toArray();

    // Loop through the customers array
    for (int i = 0; i < customersJSONArray.size(); ++i) {
        QJsonObject customer = customersJSONArray[i].toObject();

        // Check if the customer matches the criteria
        if (customer["Name"] == customerName && customer["Address"] == customerAddress && customer["PhoneNumber"] == customerPhoneNumber) {
            // Update salesTable
            for (int rows = 0; rows < salesTable->rowCount(); ++rows) {
                QPushButton *button = qobject_cast<QPushButton*>(salesTable->cellWidget(rows, 1));
                if (button && button->text() == customerName) {
                    QTableWidgetItem *tableItem = new QTableWidgetItem(QIcon(":/done.ico"), "Paid");
                    tableItem->setForeground(QColor(Qt::green));
                    tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
                    salesTable->setItem(rows, 3, tableItem);
                }
            }

            // Update total revenue
            // double price = customer["Total"].toDouble();
            totalRevenue->setText("Total Revenue : "+QString::number(getTotalDuePayment()+getTotalPaidPayment())+"PKR"+"\n-----------------------\n"+"Paid = "
                                  +QString::number(getNumberOfPaidTransactions())+"\nPaid Amount = "
                                  +QString::number(getTotalPaidPayment())+"\n-----------------------\n"+"Unpaid = "
                                  +QString::number(getNumberOfUnPaidTransactions())+"\nUnPaid Amount = "+QString::number(getTotalDuePayment()));
        }
    }

}

int SalesAndReports::getNumberOfPaidTransactions()
{
    int total=0;
    for (int rows = 0; rows < salesTable->rowCount(); ++rows) {
        if(salesTable->item(rows,3)->text()=="Paid"){
            ++total;
        }
    }
    return total;
}

int SalesAndReports::getNumberOfUnPaidTransactions()
{
    int total=0;
    for (int rows = 0; rows < salesTable->rowCount(); ++rows) {
        if(salesTable->item(rows,3)->text()=="UnPaid"){
            ++total;
        }
    }
    return total;
}

double SalesAndReports::getTotalDuePayment()
{
    double totalDue=0.0;
    for (int rows = 0; rows < salesTable->rowCount(); ++rows) {
        if(salesTable->item(rows,3)->text()=="UnPaid"){
            totalDue+=salesTable->item(rows,4)->text().toDouble();
        }
    }
    return totalDue;
}

double SalesAndReports::getTotalPaidPayment()
{
    double totalPaid=0.0;
    for (int rows = 0; rows < salesTable->rowCount(); ++rows) {
        if(salesTable->item(rows,3)->text()=="Paid"){
            totalPaid+=salesTable->item(rows,4)->text().toDouble();
        }
    }
    return totalPaid;
}

SalesAndReports::~SalesAndReports()
{
    delete mainLayout;
    delete boardLayout;
    delete salesTable;
    delete tableItem;
    delete totalRevenue;
}
