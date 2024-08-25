#include "medicinesmenu.h"

MedicinesMenu::MedicinesMenu(QWidget *parent)
    : QWidget{parent}
{
    buttonsLayout = new QVBoxLayout();
    mainLayout = new QHBoxLayout(this);
    //////////////////////////////////////// Medicines Table
    medicinesTable = new QTableWidget(0, 5,parent);
    medicinesTable->hide();
    QStringList headers = { "Name", "Price", "Quantity", "MG", "Company" };
    medicinesTable->setHorizontalHeaderLabels(headers);
    medicinesTable->setFont(QFont("Times New Roman", 14, 13));
    medicineTableGeometry = {190,0,680,700};
    medicinesTable->setGeometry(medicineTableGeometry);

    settingColumnsWidth();
    //////////////////////////////////////// Search Bar and Button
    QWidget *searchContainer = new QWidget(this);
    searchContainer->setFixedSize(230, 26);

    QHBoxLayout *searchLayout = new QHBoxLayout(searchContainer);
    searchLayout->setContentsMargins(0, 0, 0, 0);
    searchLayout->setSpacing(0);
    searchBar = new QLineEdit(searchContainer);
    searchBar->setFixedHeight(26);
    searchBar->setPlaceholderText("Search");
    searchBar->setStyleSheet("QLineEdit {"
                             "border-radius: 13px;"
                             "padding-left: 10px;"
                             "}");

    searchButton = new QPushButton(searchContainer);
    searchButton->setIcon(QIcon(":/search.ico"));
    searchButton->setFixedSize(26, 26);
    searchButton->setStyleSheet("QPushButton {"
                                "border: none;"
                                "background: transparent;"
                                "margin: 0px;"
                                "padding: 0px;"
                                "}");

    searchLayout->addWidget(searchBar);
    searchLayout->addWidget(searchButton);
    //////////////////////////////////////// Add and Remove Buttons
    addButton = new QPushButton(QIcon(":/add.ico"), "Add Row", this);
    removeButton = new QPushButton(QIcon(":/removeButton.ico"), "Delete Row", this);

    addButton->setFixedSize(205, 60);
    removeButton->setFixedSize(205, 60);

    addButton->setIconSize(QSize(55, 55));
    removeButton->setIconSize(QSize(40, 40));

    addButton->setFont(QFont("Times New Roman", 14));
    addButton->setStyleSheet("QPushButton {"
                             "border-radius: 10px;"
                             "color: green;"
                             "padding: 5px 10px;"
                             "}");

    removeButton->setFont(QFont("Times New Roman", 14));
    removeButton->setStyleSheet("QPushButton {"
                                "border-radius: 10px;"
                                "color: red;"
                                "padding: 5px 10px;"
                                "}");
    //////////////////////////////////////// Setting Layouts
    // mainLayout->addWidget(medicinesTable);
    buttonsLayout->addWidget(searchContainer);
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(removeButton);

    mainLayout->addLayout(buttonsLayout);
    //////////////////////////////////////// Signal-Slot Connections
    connect(addButton, &QPushButton::clicked, this, &MedicinesMenu::handleAddRowButton);
    connect(removeButton, &QPushButton::clicked, this, &MedicinesMenu::handleRemoveRowButton);
    connect(searchBar, &QLineEdit::textChanged, this, &MedicinesMenu::handleSearchBarAndButton);
    connect(searchButton, &QPushButton::clicked, this, &MedicinesMenu::handleSearchBarAndButton);
    // Reading Medicines data into the table
    readMedicineTableFromJson();
}




MedicinesMenu::~MedicinesMenu(){
    writeMedicinesTableToJson();
}


void MedicinesMenu::filterTable(const QString &text)
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


void MedicinesMenu::writeMedicinesTableToJson()
{
    qDebug()<<"Writing MedicinesTable to json";
    QJsonObject medicinesFile;
    QJsonArray medicinesArray;
    for (int row = 0; row < medicinesTable->rowCount(); ++row) {
        QJsonObject jsonRow;
        jsonRow["Name"] = medicinesTable->item(row, 0) ? medicinesTable->item(row, 0)->text() : "";
        jsonRow["Price"] = medicinesTable->item(row, 1) ? medicinesTable->item(row, 1)->text() : "";
        jsonRow["Quantity"] = medicinesTable->item(row, 2) ? medicinesTable->item(row, 2)->text() : "";
        jsonRow["Mg"] = medicinesTable->item(row, 3) ? medicinesTable->item(row, 3)->text() : "";
        jsonRow["Company"] = medicinesTable->item(row, 4) ? medicinesTable->item(row, 4)->text() : "";
        medicinesArray.append(jsonRow);
    }
    medicinesFile["MedicinesTable"] = medicinesArray;
    QJsonDocument jsonDoc(medicinesFile);
    QFile fOut("Medicines.json");
    if (fOut.open(QIODevice::WriteOnly)) {
        fOut.write(jsonDoc.toJson(QJsonDocument::Indented));
        fOut.close();
    } else {
        qDebug() << "Unable to open file for writing.";
    }
}


void MedicinesMenu::readMedicineTableFromJson()
{
    QFile file("Medicines.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to open file.";
        return;
    }
    QByteArray jsonData = file.readAll();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData));
    file.close();
    if (!jsonDoc.isObject()) {
        qDebug() << "JSON document is not an object.";
        return;
    }
    QJsonObject jsonObj = jsonDoc.object();
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

            itemTable = new QTableWidgetItem(data0);
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

void MedicinesMenu::settingColumnsWidth()
{
    int numericColumnsWidth=80;
    medicinesTable->setColumnWidth(0,200);
    medicinesTable->setColumnWidth(4,200);
    medicinesTable->setColumnWidth(1,numericColumnsWidth);
    medicinesTable->setColumnWidth(2,numericColumnsWidth);
    medicinesTable->setColumnWidth(3,numericColumnsWidth);
}


void MedicinesMenu::handleSearchBarAndButton()
{
    filterTable(searchBar->text());
}

void MedicinesMenu::handleRemoveRowButton()
{
    int rowNumber = QInputDialog ::getInt(this,"Delete Row","Enter Row number to delete");
    if(rowNumber>0&&rowNumber<=medicinesTable->rowCount()){
        medicinesTable->removeRow(rowNumber-1);
    }else{
        QMessageBox::warning(this,"Invalid Input","Enter a Number from the Table!!!");
    }
}

void MedicinesMenu::handleAddRowButton()
{
    inputMedicine =new InputDialog(this);
    if (inputMedicine->exec() == QDialog::Accepted) {
        if(inputMedicine->getName().isEmpty()||inputMedicine->getQuantity().isEmpty()||inputMedicine->getCompany().isEmpty()||inputMedicine->getPrice().isEmpty()||inputMedicine->getmg().isEmpty()){
            QMessageBox::warning(this,"Invalid Input","Enter complete data!!!");
            return;
        }
        medicinesTable->setRowCount(medicinesTable->rowCount()+1);

        itemTable=new QTableWidgetItem(inputMedicine->getName());
        itemTable->setFlags(itemTable->flags()& ~Qt::ItemIsEditable);
        medicinesTable->setItem(medicinesTable->rowCount()-1,0,itemTable);
        itemTable =new QTableWidgetItem(inputMedicine->getCompany());
        itemTable->setFlags(itemTable->flags()& ~Qt::ItemIsEditable);
        medicinesTable->setItem(medicinesTable->rowCount()-1,4,itemTable);
        itemTable =new QTableWidgetItem(inputMedicine->getPrice());
        itemTable->setFlags(itemTable->flags()& ~Qt::ItemIsEditable);
        medicinesTable->setItem(medicinesTable->rowCount()-1,1,itemTable);
        itemTable=new QTableWidgetItem(inputMedicine->getmg());
        itemTable->setFlags(itemTable->flags()& ~Qt::ItemIsEditable);
        medicinesTable->setItem(medicinesTable->rowCount()-1,3,itemTable);
        itemTable =new QTableWidgetItem(inputMedicine->getQuantity());
        itemTable->setFlags(itemTable->flags()& ~Qt::ItemIsEditable);
        medicinesTable->setItem(medicinesTable->rowCount()-1,2,itemTable);

    }
}
