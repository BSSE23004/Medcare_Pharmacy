#include "salesandreports.h"

SalesAndReports::SalesAndReports(QWidget *parent, QTableWidget *NewMedicinesTable)
    : QWidget{parent}
{
    nOfTopSellings=5;
    medicinesTable=NewMedicinesTable;
    salesTable = new QTableWidget(0, 5);
    salesTable->setIconSize(QSize(50, 40));
    salesTable->setFont(QFont("Times New Roman", 14));
    QStringList headers = {"Date", "Customer", "SalesType", "Payment Status", "Total"};
    salesTable->setHorizontalHeaderLabels(headers);
    ////SetColumnWidth
    /// date
    salesTable->setColumnWidth(0, 155);
    /// Customer PushButton
    salesTable->setColumnWidth(1, 150);
    /// SalesType
    salesTable->setColumnWidth(2, 130);
    /// Payment Status
    salesTable->setColumnWidth(3, 135);
    /// Total
    salesTable->setColumnWidth(4, 127);

    totalRevenue = new QPushButton();
    totalRevenue->setMinimumHeight(200);
    totalRevenue->setMinimumWidth(200);
    totalRevenue->setIcon(QIcon(":/cash.ico"));
    totalRevenue->setIconSize(QSize(70, 70));
    totalRevenue->setText("Total Revenue : " + QString::number(getTotalDuePayment() + getTotalPaidPayment()) + "PKR\n-----------------------\n" +
                          "Paid = " + QString::number(getNumberOfPaidTransactions()) + "\nPaid Amount = " +
                          QString::number(getTotalPaidPayment()) + "\n-----------------------\n" +
                          "Unpaid = " + QString::number(getNumberOfUnPaidTransactions()) + "\nUnPaid Amount = " + QString::number(getTotalDuePayment()));
    totalRevenue->setFont(QFont("Times New Roman", 18));
    totalRevenue->setStyleSheet("QPushButton {"
                                "border-radius: 10px;"  // Adjust the radius value to control how round the corners are
                                "color: goldenrod;"  // Optional: sets the text color
                                "padding: 5px 10px;"  // Optional: sets padding to make the button size more appropriate
                                "}");
    topSellings = new QPushButton();
    topSellings->setMinimumHeight(200);
    topSellings->setMinimumWidth(200);
    topSellings->setIcon(QIcon(":/growth.ico"));
    topSellings->setIconSize(QSize(70, 70));
    topSellings->setFont(QFont("Times New Roman", 18));
    topSellings->setStyleSheet("QPushButton {"
                                "border-radius: 10px;"  // Adjust the radius value to control how round the corners are
                                "color: green;"  // Optional: sets the text color
                                "padding: 5px 10px;"  // Optional: sets padding to make the button size more appropriate
                                "}");
    topSellings->setText(getTopSellingMedicines(nOfTopSellings));
    // Layouts
    mainLayout = new QVBoxLayout(this);
    buttonLayout = new QVBoxLayout();
    boardLayout = new QHBoxLayout();

    // Add widgets to layouts
    buttonLayout->addWidget(totalRevenue);
    buttonLayout->addWidget(topSellings);
    boardLayout->addWidget(salesTable);
    boardLayout->addLayout(buttonLayout);
    mainLayout->addLayout(boardLayout);

    // Set the layout for the main widget
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


    QJsonObject customerJson;
    customerJson["Name"] = customerName;
    customerJson["PhoneNumber"] = phoneNumber;
    customerJson["Total"] = total;
    customerJson["Address"] = address;
    customerJson["Order"] = order;
    customerJson["OrderID"] = orderID;
    customerJson["PaymentType"] = physical ? "Physical" : "Delivery";


    QTime currentTime = QTime::currentTime();
    QDate currentDate = QDate::currentDate();
    QString date = currentDate.toString("dd/MMM/yyyy");
    QString time = currentTime.toString("hh:mm");
    salesTable->setRowCount(salesTable->rowCount() + 1);

    // Date & Time
    QTableWidgetItem *tableItem = new QTableWidgetItem(QIcon(":/calender.ico"), time + "\n" + date);
    tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
    salesTable->setItem(salesTable->rowCount() - 1, 0, tableItem);


    if (physical) {
        tableItem = new QTableWidgetItem(QIcon(":/user.ico"), "Physical");
        tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
        salesTable->setItem(salesTable->rowCount() - 1, 2, tableItem);
        customer = new CustomPushButton(QIcon(":/customer.ico"), customerName,order,true);
        salesTable->setCellWidget(salesTable->rowCount() - 1, 1, customer);
        tableItem = new QTableWidgetItem(QIcon(":/done.ico"), "Paid");
        tableItem->setForeground(QColor(Qt::green));
        tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
        salesTable->setItem(salesTable->rowCount() - 1, 3, tableItem);
    } else {
        tableItem = new QTableWidgetItem(QIcon(":/delivery-bike.ico"), "Delivery");
        tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
        salesTable->setItem(salesTable->rowCount() - 1, 2, tableItem);
        customer = new CustomPushButton(QIcon(":/customer.ico"), customerName,order,false);
        salesTable->setCellWidget(salesTable->rowCount() - 1, 1, customer);
        tableItem = new QTableWidgetItem(QIcon(":/unpaid.ico"), "UnPaid");
        tableItem->setForeground(QColor(Qt::red));
        tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
        salesTable->setItem(salesTable->rowCount() - 1, 3, tableItem);
    }

    tableItem = new QTableWidgetItem(QIcon(":/growth.ico"), QString::number(total));
    tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
    salesTable->setItem(salesTable->rowCount() - 1, 4, tableItem);

    customersArray.append(customerJson);

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
    ////////////////Writing To Sales.json Also
    writeToJson();
    totalRevenue->setText("Total Revenue : "+QString::number(getTotalDuePayment()+getTotalPaidPayment())+"PKR"+"\n-----------------------\n"+"Paid = "
                          +QString::number(getNumberOfPaidTransactions())+"\nPaid Amount = "
                          +QString::number(getTotalPaidPayment())+"\n-----------------------\n"+"Unpaid = "
                          +QString::number(getNumberOfUnPaidTransactions())+"\nUnPaid Amount = "+QString::number(getTotalDuePayment()));
    topSellings->setText(getTopSellingMedicines(nOfTopSellings));
}

void SalesAndReports::addSalesRowFromJSon(double total, bool physical, QString customerName, QString order, QString dateAndTime, QString paymentStatus)
{
    salesTable->setRowCount(salesTable->rowCount() + 1);

    // Date & Time
    QTableWidgetItem *tableItem = new QTableWidgetItem(QIcon(":/calender.ico"),dateAndTime);
    tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
    salesTable->setItem(salesTable->rowCount() - 1, 0, tableItem);


    if (physical) {
        tableItem = new QTableWidgetItem(QIcon(":/user.ico"), "Physical");
        tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
        salesTable->setItem(salesTable->rowCount() - 1, 2, tableItem);
        customer = new CustomPushButton(QIcon(":/customer.ico"), customerName,order,true);
        salesTable->setCellWidget(salesTable->rowCount() - 1, 1, customer);

    } else {
        tableItem = new QTableWidgetItem(QIcon(":/delivery-bike.ico"), "Delivery");
        tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
        salesTable->setItem(salesTable->rowCount() - 1, 2, tableItem);
        customer = new CustomPushButton(QIcon(":/customer.ico"), customerName,order,false);
        salesTable->setCellWidget(salesTable->rowCount() - 1, 1, customer);
    }
    if(paymentStatus=="Paid"){
        tableItem = new QTableWidgetItem(QIcon(":/done.ico"), "Paid");
        tableItem->setForeground(QColor(Qt::green));
        tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
        salesTable->setItem(salesTable->rowCount() - 1, 3, tableItem);
    }else {
        tableItem = new QTableWidgetItem(QIcon(":/unpaid.ico"), "UnPaid");
        tableItem->setForeground(QColor(Qt::red));
        tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
        salesTable->setItem(salesTable->rowCount() - 1, 3, tableItem);
    }

    tableItem = new QTableWidgetItem(QIcon(":/growth.ico"), QString::number(total));
    tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
    salesTable->setItem(salesTable->rowCount() - 1, 4, tableItem);
    for (int i = 0; i < salesTable->rowCount(); ++i) {
        salesTable->setRowHeight(i,60);
    }
    totalRevenue->setText("Total Revenue : "+QString::number(getTotalDuePayment()+getTotalPaidPayment())+"PKR"+"\n-----------------------\n"+"Paid = "
                          +QString::number(getNumberOfPaidTransactions())+"\nPaid Amount = "
                          +QString::number(getTotalPaidPayment())+"\n-----------------------\n"+"Unpaid = "
                          +QString::number(getNumberOfUnPaidTransactions())+"\nUnPaid Amount = "+QString::number(getTotalDuePayment()));
    topSellings->setText(getTopSellingMedicines(nOfTopSellings));

}


void SalesAndReports::removeRow(int row)
{
    salesTable->removeRow(row);
}

void SalesAndReports::setDeliveryStatus(QString customerName, QString customerOrder)
{
    for (int rows = 0; rows < salesTable->rowCount(); ++rows) {
        CustomPushButton *button = qobject_cast<CustomPushButton*>(salesTable->cellWidget(rows, 1));
        if (button && button->text() == customerName&&button->correspondingOrder==customerOrder) {
            QTableWidgetItem *tableItem = new QTableWidgetItem(QIcon(":/done.ico"), "Paid");
            tableItem->setForeground(QColor(Qt::green));
            tableItem->setFlags(tableItem->flags() & ~Qt::ItemIsEditable);
            salesTable->setItem(rows, 3, tableItem);
        }
    }
    totalRevenue->setText("Total Revenue : "+QString::number(getTotalDuePayment()+getTotalPaidPayment())+"PKR"+"\n-----------------------\n"+"Paid = "
                          +QString::number(getNumberOfPaidTransactions())+"\nPaid Amount = "
                          +QString::number(getTotalPaidPayment())+"\n-----------------------\n"+"Unpaid = "
                          +QString::number(getNumberOfUnPaidTransactions())+"\nUnPaid Amount = "+QString::number(getTotalDuePayment()));
    topSellings->setText(getTopSellingMedicines(nOfTopSellings));
    writeToJson();
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


QMultiMap<int, QString> SalesAndReports::getMedicineSales()
{
    QMultiMap<int,QString> bestSellings;
    QDate date =QDate::currentDate();
    QString currentDate =date.toString("dd/MMM/yyyy");
    QJsonObject jsonObj;
    QFile file("Sales.json");
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray jsonData = file.readAll();
        file.close();

        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "Parse error: " << parseError.errorString();
        }

        if (jsonDoc.isObject()) {
            jsonObj = jsonDoc.object();
        } else {
            qDebug() << "JSON is not an object.";
        }
    } else {
        qDebug() << "Unable to open file.";
    }

    if (jsonObj.contains(currentDate) && jsonObj[currentDate].isArray()) {
        QJsonArray dateArray = jsonObj[currentDate].toArray();
        for (int rows = 0; rows < medicinesTable->rowCount(); ++rows) {
            QString medicineName = medicinesTable->item(rows, 0)->text();
            int numberOfSales = 0;
            for (const QJsonValue &value : dateArray) {
                QJsonObject tableRow = value.toObject();
                QJsonObject button = tableRow["Button"].toObject();
                QString order = button["Order"].toString();
                if (order.contains(medicineName, Qt::CaseInsensitive)) {
                    ++numberOfSales;
                }
            }
            bestSellings.insert(numberOfSales, medicineName);
        }
    } else {
        qDebug() << "No data for the current date or invalid structure.";
    }
    return bestSellings;
}

QString SalesAndReports::getTopSellingMedicines(int topN)
{
    QMultiMap<int, QString> bestSellings = getMedicineSales();
    QStringList topMedicines;
    QMultiMap<int, QString>::const_iterator it = bestSellings.constEnd();
    int count = 0;

    while (it != bestSellings.constBegin() && count < topN) {
        --it;
        topMedicines.append(it.value());
        ++count;
    }
    QString topSellingsText ="Top Sellings :";
    for (int i = 0; i < topMedicines.count(); ++i) {
        topSellingsText.append("\n"+QString::number(i+1)+". "+topMedicines.at(i));
    }
    return topSellingsText;
}

void SalesAndReports::readFromJson()
{
    QDate date =QDate::currentDate();
    QJsonObject jsonObj;
    QFile file("Sales.json");
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray jsonData = file.readAll();
        file.close();

        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "Parse error: " << parseError.errorString();
            return;
        }

        if (jsonDoc.isObject()) {
            jsonObj = jsonDoc.object();
        } else {
            qDebug() << "JSON is not an object.";
        }
    } else {
        qDebug() << "Unable to open file.";
        return;
    }

    for (const QString &key : jsonObj.keys()) {
        if(date.toString("dd/MMM/yyyy")==key){
            QJsonArray date=jsonObj[key].toArray();
            for (int i = 0; i < date.count(); ++i) {
                QJsonObject tableRow= date.at(i).toObject();
                QString dateandTime=tableRow["Date&Time"].toString();
                QString paymentStatus=tableRow["Payment Status"].toString();
                double total=tableRow["Total"].toString().toDouble();
                QJsonObject button=tableRow["Button"].toObject();
                QString nameOrLabel =button["Label"].toString();
                QString order =button["Order"].toString();
                bool physical =button["Physical"].toBool();
                addSalesRowFromJSon(total,physical,nameOrLabel,order,dateandTime,paymentStatus);
            }
        }
    }

}

void SalesAndReports::writeToJson() {
    QFile fIn("Sales.json");
    QJsonObject rootObj;
    QJsonArray saleJsonTable;
    QDate date = QDate::currentDate();
    QString currentDate = date.toString("dd/MMM/yyyy");

/////////////// Reading the existing JSON file
    if (fIn.open(QIODevice::ReadOnly)) {
        QByteArray jsonData = fIn.readAll();
        fIn.close();

        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "Parse error: " << parseError.errorString() << " In SalesAndReports::writeToJson()";
        }

        if (jsonDoc.isObject()) {
            rootObj = jsonDoc.object();
        } else {
            qDebug() << "JSON is not an object. SalesAndReports::writeToJson()";
        }
    } else {
        qDebug() << "Unable to open file. SalesAndReports::writeToJson()";
    }
    if (rootObj.contains(currentDate) && rootObj[currentDate].isArray()) {
        saleJsonTable = rootObj[currentDate].toArray();
    }
    for (int row = saleJsonTable.count(); row < salesTable->rowCount(); ++row) {
        QJsonObject jsonObj;
        auto dateTimeItem = salesTable->item(row, 0);
        if (dateTimeItem) {
            jsonObj["Date&Time"] = dateTimeItem->text();
        }
        CustomPushButton *button = dynamic_cast<CustomPushButton *>(salesTable->cellWidget(row, 1));
        if (button) {
            QJsonObject buttonObj;
            buttonObj["Order"] = button->correspondingOrder;
            buttonObj["Label"] = button->buttonLabel;
            buttonObj["Physical"] = button->physical;
            jsonObj["Button"] = buttonObj;
        }
        auto salesTypeItem = salesTable->item(row, 2);
        auto paymentStatusItem = salesTable->item(row, 3);
        auto totalItem = salesTable->item(row, 4);
        if (salesTypeItem) {
            jsonObj["SalesType"] = salesTypeItem->text();
        }
        if (paymentStatusItem) {
            jsonObj["Payment Status"] = paymentStatusItem->text();
        }
        if (totalItem) {
            jsonObj["Total"] = totalItem->text();
        }
        saleJsonTable.append(jsonObj);
    }

    rootObj[currentDate] = saleJsonTable;

    QJsonDocument saveDoc(rootObj);
    QFile fOut("Sales.json");
    if (fOut.open(QIODevice::WriteOnly)) {
        fOut.write(saveDoc.toJson(QJsonDocument::Indented));
        fOut.close();
    } else {
        qDebug() << "Unable to open file for writing. SalesAndReports::writeToJson()";
    }
}




