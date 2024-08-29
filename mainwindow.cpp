#include "mainwindow.h"

double MainWindow::totalForSalesAndReports=0.0;
QString MainWindow::order="";
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //////////////1st Window
    loginPage = new SignUpPage("Login",this);
    loginPage->resize(400, 300);
    loginPage->setStyleSheet(
        "QWidget {"
        "background-color: transparent;"  // Correct the spelling: "background-color"
        "border-radius: 10px;"
        "}");
    loginPage->setGeometry(400,200,500,300);
    ////// others
    total=0;
    checkTimer =new QTimer(this);
    makeListMenu();
    hideButton =new QPushButton("Hide Panel",this);
    hideButton->setIcon(QIcon(":/blind.ico"));
    hideButton->setIconSize(QSize(30,30));
    hideButton->setGeometry(-2,650,182,50);
    hideButton->setFont(QFont("Times New Roman",14 ));
    hideButton->setStyleSheet("QPushButton {"
                              "border-radius: 10px;"
                              "padding: 5px 10px;"
                              "}");
    hideButton->hide();
    //Connections
    connect(loginPage->signUpButton, &QPushButton::clicked, this, &MainWindow::onSignUpButtonClicked);
    connect(loginPage->signUp, &ClickableLabel::clicked, this, &MainWindow::onSignUpLabelClicked);
    connect(hideButton,SIGNAL(clicked(bool)),this,SLOT(handleHideButton()));
    connect(listMenu,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(currentMenu()));
    //building menus

    staffMenu();
    customerCareMenu();
    billMenu();
    makeMedicinesMenu();
    salesAndReportsMenu();
    ordersAndDeliveryMenu();
    kanbanBoard->readFromJson();
    salesMenu->readFromJson();
    connect(kanbanBoard->deliveryInput->orderButton,SIGNAL(clicked(bool)),this,SLOT(handleOrderButton()));
    connect(kanbanBoard->doneList,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(handleDoneList()));
}

MainWindow::~MainWindow() {
    qDebug()<<"Exiting Program....";
}

void MainWindow::makeListMenu()
{
    listMenu =new QListWidget(this);
    listItems=new QListWidgetItem(QIcon(":/Medicine.ico"),"Medicines");
    listMenu->insertItem(1,listItems);
    listItems =new QListWidgetItem(QIcon(":/delivery-bike.ico"),"Orders&Delivery");
    listMenu->insertItem(2,listItems);
    listItems =new QListWidgetItem(QIcon(":/medical-team.ico"),"Staff");
    listMenu->insertItem(3,listItems);
    listItems =new QListWidgetItem(QIcon(":/business-report.ico"),"Sales And Reports");
    listMenu->insertItem(4,listItems);
    listItems =new QListWidgetItem(QIcon(":/bill.ico"),"Generate Bill");
    listMenu->insertItem(5,listItems);
    listItems =new QListWidgetItem(QIcon(":/customer.ico"),"Customer Care");
    listMenu->insertItem(6,listItems);
    listMenu->setFont(QFont("Times New Roman",14));
    listMenu->hide();
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

void MainWindow::makeProfileMenu()
{
    profileMenu =new ProfileMenu(this,email);
    profileMenu->setGeometry(175,0,1100,700);
    profileMenu->hide();
    connect(profileMenu->setWindowsOpacity,&QPushButton::clicked,this,&MainWindow::handleSetOpacityButton);
    connect(profileMenu->setWindowsFont,&QPushButton::clicked,this,&MainWindow::handleSetFontButton);
}

void MainWindow::makeMedicinesMenu()
{
    medicinesMenu =new MedicinesMenu(this);
    medicinesMenu->setGeometry(600,0,800,700);
    medicinesMenu->hide();
}


void MainWindow::billMenu()
{
    generateBillButton =new QPushButton(QIcon(":/add.ico"),"Generate Bill",this);
    generateBillButton->setGeometry(900,100,205,60);
    generateBillButton->setIconSize(QSize(55,55));
    generateBillButton->setFont(QFont("Times New Roman",14));
    generateBillButton->setStyleSheet("QPushButton {"
                                      "border-radius: 10px;"
                                      "color: green;"
                                      "padding: 5px 10px;"
                                      "}");
    generateBillButton->setCheckable(true);
    generateBillButton->hide();
    generateReceiptButton =new QPushButton(QIcon(":/receipt.ico"),"Generate Receipt",this);
    generateReceiptButton->setGeometry(915,300,205,60);
    generateReceiptButton->setIconSize(QSize(50,50));
    generateReceiptButton->setFont(QFont("Times New Roman",14));
    generateReceiptButton->setStyleSheet("QPushButton {"
                                         "border-radius: 10px;"
                                         "color: green;"
                                         "padding: 5px 10px;"
                                         "}");
    generateReceiptButton->hide();
    connect(generateBillButton,SIGNAL(clicked(bool)),this,SLOT(handleBillButton()));
    connect(generateReceiptButton,SIGNAL(clicked(bool)),this,SLOT(handleReceiptButton()));
}

static int it=0;
static int widthForString =20;
void MainWindow::padRight(QString &text)
{

    for (int i = text.size(); i < widthForString; ++i) {
        text.append("-");
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
    salesMenu =new SalesAndReports(this,medicinesMenu->medicinesTable);
    salesMenu->setGeometry(175,0,1100,700);
    salesMenu->hide();
}

void MainWindow::customerCareMenu()
{
    customerCare =new CustomerCare(this);
    customerCare->setGeometry(175,0,1100,700);
    customerCare->hide();
}

void MainWindow::staffMenu()
{
    staffOption =new StaffMenu(this);
    staffOption->setGeometry(175,0,1100,700);
    staffOption->hide();
}

void MainWindow::onSignUpButtonClicked()
{
    email = loginPage->emailEdit->text();
    QString password = loginPage->passwordEdit->text();

    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all fields.");
        return;
    }

    if (loginPage->page_name == "Login") {
        QJsonObject jsonObj;
        QFile file("Credentials.json");
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
                return;
            }
        } else {
            qDebug() << "Unable to open file.";
            return;
        }

        if (jsonObj["Email"].toString() == email && jsonObj["Password"].toString() == password) {
            QMessageBox::information(this, "Login Successful", "Thank you for logging in!");
            loginPage->hide();
            listItems =new QListWidgetItem(QIcon(":/user.ico"),jsonObj["Name"].toString());
            listMenu->insertItem(0,listItems);
            // getting profile NAme so that I can use it currentMenu() slot
            profileName=jsonObj["Name"].toString();
            setListWidgetSize(listMenu);
            listMenu->show();
            hideButton->show();
        } else {
            QMessageBox::warning(this, "Login Failed", "Invalid email or password.");
        }
    } else if (loginPage->page_name == "Signup") {
        QMessageBox::information(this, "Signup Successful", "Thank you for signing up!");
        QJsonObject credentials;
        credentials["Name"] = loginPage->nameEdit->text();
        credentials["Email"] = email;
        credentials["Password"] = password;
        QJsonDocument jsonDoc(credentials);
        QFile fOut("Credentials.json");
        if (fOut.open(QIODevice::WriteOnly)) {
            fOut.write(jsonDoc.toJson(QJsonDocument::Indented));
            fOut.close();
        } else {
            qDebug() << "Unable to open Credentials.json file for writing.";
        }

        loginPage->hide();
        listItems =new QListWidgetItem(QIcon(":/user.ico"),loginPage->nameEdit->text());
        listMenu->insertItem(0,listItems);
        // getting profile NAme so that I can use it currentMenu() slot
        profileName=loginPage->nameEdit->text();
        setListWidgetSize(listMenu);
        listMenu->show();
        hideButton->show();
    } else {
        qDebug() << "Unknown page name: " << loginPage->page_name;
    }
    makeProfileMenu();

}


void MainWindow::onSignUpLabelClicked()
{
    delete loginPage;
    loginPage =new SignUpPage("Signup",this);
    loginPage->resize(400, 300);
    loginPage->setStyleSheet(
        "QWidget {"
        "background-color: transparent;"
        "border-radius: 10px;"
        "}");
    loginPage->setGeometry(400,200,500,300);
    loginPage->show();
    connect(loginPage->signUpButton, &QPushButton::clicked, this, &MainWindow::onSignUpButtonClicked);
}

void MainWindow::handleSetFontButton()
{
    bool ok;
    QFont font =QFontDialog::getFont(&ok,this);
    this->setFont(font);
    profileMenu->setFont(font);
    medicinesMenu->setFont(font);
    kanbanBoard->setFont(font);
    staffOption->setFont(font);
    customerCare->setFont(font);
    salesMenu->setFont(font);
    hideButton->setFont(font);
    generateBillButton->setFont(font);
    generateReceiptButton->setFont(font);
}

void MainWindow::handleSetOpacityButton()
{
    sliderDialog =new SliderDialog(this);
    connect(sliderDialog->slider,&QSlider::sliderMoved,this,&MainWindow::handleSetOpacity);
    if(sliderDialog->exec()==QDialog::Accepted){
        return;
    }
}

void MainWindow::handleSetOpacity()
{
    double opacityValue = static_cast<double>(sliderDialog->slider->value()) / 100.0;
    this->setWindowOpacity(opacityValue);
}







void MainWindow::handleHideButton()
{
    static bool isHidden = false;

    if (!isHidden) {
        hideButton->setText("Show Panel");
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
    /////////Profile Menu
    profileMenu->hide();
    /////////Profile Menu
    /////////Medicine Menu
    medicinesMenu->hide();
    medicinesMenu->medicinesTable->hide();
    medicinesMenu->medicinesTable->setGeometry(medicinesMenu->medicineTableGeometry);
    medicinesMenu->settingColumnsWidth();
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
    /////////CustomerCare  Menu
    customerCare->hide();
    /////////CustomerCare  Menu
    /////////Staff Menu
    staffOption->hide();
    /////////Staff Menu
    QString currentText =listMenu->currentItem()->text();
    if(currentText==profileName){
        profileMenu->show();
    }
    if(currentText=="Medicines"){
        medicinesMenu->medicinesTable->show();
        medicinesMenu->show();
    }
    if(currentText=="Orders&Delivery"){
        kanbanBoard->show();
        medicinesMenu->medicinesTable->show();
        medicinesMenu->medicinesTable->setGeometry(820,0,510,700);
    }
    if(currentText=="Staff"){
        staffOption->show();
    }
    if(currentText=="Sales And Reports"){
        salesMenu->show();
    }
    if(currentText=="Generate Bill"){
        medicinesMenu->medicinesTable->show();
        generateBillButton->show();
        generateReceiptButton->show();
    }
    if(currentText=="Customer Care"){
        customerCare->initializeList();
        customerCare->show();
    }
}


int billInputHeight =100;
int billInputWidth =400;
void MainWindow::handleBillButton()
{
    if(generateBillButton->isChecked()){
        totalForSalesAndReports=0.0;
        order="";
        receiptText="";
    }
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
        for (int row = 0; row < medicinesMenu->medicinesTable->rowCount(); ++row) {
            medicinesMenu->itemTable =medicinesMenu->medicinesTable->item(row,0);
            if(medicinesMenu->itemTable && medicinesMenu->itemTable->text().contains(billInput->getName(), Qt::CaseInsensitive)){
                rowNumber=row;
                if(billInput->getmg()!=medicinesMenu->medicinesTable->item(row,3)->text()||billInput->getQuantity().toFloat()>medicinesMenu->medicinesTable->item(row,2)->text().toFloat()) {
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
        newLine.append(medicinesMenu->medicinesTable->item(rowNumber,1)->text());
        order.append("Price : "+medicinesMenu->medicinesTable->item(rowNumber,1)->text()+"\n");
        padRight(newLine);
        newLine.append(billInput->getmg());
        order.append("MG : "+billInput->getmg()+"\n");
        padRight(newLine);
        newLine.append(QString::number(billInput->getQuantity().toFloat()*medicinesMenu->medicinesTable->item(rowNumber,1)->text().toFloat()));
        order.append("$/Quantity : "+QString::number(billInput->getQuantity().toFloat()*medicinesMenu->medicinesTable->item(rowNumber,1)->text().toFloat())+"\n");
        padRight(newLine);
        newLine.append("\n");
        order.append("\n");
        receiptText.append(newLine);
        if(rowNumber==-1){
            total+=0;
            totalForSalesAndReports+=0;
        }else {
            total+=billInput->getQuantity().toFloat()*medicinesMenu->medicinesTable->item(rowNumber,1)->text().toFloat();
            totalForSalesAndReports+=billInput->getQuantity().toFloat()*medicinesMenu->medicinesTable->item(rowNumber,1)->text().toFloat();
        }
        billInput->setName("");
        for (int row = 0; row < medicinesMenu->medicinesTable->rowCount(); ++row) {
            medicinesMenu->medicinesTable->showRow(row);
        }
        if(billInput->isOkButtonClicked()){
            return;
        }
        if(billInput->isAddMoreButtonClicked()){
            handleBillButton();
        }
    }

    billInput->setName("");
    for (int row = 0; row < medicinesMenu->medicinesTable->rowCount(); ++row) {
        medicinesMenu->medicinesTable->showRow(row);
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
        for (int row = 0; row <medicinesMenu->medicinesTable->rowCount(); ++row) {
            medicinesMenu->itemTable =medicinesMenu->medicinesTable->item(row,0);
            if(medicinesMenu->itemTable && medicinesMenu->itemTable->text().contains(billInput->getName(), Qt::CaseInsensitive)){
                rowNumber=row;
                if(billInput->getmg()!=medicinesMenu->medicinesTable->item(row,3)->text()||billInput->getQuantity().toFloat()>medicinesMenu->medicinesTable->item(row,2)->text().toFloat()) {
                    QMessageBox::warning(this,"Invalid Input","Enter proper data!!!(Maybe Quantity OR Mg You entered is not correct)");
                    totalForSalesAndReports=0.0;
                    return;
                }
            }
        }
        if(rowNumber==-1){
            totalPricePerItem+=0;
        }else{
            totalPricePerItem+=billInput->getQuantity().toFloat()*medicinesMenu->medicinesTable->item(rowNumber,1)->text().toFloat();
        }
        totalForSalesAndReports+=totalPricePerItem;
        kanbanBoard->deliveryInput->setTotal(kanbanBoard->deliveryInput->getTotal()+totalPricePerItem);
        kanbanBoard->deliveryInput->setOrder(kanbanBoard->deliveryInput->getOrder()+"Medicine : "+billInput->getName()
                                             +"\nQuantity : "+billInput->getQuantity()+
                                             "\nPrice : "+medicinesMenu->medicinesTable->item(rowNumber,1)->text()+
                                             "\nPrice/Quantity : "+QString::number(totalPricePerItem)+"\n\n");
        billInput->setName("");
        for (int row = 0; row < medicinesMenu->medicinesTable->rowCount(); ++row) {
            medicinesMenu->medicinesTable->showRow(row);
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
    for (int row = 0; row < medicinesMenu->medicinesTable->rowCount(); ++row) {
        medicinesMenu->medicinesTable->showRow(row);
    }
}


void MainWindow::handleLineEdits()
{
    for (int row = 0; row < medicinesMenu->medicinesTable->rowCount(); ++row) {
        medicinesMenu->itemTable =medicinesMenu->medicinesTable->item(row,0);
        if(medicinesMenu->itemTable && medicinesMenu->itemTable->text().contains(billInput->getName(), Qt::CaseInsensitive)){
            billInput->setIntValidatorRange(0,medicinesMenu->medicinesTable->item(row,3)->text().toInt());
            billInput->setDoubleValidatorRange(0.0,medicinesMenu->medicinesTable->item(row,2)->text().toFloat());
            billInput->setCompanyLine(medicinesMenu->medicinesTable->item(row,4)->text());
        }
    }
    medicinesMenu->filterTable(billInput->getName());
}

void MainWindow::printReceipt(QString &receiptText)
{
    receiptText.append("\nTotal : "+QString::number(total)+"\n");
    receiptText.append("===============================================================\n");
    receiptText.append("Thank you for your purchase!\n");
    total=0;
    QString finalText="";
    finalText.append("Receipt\n");
    finalText.append("===============================================================\n");
    finalText.append("Name             Quantity         Price            Mg         TotalPrice/item\n");
    finalText.append(receiptText);
    finalText.append("\nTotal : "+QString::number(total)+"\n");
    finalText.append("===============================================================\n");
    finalText.append("Thank you for your purchase!\n");

    QPrinter printer;
    printer.setPrinterName("Microsoft Print to PDF");
    printer.setPageSize(QPageSize::A4);
    printer.setPageOrientation(QPageLayout::Portrait);

    QPrintDialog printDialog(&printer);
    if (printDialog.exec() != QDialog::Accepted) {
        receiptText="";
        order="";
        totalForSalesAndReports=0.0;
        return;
    }

    QPainter painter(&printer);
    QFont font = painter.font();
    font.setPointSize(12);
    painter.setFont(font);

    QRect rect = painter.viewport();
    int margin = 50;
    rect.adjust(margin, margin, -margin, -margin);
    if (!rect.isValid()) {
        qDebug() << "Invalid rectangle for drawing.";
        painter.end();
        return;
    }

    if (finalText.isEmpty()) {
        qDebug() << "No text to print.";
        painter.end();
        return;
    }

    painter.drawText(rect, Qt::AlignLeft | Qt::TextWordWrap, finalText);

    painter.end();
    receiptText="";
    if(order!=""&&totalForSalesAndReports!=0.0){
        order.append("\n\nTotal : "+QString::number(totalForSalesAndReports));
        salesMenu->addSalesRow(totalForSalesAndReports,true,"N/A","N/A","N/A",order);
        order="";
        totalForSalesAndReports=0.0;
    }
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
            item = kanbanBoard->doneList->item(j);
            if(item && item->text().contains("Name : "+customer["Name"].toString()+"\nID : "+customer["OrderID"].toString()+"\nAddress : "+customer["Address"].toString()+"\nPhone : "+customer["PhoneNumber"].toString(), Qt::CaseInsensitive)){
                salesMenu->setDeliveryStatus(customer["Name"].toString(),customer["Order"].toString());
            }
        }
    }
}
