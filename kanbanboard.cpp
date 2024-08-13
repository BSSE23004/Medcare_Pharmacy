#include "kanbanboard.h"


int KanbanBoard::orderId=0;
KanbanBoard::KanbanBoard(QWidget *parent, SalesAndReports *menu)
    : QWidget{parent}
{
    setOrderIDInitialValue();
    salesMenu=menu;
    mainLayout = new QVBoxLayout(this);
    boardLayout = new QHBoxLayout();
    // To Do Column
    todoLayout = new QVBoxLayout();
    todoLabel = new QLabel("To Do");
    todoList = new KanbanListWidget();
    todoLayout->addWidget(todoLabel);
    todoLayout->addWidget(todoList);
    todoList->setStyleSheet("color : red");
    // In Progress Column
    inProgressLayout = new QVBoxLayout();
    inProgressLabel = new QLabel("In Progress");
    inProgressList = new KanbanListWidget();
    inProgressLayout->addWidget(inProgressLabel);
    inProgressLayout->addWidget(inProgressList);
    inProgressList->setStyleSheet("color : yellow");
    // Done Column
    doneLayout = new QVBoxLayout();
    doneLabel = new QLabel("Done");
    doneList = new KanbanListWidget();
    doneLayout->addWidget(doneLabel);
    doneLayout->addWidget(doneList);
    doneList->setStyleSheet("color : green");
    //Seting Size
    const int listIconsSizew=40;
    const int listIconsSizeh=40;
    const int listFontSize=14;
    todoList->setIconSize(QSize(listIconsSizew,listIconsSizeh));
    todoList->setUniformItemSizes(true);
    inProgressList->setIconSize(QSize(listIconsSizew,listIconsSizeh));
    inProgressList->setUniformItemSizes(true);
    doneList->setIconSize(QSize(listIconsSizew,listIconsSizeh));
    doneList->setUniformItemSizes(true);
    todoLabel->setMinimumSize(50,50);
    inProgressLabel->setMinimumSize(50,50);
    doneLabel->setMinimumSize(50,50);
    todoList->setFont(QFont("Times New Roman",listFontSize));
    inProgressList->setFont(QFont("Times New Roman",listFontSize));
    doneList->setFont(QFont("Times New Roman",listFontSize));
    todoLabel->setFont(QFont("Times New Roman",14));
    inProgressLabel->setFont(QFont("Times New Roman",14));
    doneLabel->setFont(QFont("Times New Roman",14));
    todoLabel->setStyleSheet("color : red");
    inProgressLabel->setStyleSheet("color : yellow");
    doneLabel->setStyleSheet("color : green");
    // making Button
    buttonLayout =new QHBoxLayout();
    addDeliveryButton =new QPushButton(QIcon(":/add.ico"),"Add Delivery",this);
    addDeliveryButton->setGeometry(850,0,205,60);
    addDeliveryButton->setIconSize(QSize(50,50));
    addDeliveryButton->setFont(QFont("Times New Roman",14));
    removeDeliveryButton =new QPushButton(QIcon(":/removeButton.ico"),"Remove Delivery",this);
    removeDeliveryButton->setGeometry(850,0,205,60);
    removeDeliveryButton->setIconSize(QSize(40,50));
    removeDeliveryButton->setFont(QFont("Times New Roman",14));
    buttonLayout->addWidget(removeDeliveryButton);
    buttonLayout->addWidget(addDeliveryButton);
    // Add all columns to board layout
    boardLayout->addLayout(todoLayout);
    boardLayout->addLayout(inProgressLayout);
    boardLayout->addLayout(doneLayout);
    mainLayout->addLayout(boardLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
    ///Connections
    connect(addDeliveryButton,SIGNAL(clicked(bool)),this,SLOT(handleAddDelivery()));
    connect(removeDeliveryButton,SIGNAL(clicked(bool)),this,SLOT(handleRemoveDelivery()));
    connect(todoList,SIGNAL(currentRowChanged(int)),this,SLOT(handleListsItems()));
    connect(inProgressList,SIGNAL(currentRowChanged(int)),this,SLOT(handleListsItems()));
    connect(doneList,SIGNAL(currentRowChanged(int)),this,SLOT(handleListsItems()));
    deliveryInput =new DeliveryInputDialog (this);
    deliveryInput->hide();
}

KanbanBoard::~KanbanBoard()
{
    delete mainLayout;
    delete boardLayout;
    delete todoLayout;
    delete todoLabel;
    delete todoList;
    delete inProgressLayout;
    delete inProgressLabel;
    delete inProgressList;
    delete doneLayout;
    delete doneLabel;
    delete doneList;
    delete addDeliveryButton;
    delete listItem;
}

void KanbanBoard::writeToJson()
{
    // Create a QJsonObject to hold the JSON data
    QJsonObject kanbanFile;

    // Create QJsonArray for "ToDo" and populate it
    QJsonArray todoArray;
    for (int i = 0; i < todoList->count(); ++i) {
        QJsonObject obj;
        obj["content"] = todoList->item(i)->text();
        todoArray.append(obj);
    }
    kanbanFile["ToDo"] = todoArray;

    // Create QJsonArray for "InProgress" and populate it
    QJsonArray inProgressArray;
    for (int i = 0; i < inProgressList->count(); ++i) {
        QJsonObject obj;
        obj["content"] = inProgressList->item(i)->text();
        inProgressArray.append(obj);
    }
    kanbanFile["InProgress"] = inProgressArray;

    // Create QJsonArray for "Done" and populate it
    QJsonArray doneArray;
    for (int i = 0; i < doneList->count(); ++i) {
        QJsonObject obj;
        obj["content"] = doneList->item(i)->text();
        doneArray.append(obj);
    }
    kanbanFile["Done"] = doneArray;

    // Create QJsonDocument from the QJsonObject
    QJsonDocument jsonDoc(kanbanFile);

    // Write the JSON data to file
    QFile fOut("Kanban.json");
    if (fOut.open(QIODevice::WriteOnly)) {
        fOut.write(jsonDoc.toJson(QJsonDocument::Indented));
        fOut.close();
    } else {
        qDebug() << "Unable to open file for writing.";
    }

}

void KanbanBoard::readFromJson()
{
    QFile file("Kanban.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Unable to open file.";
        return;
    }

    QByteArray jsonData = file.readAll();
    QJsonDocument jsonDoc(QJsonDocument::fromJson(jsonData));

    if (!jsonDoc.isObject()) {
        qDebug() << "JSON document is not an object.";
        return;
    }

    QJsonObject jsonObj = jsonDoc.object();

    // Check if the JSON object contains the necessary keys
    if (!jsonObj.contains("ToDo") || !jsonObj.contains("InProgress") || !jsonObj.contains("Done")) {
        qDebug() << "JSON object is missing required keys.";
        return;
    }

    QJsonArray todoArray = jsonObj["ToDo"].toArray();
    QJsonArray inProgressArray = jsonObj["InProgress"].toArray();
    QJsonArray doneArray = jsonObj["Done"].toArray();

    // Populate the ToDo list
    for (const QJsonValue &value : todoArray) {
        if (value.isObject()) {
            QJsonObject itemObj = value.toObject();
            if (itemObj.contains("content")) {
                QString content = itemObj["content"].toString();
                QListWidgetItem *listItem = new QListWidgetItem(QIcon(":/delivery-bike.ico"), content);
                todoList->addItem(listItem);
            }
        }
    }

    // Populate the InProgress list
    for (const QJsonValue &value : inProgressArray) {
        if (value.isObject()) {
            QJsonObject itemObj = value.toObject();
            if (itemObj.contains("content")) {
                QString content = itemObj["content"].toString();
                QListWidgetItem *listItem = new QListWidgetItem(QIcon(":/delivery-bike.ico"), content);
                inProgressList->addItem(listItem);
            }
        }
    }

    // Populate the Done list
    for (const QJsonValue &value : doneArray) {
        if (value.isObject()) {
            QJsonObject itemObj = value.toObject();
            if (itemObj.contains("content")) {
                QString content = itemObj["content"].toString();
                QListWidgetItem *listItem = new QListWidgetItem(QIcon(":/delivery-bike.ico"), content);
                doneList->addItem(listItem);
            }
        }
    }

    file.close();
}



void KanbanBoard::setOrderIDInitialValue()
{
    int latestID = 0;
    QFile fIn("Customers.json");

    if (fIn.open(QIODevice::ReadOnly)) {
        QByteArray jsonData = fIn.readAll();
        fIn.close();

        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "Parse error: " << parseError.errorString();
            return;
        }

        if (!jsonDoc.isObject()) {
            qDebug() << "JSON is not an object.";
            return;
        }

        QJsonObject jsonObj = jsonDoc.object();

        if (!jsonObj.contains("Customers") || !jsonObj["Customers"].isArray()) {
            qDebug() << "Invalid JSON structure.";
            return;
        }

        QJsonArray customersJSONArray = jsonObj["Customers"].toArray();

        // Loop through the customers array
        for (const QJsonValue &value : customersJSONArray) {
            QJsonObject customer = value.toObject();
            if (customer.contains("OrderID")) {
                QString orderIdStr = customer["OrderID"].toString();
                bool ok;
                latestID = orderIdStr.toInt(&ok);
                if (ok && latestID > orderId) {
                    orderId=latestID;
                }
            }
        }
    } else {
        qDebug() << "Unable to open file.";
    }

}

int KanbanBoard::getOrderID()
{
    return orderId+1;
}

void KanbanBoard::handleAddDelivery()
{
    if(deliveryInput->isHidden()){
        deliveryInput->show();
        deliveryInput->setOkButtonClicked(false);
    }
    // deliveryInput =new DeliveryInputDialog (this);
    if (deliveryInput->exec() == QDialog::Accepted) {
        if(deliveryInput->getName().isEmpty()||deliveryInput->getAddress().isEmpty()||deliveryInput->getPhoneNumber().isEmpty()||deliveryInput->getOrder().isEmpty()){
            QMessageBox::warning(this,"Invalid Input","Enter complete data!!!From DeliveryInput");
            return;
        }
        listItem=new QListWidgetItem(QIcon(":/delivery-bike.ico"),"Name : "+deliveryInput->getName()+"\nID : "+QString::number(++orderId)+"\nAddress : "+deliveryInput->getAddress()+"\nPhone : "+deliveryInput->getPhoneNumber()+"\nOrder : "+deliveryInput->getOrder()+"Total  : "+QString::number(deliveryInput->getTotal()));
        todoList->addItem(listItem);
        customersName.append(deliveryInput->getName());
        customersPhoneNumbers.append(deliveryInput->getPhoneNumber());
        customersAddresses.append(deliveryInput->getAddress());
        deliveryInput->setOrder("");
        deliveryInput->setTotal(0.0);

    }

    deliveryInput->setOkButtonClicked(true);
    deliveryInput->hide();
}

void KanbanBoard::handleRemoveDelivery()
{
    QString id = QString::number(QInputDialog::getInt(this,"ID","Enter OrderID : ",0,1));
    for (int row = 0; row < todoList->count(); ++row) {
        QListWidgetItem *item = todoList->item(row);
        if (item && item->text().contains("ID : "+id, Qt::CaseInsensitive)) {
            delete todoList->takeItem(row);
            break;
        }
    }
    for (int row = 0; row < inProgressList->count(); ++row) {
        QListWidgetItem *item = inProgressList->item(row);
        if (item && item->text().contains("ID : "+id, Qt::CaseInsensitive)) {
            delete inProgressList->takeItem(row);
            break;
        }
    }
    for (int row = 0; row < doneList->count(); ++row) {
        QListWidgetItem *item = doneList->item(row);
        if (item && item->text().contains("ID : "+id, Qt::CaseInsensitive)) {
            delete doneList->takeItem(row);
            break;
        }
    }
}

void KanbanBoard::handleListsItems()
{
    // Disconnect signals to prevent re-triggering during modifications
    disconnect(todoList, SIGNAL(currentRowChanged(int)), this, SLOT(handleListsItems()));
    disconnect(inProgressList, SIGNAL(currentRowChanged(int)), this, SLOT(handleListsItems()));
    disconnect(doneList, SIGNAL(currentRowChanged(int)), this, SLOT(handleListsItems()));

    // Perform the list modifications
    // Remove items from inProgressList and todoList if they exist in doneList
    for (int i = 0; i < doneList->count(); ++i) {
        QString doneText = doneList->item(i)->text();

        // Remove matching items from inProgressList
        for (int j = 0; j < inProgressList->count(); ++j) {
            if (inProgressList->item(j)->text() == doneText) {
                delete inProgressList->takeItem(j);
                --j; // Adjust index after deletion
            }
        }

        // Remove matching items from todoList
        for (int k = 0; k < todoList->count(); ++k) {
            if (todoList->item(k)->text() == doneText) {
                delete todoList->takeItem(k);
                --k; // Adjust index after deletion
            }
        }
    }

    // Remove items from todoList if they exist in inProgressList
    for (int i = 0; i < inProgressList->count(); ++i) {
        QString inProgressText = inProgressList->item(i)->text();

        for (int j = 0; j < todoList->count(); ++j) {
            if (todoList->item(j)->text() == inProgressText) {
                delete todoList->takeItem(j);
                --j; // Adjust index after deletion
            }
        }
    }

    // for (int i = 0; i < todoList->count(); ++i) {
    //     for (int j = 0; j < inProgressList->count(); ++j) {
    //         if (todoList->item(i)->text() == inProgressList->item(j)->text()) {
    //             delete todoList->takeItem(i);
    //             --i; // Adjust index i after deletion
    //             break; // Exit inner loop since the item was removed
    //         }
    //     }
    // }
    // for (int j = 0; j < inProgressList->count(); ++j) {
    //     for (int k = 0; k < doneList->count(); ++k) {
    //         if (inProgressList->item(j)->text() == doneList->item(k)->text()) {
    //             delete inProgressList->takeItem(j);
    //             --j;
    //             break;
    //         }
    //     }
    // }
    // deleting duplicates
    for (int i = todoList->count() - 1; i >= 0; --i) {
        for (int j = i - 1; j >= 0; --j) {
            if (todoList->item(i)->text() == todoList->item(j)->text()) {
                delete todoList->takeItem(i);
                break;
            }
        }
    }
    for (int i = inProgressList->count() - 1; i >= 0; --i) {
        for (int j = i - 1; j >= 0; --j) {
            if (inProgressList->item(i)->text() == inProgressList->item(j)->text()) {
                delete inProgressList->takeItem(i);
                break;
            }
        }
    }
    for (int i = doneList->count() - 1; i >= 0; --i) {
        for (int j = i - 1; j >= 0; --j) {
            if (doneList->item(i)->text() == doneList->item(j)->text()) {
                delete doneList->takeItem(i);
                break;
            }
        }
    }
    // Reconnect signals after modifications are done
    connect(todoList, SIGNAL(currentRowChanged(int)), this, SLOT(handleListsItems()));
    connect(inProgressList, SIGNAL(currentRowChanged(int)), this, SLOT(handleListsItems()));
    connect(doneList, SIGNAL(currentRowChanged(int)), this, SLOT(handleListsItems()));
}
