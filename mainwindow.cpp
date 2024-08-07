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
    ordersAndDeliveryMenu();
    readMedicineTableFromJson();
    connect(kanbanBoard->deliveryInput->orderButton,SIGNAL(clicked(bool)),this,SLOT(handleOrderButton()));
}

MainWindow::~MainWindow() {
    writeMedicinesTableToJson();
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
    if(medicinesTable!=nullptr){
        hbox->removeWidget(medicinesTable);
        delete medicinesTable;
        delete searchButton;
    }
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
    medicineTableGeometry=totalWidth+10;
    medicinesTable->setGeometry(200,0,totalWidth+10,700);
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
    connect(searchBar, &QLineEdit::textChanged, this, &MainWindow::handleSearchBarAndButton);
    connect(searchButton,SIGNAL(clicked(bool)), this,SLOT(handleSearchBarAndButton()));
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
    json medicinesFile;
    medicinesFile["MedicinesTable"] = json::array();

    for (int row = 0; row < medicinesTable->rowCount(); ++row) {
        json jsonRow;
        jsonRow["Name"] = medicinesTable->item(row, 0) ? medicinesTable->item(row, 0)->text().toStdString() : "";
        jsonRow["Price"] = medicinesTable->item(row, 1) ? medicinesTable->item(row, 1)->text().toStdString() : "";
        jsonRow["Quantity"] = medicinesTable->item(row, 2) ? medicinesTable->item(row, 2)->text().toStdString() : "";
        jsonRow["Mg"] = medicinesTable->item(row, 3) ? medicinesTable->item(row, 3)->text().toStdString() : "";
        jsonRow["Company"] = medicinesTable->item(row, 4) ? medicinesTable->item(row, 4)->text().toStdString() : "";

        medicinesFile["MedicinesTable"].push_back(jsonRow);
    }
    std::ofstream fOut("Medicines.json");
    fOut << medicinesFile.dump(4);
    fOut.close();
}

void MainWindow::readMedicineTableFromJson()
{
    json medicineFile;
    std::ifstream fIn("Medicines.json");
    try {
        fIn >> medicineFile;
    } catch (json::parse_error &e) {
        qDebug() << "Parse error: " << e.what();
        return;
    }
    json medicineTableFromJson = medicineFile["MedicinesTable"];
    medicinesTable->setRowCount(medicineTableFromJson.size());
    int row = 0;
    for (const auto &i : medicineTableFromJson) {
        QString data0 = QString::fromStdString(i["Name"]);
        QString data1 = QString::fromStdString(i["Price"]);
        QString data2 = QString::fromStdString(i["Quantity"]);
        QString data3 = QString::fromStdString(i["Mg"]);
        QString data4 = QString::fromStdString(i["Company"]);
        itemTable =new QTableWidgetItem(data0);
        itemTable->setFlags(itemTable->flags()& ~Qt::ItemIsEditable);
        medicinesTable->setItem(row, 0, itemTable);
        itemTable =new QTableWidgetItem(data1);
        itemTable->setFlags(itemTable->flags()& ~Qt::ItemIsEditable);
        medicinesTable->setItem(row, 1, itemTable);
        itemTable =new QTableWidgetItem(data2);
        itemTable->setFlags(itemTable->flags()& ~Qt::ItemIsEditable);
        medicinesTable->setItem(row, 2, itemTable);
        itemTable =new QTableWidgetItem(data3);
        itemTable->setFlags(itemTable->flags()& ~Qt::ItemIsEditable);
        medicinesTable->setItem(row, 3, itemTable);
        itemTable =new QTableWidgetItem(data4);
        itemTable->setFlags(itemTable->flags()& ~Qt::ItemIsEditable);
        medicinesTable->setItem(row, 4, itemTable);
        ++row;
    }
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
    /////////Medicine Menu
    /////////Bill Menu
    generateBillButton->hide();
    generateReceiptButton->hide();
    /////////Bill Menu
    /////////Orders&Delivery Menu
    kanbanBoard->hide();
    /////////Orders&Delivery Menu
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

}



void MainWindow::handleBillButton()
{
    int rowNumber;
    billInput =new BillInputDialog (this);
    connect(checkTimer,SIGNAL(timeout()),this,SLOT(handleLineEdits()));
    checkTimer->start(1000);
    if (billInput->exec() == QDialog::Accepted) {
        if(billInput->getName().isEmpty()||billInput->getQuantity().isEmpty()||billInput->getCompany().isEmpty()||billInput->getmg().isEmpty()){
            QMessageBox::warning(this,"Invalid Input","Enter complete data!!!");
            return;
        }
        for (int row = 0; row < medicinesTable->rowCount(); ++row) {
            itemTable =medicinesTable->item(row,0);
            if(itemTable && itemTable->text().contains(billInput->getName(), Qt::CaseInsensitive)){
                rowNumber=row;
                if(billInput->getmg()!=medicinesTable->item(row,3)->text()||billInput->getQuantity().toFloat()>medicinesTable->item(row,2)->text().toFloat()) {
                    QMessageBox::warning(this,"Invalid Input","Enter proper data!!!(Maybe Quantity OR Mg You entered is not correct)");
                    return;
                }
            }
        }
        QString newLine="";
        newLine.append(billInput->getName());
        padRight(newLine);
        newLine.append(billInput->getQuantity());
        padRight(newLine);
        newLine.append(medicinesTable->item(rowNumber,1)->text());
        padRight(newLine);
        newLine.append(billInput->getmg());
        padRight(newLine);
        newLine.append(QString::number(billInput->getQuantity().toFloat()*medicinesTable->item(rowNumber,1)->text().toFloat()));
        padRight(newLine);
        newLine.append("\n");
        receiptText.append(newLine);
        total+=billInput->getQuantity().toFloat()*medicinesTable->item(rowNumber,1)->text().toFloat();
        if(billInput->isAddMoreButtonClicked()){

            handleBillButton();
        }
    }
}

void MainWindow::handleOrderButton()
{
    int rowNumber;
    billInput =new BillInputDialog (this);
    connect(checkTimer,SIGNAL(timeout()),this,SLOT(handleLineEdits()));
    checkTimer->start(1000);
    if (billInput->exec() == QDialog::Accepted) {
        if(billInput->getName().isEmpty()||billInput->getQuantity().isEmpty()||billInput->getCompany().isEmpty()||billInput->getmg().isEmpty()){
            QMessageBox::warning(this,"Invalid Input","Enter complete data!!!");
            return;
        }
        for (int row = 0; row < medicinesTable->rowCount(); ++row) {
            itemTable =medicinesTable->item(row,0);
            if(itemTable && itemTable->text().contains(billInput->getName(), Qt::CaseInsensitive)){
                rowNumber=row;
                if(billInput->getmg()!=medicinesTable->item(row,3)->text()||billInput->getQuantity().toFloat()>medicinesTable->item(row,2)->text().toFloat()) {
                    QMessageBox::warning(this,"Invalid Input","Enter proper data!!!(Maybe Quantity OR Mg You entered is not correct)");
                    return;
                }
            }
        }
        total+=billInput->getQuantity().toFloat()*medicinesTable->item(rowNumber,1)->text().toFloat();
        kanbanBoard->deliveryInput->setTotal(kanbanBoard->deliveryInput->getTotal()+total);
        kanbanBoard->deliveryInput->setOrder(kanbanBoard->deliveryInput->getOrder()+"Medicine : "+billInput->getName()+" Quantity : "+billInput->getQuantity()+" Price : "+medicinesTable->item(rowNumber,1)->text()+" Price/Quantity : "+QString::number(billInput->getQuantity().toFloat()*medicinesTable->item(rowNumber,1)->text().toFloat())+"\n");
        total=0;
        if(billInput->isAddMoreButtonClicked()){
            handleBillButton();
        }
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


