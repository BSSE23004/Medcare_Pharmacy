#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    medicineTableGeometry=0;
    total=0;
    checkTimer =new QTimer(this);
    medicinesTable=nullptr;
    makeListMenu();
    hideButton =new QPushButton("Hide Panel",this);
    hideButton->setIcon(QIcon(":/blind.ico"));
    hideButton->setGeometry(-2,670,182,30);
    hbox=new QHBoxLayout();
    hbox->addWidget(listMenu);
    hbox->addWidget(hideButton);
    //Connections
    connect(hideButton,SIGNAL(clicked(bool)),this,SLOT(handleHideButton()));
    connect(listMenu,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(currentMenu()));
    //building menus
    billMenu();
    medicinesMenu();
    salesAndReportsMenu();
    ordersAndDeliveryMenu();
    readMedicineTableFromJson();
    kanbanBoard->readFromJson();
    salesMenu->readFromJson();
    connect(kanbanBoard->deliveryInput->orderButton,SIGNAL(clicked(bool)),this,SLOT(handleOrderButton()));
    connect(kanbanBoard->doneList,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(handleDoneList()));
    connect(searchBar, &QLineEdit::textChanged, this, &MainWindow::handleSearchBarAndButton);
    connect(searchButton,SIGNAL(clicked(bool)), this,SLOT(handleSearchBarAndButton()));
}

MainWindow::~MainWindow() {
    writeMedicinesTableToJson();
    kanbanBoard->writeToJson();
    salesMenu->writeToJson();
    delete hbox;
    delete listMenu;
    delete hideButton;
    delete profile;
    delete medicines;
    delete ordersAndDelivery;
    delete staff;
    delete salesAndReports;
    delete bills;
    delete customers;
    delete item;
    delete medicinesTable;
    delete searchButton;
    delete searchBar;
    delete itemTable;
    delete addButton;
    delete name;
    delete company;
    delete mg;
    delete price;
    delete quantity;
    delete inputMedicine;
    delete removeButton;
    delete billInput;
    delete generateReceiptButton;
    delete generateBillButton;
    delete kanbanBoard;
    delete salesMenu;
}

void MainWindow::makeListMenu()
{
    listMenu =new QListWidget(this);
    profile =new QListWidgetItem(QIcon(":/user.ico"),"Profile");
    medicines=new QListWidgetItem(QIcon(":/Medicine.ico"),"Medicines");
    ordersAndDelivery =new QListWidgetItem(QIcon(":/delivery-bike.ico"),"Orders&Delivery");
    staff =new QListWidgetItem(QIcon(":/medical-team.ico"),"Staff");
    salesAndReports =new QListWidgetItem(QIcon(":/business-report.ico"),"Sales And Reports");
    bills =new QListWidgetItem(QIcon(":/bill.ico"),"Generate Bill");
    customers =new QListWidgetItem(QIcon(":/customer.ico"),"Customer Care");
    listMenu->insertItem(0,profile);
    listMenu->insertItem(1,medicines);
    listMenu->insertItem(2,ordersAndDelivery);
    listMenu->insertItem(3,staff);
    listMenu->insertItem(4,salesAndReports);
    listMenu->insertItem(5,bills);
    listMenu->insertItem(6,customers);
    listMenu->setFont(QFont("Times New Roman",14));
    setListWidgetSize(listMenu);
}

void MainWindow::setListWidgetSize(QListWidget *listWidget)
{
    int totalHeight = 0;
    for (int i = 0; i < listWidget->count(); ++i) {
        item = listWidget->item(i);
        totalHeight += listWidget->visualItemRect(item).height();
        item->setSizeHint(QSize(30,listWidget->visualItemRect(item).height()+40));
    }
    totalHeight += 2 * listWidget->frameWidth();
    listWidget->setMinimumSize(180,totalHeight+700);
    listWidget->setMaximumSize(300,totalHeight+800);
    listWidget->setIconSize(QSize(30,(totalHeight/listWidget->count())+10));
}

void MainWindow::medicinesMenu()
{
    ////////////////////////////////////////Medicines Table
    int totalWidth=0;
    // if(medicinesTable!=nullptr){
    //     hbox->removeWidget(medicinesTable);
    //     delete medicinesTable;
    //     delete searchButton;
    // }
    medicinesTable =new QTableWidget(0,5,this);
    QStringList headers = { "Name","Price", "Quantity", "MG", "Company" };
    medicinesTable->setHorizontalHeaderLabels(headers);
    medicinesTable->setFont(QFont("Times New Roman",14,13));
    for (int row = 0; row < medicinesTable->rowCount(); ++row) {
        for (int col = 0; col < medicinesTable->columnCount(); ++col) {
            itemTable = new QTableWidgetItem();
            itemTable->setFlags(itemTable->flags() & ~Qt::ItemIsEditable);
            medicinesTable->setItem(row, col, itemTable);
        }
    }
    for (int col = 0; col < medicinesTable->columnCount(); ++col) {
        totalWidth+=medicinesTable->columnWidth(col);
    }
    medicineTableGeometry=totalWidth+50;
    medicinesTable->setGeometry(200,0,medicineTableGeometry,700);
    settingColumnsWidth();
    hbox->addWidget(medicinesTable);
    ////////////////////////////////////////Medicines Table
    searchBar =new QLineEdit(this);
    searchButton =new QPushButton(this);
    searchButton->setIcon(QIcon(":/search.ico"));
    addButton =new QPushButton(QIcon(":/add.ico"),"Add Row",this);
    removeButton =new QPushButton(QIcon(":/removeButton.ico"),"Delete Row",this);
    removeButton->hide();
    addButton->hide();
    searchButton->hide();
    searchBar->hide();
    searchButton->setGeometry(913,1,40,25);
    searchBar->setGeometry(751,1,200,25);
    addButton->setGeometry(750,50,205,60);
    removeButton->setGeometry(750,130,205,60);
    addButton->setIconSize(QSize(55,55));
    removeButton->setIconSize(QSize(40,40));
    addButton->setFont(QFont("Times New Roman",14));
    removeButton->setFont(QFont("Times New Roman",14));
    connect(addButton,SIGNAL(clicked(bool)),this,SLOT(handleAddRowButton()));
    connect(removeButton,SIGNAL(clicked(bool)),this,SLOT(handleRemoveRowButton()));

}

void MainWindow::filterTable(const QString &text)
{
    for (int row = 0; row < medicinesTable->rowCount(); ++row) {
        bool match = false;
        for (int column = 0; column < medicinesTable->columnCount(); ++column) {
            itemTable = medicinesTable->item(row, column);
            if (itemTable && itemTable->text().contains(text, Qt::CaseInsensitive)) {
                match = true;
                break;
            }
        }
        medicinesTable->setRowHidden(row, !match);
    }
}

void MainWindow::writeMedicinesTableToJson()
{
    QJsonObject medicinesFile;

    // Create a QJsonArray to hold the rows of the table
    QJsonArray medicinesArray;

    // Iterate through each row in the medicinesTable
    for (int row = 0; row < medicinesTable->rowCount(); ++row) {
        QJsonObject jsonRow;

        // Populate jsonRow with data from each cell in the row
        jsonRow["Name"] = medicinesTable->item(row, 0) ? medicinesTable->item(row, 0)->text() : "";
        jsonRow["Price"] = medicinesTable->item(row, 1) ? medicinesTable->item(row, 1)->text() : "";
        jsonRow["Quantity"] = medicinesTable->item(row, 2) ? medicinesTable->item(row, 2)->text() : "";
        jsonRow["Mg"] = medicinesTable->item(row, 3) ? medicinesTable->item(row, 3)->text() : "";
        jsonRow["Company"] = medicinesTable->item(row, 4) ? medicinesTable->item(row, 4)->text() : "";

        // Append the jsonRow to the QJsonArray
        medicinesArray.append(jsonRow);
    }

    // Add the array to the root object
    medicinesFile["MedicinesTable"] = medicinesArray;

    // Create a QJsonDocument from the QJsonObject
    QJsonDocument jsonDoc(medicinesFile);

    // Write the JSON data to the file
    QFile fOut("Medicines.json");
    if (fOut.open(QIODevice::WriteOnly)) {
        fOut.write(jsonDoc.toJson(QJsonDocument::Indented));
        fOut.close();
    } else {
        qDebug() << "Unable to open file for writing.";
    }
}

void MainWindow::readMedicineTableFromJson()
{
    // Load the JSON file
    QFile file("Medicines.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to open file.";
        return;
    }

    // Parse the JSON data
    QByteArray jsonData = file.readAll();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData));
    file.close();

    if (!jsonDoc.isObject()) {
        qDebug() << "JSON document is not an object.";
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();

    // Check if the JSON object contains the necessary key
    if (!jsonObj.contains("MedicinesTable") || !jsonObj["MedicinesTable"].isArray()) {
        qDebug() << "JSON object is missing 'MedicinesTable' or it is not an array.";
        return;
    }

    QJsonArray medicineTableFromJson = jsonObj["MedicinesTable"].toArray();
    medicinesTable->setRowCount(medicineTableFromJson.size());

    int row = 0;
    for (const QJsonValue &value : medicineTableFromJson) {
        if (value.isObject()) {
            QJsonObject obj = value.toObject();

            QString data0 = obj["Name"].toString();
            QString data1 = obj["Price"].toString();
            QString data2 = obj["Quantity"].toString();
            QString data3 = obj["Mg"].toString();
            QString data4 = obj["Company"].toString();

            QTableWidgetItem *itemTable = new QTableWidgetItem(data0);
            itemTable->setFlags(itemTable->flags() & ~Qt::ItemIsEditable);
            medicinesTable->setItem(row, 0, itemTable);

            itemTable = new QTableWidgetItem(data1);
            itemTable->setFlags(itemTable->flags() & ~Qt::ItemIsEditable);
            medicinesTable->setItem(row, 1, itemTable);

            itemTable = new QTableWidgetItem(data2);
            itemTable->setFlags(itemTable->flags() & ~Qt::ItemIsEditable);
            medicinesTable->setItem(row, 2, itemTable);

            itemTable = new QTableWidgetItem(data3);
            itemTable->setFlags(itemTable->flags() & ~Qt::ItemIsEditable);
            medicinesTable->setItem(row, 3, itemTable);

            itemTable = new QTableWidgetItem(data4);
            itemTable->setFlags(itemTable->flags() & ~Qt::ItemIsEditable);
            medicinesTable->setItem(row, 4, itemTable);
            ++row;
        } else {
            qDebug() << "Invalid JSON object in array.";
        }
    }

}

void MainWindow::settingColumnsWidth()
{
    int numericColumnsWidth=70;
    medicinesTable->setColumnWidth(0,150);
    medicinesTable->setColumnWidth(4,150);
    medicinesTable->setColumnWidth(1,numericColumnsWidth);
    medicinesTable->setColumnWidth(2,numericColumnsWidth);
    medicinesTable->setColumnWidth(3,numericColumnsWidth);
}

void MainWindow::billMenu()
{
    receiptText="";
    receiptText.append("Receipt\n");
    receiptText.append("===============================================================\n");
    receiptText.append("Name             Quantity         Price            Mg         TotalPrice/item\n");
    generateBillButton =new QPushButton(QIcon(":/add.ico"),"Generate Bill",this);
    generateBillButton->setGeometry(750,0,205,60);
    generateBillButton->setIconSize(QSize(55,55));
    generateBillButton->setFont(QFont("Times New Roman",14));
    generateBillButton->hide();
    generateReceiptButton =new QPushButton(QIcon(":/receipt.ico"),"Generate Receipt",this);
    generateReceiptButton->setGeometry(750,70,205,60);
    generateReceiptButton->setIconSize(QSize(50,50));
    generateReceiptButton->setFont(QFont("Times New Roman",14));
    generateReceiptButton->hide();
    connect(generateBillButton,SIGNAL(clicked(bool)),this,SLOT(handleBillButton()));
    connect(generateReceiptButton,SIGNAL(clicked(bool)),this,SLOT(handleReceiptButton()));
}

static int it=0;
static int widthForString =20;
void MainWindow::padRight(QString &text)
{

    for (int i = text.size(); i < widthForString; ++i) {
        text.append(" ");
    }
    ++it;
    if(it%5==0){
        widthForString=20;
        return;
    }
    widthForString+=12;
}

void MainWindow::ordersAndDeliveryMenu()
{
    kanbanBoard =new KanbanBoard(this);
    kanbanBoard->setGeometry(175,0,650,700);
    kanbanBoard->hide();

}

void MainWindow::salesAndReportsMenu()
{
    salesMenu =new SalesAndReports(this);
    salesMenu->setGeometry(175,0,1100,700);
    salesMenu->hide();
}


void MainWindow::handleSearchBarAndButton()
{
    filterTable(searchBar->text());
}

void MainWindow::handleRemoveRowButton()
{
    int rowNumber = QInputDialog ::getInt(this,"Delete Row","Enter Row number to delete");
    if(rowNumber>0&&rowNumber<=medicinesTable->rowCount()){
        medicinesTable->removeRow(rowNumber-1);
    }else{
        QMessageBox::warning(this,"Invalid Input","Enter a Number from the Table!!!");
    }
}

void MainWindow::handleAddRowButton()
{
    inputMedicine =new InputDialog(this);
    if (inputMedicine->exec() == QDialog::Accepted) {
        if(inputMedicine->getName().isEmpty()||inputMedicine->getQuantity().isEmpty()||inputMedicine->getCompany().isEmpty()||inputMedicine->getPrice().isEmpty()||inputMedicine->getmg().isEmpty()){
            QMessageBox::warning(this,"Invalid Input","Enter complete data!!!");
            return;
        }
        medicinesTable->setRowCount(medicinesTable->rowCount()+1);

        name=new QTableWidgetItem(inputMedicine->getName());
        company =new QTableWidgetItem(inputMedicine->getCompany());
        price =new QTableWidgetItem(inputMedicine->getPrice());
        mg =new QTableWidgetItem(inputMedicine->getmg());
        quantity =new QTableWidgetItem(inputMedicine->getQuantity());
        name->setFlags(name->flags()& ~Qt::ItemIsEditable);
        company->setFlags(company->flags()& ~Qt::ItemIsEditable);
        price->setFlags(price->flags()& ~Qt::ItemIsEditable);
        mg->setFlags(mg->flags()& ~Qt::ItemIsEditable);
        quantity->setFlags(quantity->flags()& ~Qt::ItemIsEditable);
        medicinesTable->setItem(medicinesTable->rowCount()-1,0,name);
        medicinesTable->setItem(medicinesTable->rowCount()-1,1,price);
        medicinesTable->setItem(medicinesTable->rowCount()-1,2,quantity);
        medicinesTable->setItem(medicinesTable->rowCount()-1,3,mg);
        medicinesTable->setItem(medicinesTable->rowCount()-1,4,company);

    }

}



void MainWindow::handleHideButton()
{
    static bool isHidden = false;

    if (!isHidden) {
        hideButton->setText("Unhide Panel");
        hideButton->setIcon(QIcon(":/unhide.ico"));
        listMenu->hide();
    } else {
        hideButton->setText("Hide Panel");
        hideButton->setIcon(QIcon(":/blind.ico"));
        listMenu->show();
    }

    isHidden = !isHidden;
}

void MainWindow::currentMenu()
{
    /////////Medicine Menu
    removeButton->hide();
    addButton->hide();
    searchBar->hide();
    searchButton->hide();
    medicinesTable->hide();
    medicinesTable->setGeometry(200,0,medicineTableGeometry,700);
    settingColumnsWidth();
    /////////Medicine Menu
    /////////Bill Menu
    generateBillButton->hide();
    generateReceiptButton->hide();
    /////////Bill Menu
    /////////Orders&Delivery Menu
    kanbanBoard->hide();
    /////////Orders&Delivery Menu
    /////////Sales&Reports Menu
    salesMenu->hide();
    /////////Sales&Reports Menu
    if(listMenu->currentItem()->text()=="Medicines"){
        medicinesTable->show();
        searchButton->show();
        searchBar->show();
        addButton->show();
        removeButton->show();
    }
    if(listMenu->currentItem()->text()=="Generate Bill"){
        medicinesTable->show();
        generateBillButton->show();
        generateReceiptButton->show();
    }
    if(listMenu->currentItem()->text()=="Orders&Delivery"){
        kanbanBoard->show();
        medicinesTable->setGeometry(820,0,470,700);
        medicinesTable->show();
    }
    if(listMenu->currentItem()->text()=="Sales And Reports"){
        salesMenu->show();
    }

}


int billInputHeight =100;
int billInputWidth =400;
void MainWindow::handleBillButton()
{
    static QString order;
    static double totalForSalesAndReports=0.0;
    billInput =new BillInputDialog (this);
    billInput->setMinimumHeight(billInputHeight);
    billInput->setMinimumWidth(billInputWidth);
    int rowNumber=-1;
    connect(checkTimer,SIGNAL(timeout()),this,SLOT(handleLineEdits()));
    checkTimer->start(1000);
    if (billInput->exec() == QDialog::Accepted) {
        if(billInput->getName().isEmpty()||billInput->getQuantity().isEmpty()||billInput->getCompany().isEmpty()||billInput->getmg().isEmpty()){
            QMessageBox::warning(this,"Invalid Input","Enter complete data!!!");
            order="";
            totalForSalesAndReports=0.0;
            return;
        }
        for (int row = 0; row < medicinesTable->rowCount(); ++row) {
            itemTable =medicinesTable->item(row,0);
            if(itemTable && itemTable->text().contains(billInput->getName(), Qt::CaseInsensitive)){
                rowNumber=row;
                if(billInput->getmg()!=medicinesTable->item(row,3)->text()||billInput->getQuantity().toFloat()>medicinesTable->item(row,2)->text().toFloat()) {
                    QMessageBox::warning(this,"Invalid Input","Enter proper data!!!(Maybe Quantity OR Mg You entered is not correct)");
                    order="";
                    totalForSalesAndReports=0.0;
                    return;
                }
            }
        }
        QString newLine="";
        newLine.append(billInput->getName());
        order.append("Medicine : "+billInput->getName()+"\n");
        padRight(newLine);
        newLine.append(billInput->getQuantity());
        order.append("Quantity : "+billInput->getQuantity()+"\n");
        padRight(newLine);
        newLine.append(medicinesTable->item(rowNumber,1)->text());
        order.append("Price : "+medicinesTable->item(rowNumber,1)->text()+"\n");
        padRight(newLine);
        newLine.append(billInput->getmg());
        order.append("MG : "+billInput->getmg()+"\n");
        padRight(newLine);
        newLine.append(QString::number(billInput->getQuantity().toFloat()*medicinesTable->item(rowNumber,1)->text().toFloat()));
        order.append("$/Quantity : "+QString::number(billInput->getQuantity().toFloat()*medicinesTable->item(rowNumber,1)->text().toFloat())+"\n");
        padRight(newLine);
        newLine.append("\n");
        order.append("\n");
        receiptText.append(newLine);
        if(rowNumber==-1){
            total+=0;
            totalForSalesAndReports+=0;
        }else {
            total+=billInput->getQuantity().toFloat()*medicinesTable->item(rowNumber,1)->text().toFloat();
            totalForSalesAndReports+=billInput->getQuantity().toFloat()*medicinesTable->item(rowNumber,1)->text().toFloat();
        }
        billInput->setName("");
        for (int row = 0; row < medicinesTable->rowCount(); ++row) {
            medicinesTable->showRow(row);
        }
        if(billInput->isOkButtonClicked()){
            order.append("\n\nTotal : "+QString::number(totalForSalesAndReports));
            salesMenu->addSalesRow(totalForSalesAndReports,true,"N/A","N/A","N/A",order);
            order="";
            totalForSalesAndReports=0.0;
            return;
        }
        if(billInput->isAddMoreButtonClicked()){
            handleBillButton();
        }
    }
    billInput->setName("");
    for (int row = 0; row < medicinesTable->rowCount(); ++row) {
        medicinesTable->showRow(row);
    }

}


void MainWindow::handleOrderButton()
{

    static double totalForSalesAndReports=0.0;
    int rowNumber=-1;
    int totalPricePerItem=0;
    billInput =new BillInputDialog (this);
    billInput->setMinimumHeight(billInputHeight);
    billInput->setMinimumWidth(billInputWidth);
    connect(checkTimer,SIGNAL(timeout()),this,SLOT(handleLineEdits()));
    checkTimer->start(1000);
    if (billInput->exec() == QDialog::Accepted) {
        if(billInput->getName().isEmpty()||billInput->getQuantity().isEmpty()||billInput->getCompany().isEmpty()||billInput->getmg().isEmpty()){
            QMessageBox::warning(this,"Invalid Input","Enter complete data!!!");
            totalForSalesAndReports=0.0;
            return;
        }
        for (int row = 0; row < medicinesTable->rowCount(); ++row) {
            itemTable =medicinesTable->item(row,0);
            if(itemTable && itemTable->text().contains(billInput->getName(), Qt::CaseInsensitive)){
                rowNumber=row;
                if(billInput->getmg()!=medicinesTable->item(row,3)->text()||billInput->getQuantity().toFloat()>medicinesTable->item(row,2)->text().toFloat()) {
                    QMessageBox::warning(this,"Invalid Input","Enter proper data!!!(Maybe Quantity OR Mg You entered is not correct)");
                    totalForSalesAndReports=0.0;
                    return;
                }
            }
        }
        if(rowNumber==-1){
            totalPricePerItem+=0;
        }else{
            totalPricePerItem+=billInput->getQuantity().toFloat()*medicinesTable->item(rowNumber,1)->text().toFloat();
        }
        totalForSalesAndReports+=totalPricePerItem;
        kanbanBoard->deliveryInput->setTotal(kanbanBoard->deliveryInput->getTotal()+totalPricePerItem);
        kanbanBoard->deliveryInput->setOrder(kanbanBoard->deliveryInput->getOrder()+"Medicine : "+billInput->getName()
                                             +"\nQuantity : "+billInput->getQuantity()+
                                             "\nPrice : "+medicinesTable->item(rowNumber,1)->text()+
                                             "\nPrice/Quantity : "+QString::number(totalPricePerItem)+"\n\n");
        billInput->setName("");
        for (int row = 0; row < medicinesTable->rowCount(); ++row) {
            medicinesTable->showRow(row);
        }
        if(billInput->isOkButtonClicked()){
            salesMenu->addSalesRow(totalForSalesAndReports,false,kanbanBoard->deliveryInput->getName(),
                                   kanbanBoard->deliveryInput->getPhoneNumber(),
                                   kanbanBoard->deliveryInput->getAddress(),
                                   kanbanBoard->deliveryInput->getOrder()+"\n\nTotal : "+QString::number(totalForSalesAndReports),
                                   QString::number(kanbanBoard->getOrderID()));
            totalForSalesAndReports=0.0;
            return;
        }
        if(billInput->isAddMoreButtonClicked()){
            handleOrderButton();
        }
    }
    billInput->setName("");
    for (int row = 0; row < medicinesTable->rowCount(); ++row) {
        medicinesTable->showRow(row);
    }
}


void MainWindow::handleLineEdits()
{
    for (int row = 0; row < medicinesTable->rowCount(); ++row) {
        itemTable =medicinesTable->item(row,0);
        if(itemTable && itemTable->text().contains(billInput->getName(), Qt::CaseInsensitive)){
            billInput->setIntValidatorRange(0,medicinesTable->item(row,3)->text().toInt());
            billInput->setDoubleValidatorRange(0.0,medicinesTable->item(row,2)->text().toFloat());
            billInput->setCompanyLine(medicinesTable->item(row,4)->text());
        }
    }
    filterTable(billInput->getName());
}

void MainWindow::printReceipt(QString &text)
{
    text.append("\nTotal : "+QString::number(total)+"\n");
    text.append("===============================================================\n");
    text.append("Thank you for your purchase!\n");
    total=0;
    // Create a printer object
    QPrinter printer;
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageOrientation(QPageLayout::Portrait);

    // Create a print dialog
    QPrintDialog printDialog(&printer);
    if (printDialog.exec() != QDialog::Accepted) {
        return; // User cancelled the print dialog
    }

    // Create a painter to draw on the printer
    QPainter painter(&printer);

    // Set font and other properties
    QFont font = painter.font();
    font.setPointSize(12);
    painter.setFont(font);

    // Calculate the area to print
    QRect rect = painter.viewport();
    int margin = 50;
    rect.adjust(margin, margin, -margin, -margin);

    // Draw the text
    painter.drawText(rect, Qt::AlignLeft | Qt::TextWordWrap, receiptText);

    painter.end(); // End the painting
    receiptText="";
}

void MainWindow::handleReceiptButton()
{
    printReceipt(receiptText);
}

void MainWindow::handleDoneList()
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
    for (int i = 0; i < customersJSONArray.size(); ++i) {
        QJsonObject customer = customersJSONArray[i].toObject();
        for (int j = 0; j < kanbanBoard->doneList->count(); ++j) {
            QListWidgetItem *item = kanbanBoard->doneList->item(j);
            qDebug()<<"Searching for name to setdeliveryStatus";
            if(item && item->text().contains("Name : "+customer["Name"].toString()+"\nID : "+customer["OrderID"].toString()+"\nAddress : "+customer["Address"].toString()+"\nPhone : "+customer["PhoneNumber"].toString(), Qt::CaseInsensitive)){
                salesMenu->setDeliveryStatus(customer["Name"].toString(),customer["Order"].toString());
            }
        }
    }

    // for (int i = 0; i < kanbanBoard->customersName.count(); ++i) {
    //     for (int j = 0; j < kanbanBoard->doneList->count(); ++j) {
    //         QListWidgetItem *item = kanbanBoard->doneList->item(j);
    //         if(item && item->text().contains(kanbanBoard->customersName.at(i), Qt::CaseInsensitive)&& item->text().contains(kanbanBoard->customersPhoneNumbers.at(i), Qt::CaseInsensitive)&& item->text().contains(kanbanBoard->customersAddresses.at(i), Qt::CaseInsensitive)){
    //             salesMenu->setDeliveryStatus(kanbanBoard->customersName.at(i),kanbanBoard->customersAddresses.at(i),kanbanBoard->customersPhoneNumbers.at(i));
    //         }
    //     }
    // }
}




