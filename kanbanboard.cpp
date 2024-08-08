#include "kanbanboard.h"


int KanbanBoard::id=0;
KanbanBoard::KanbanBoard(QWidget *parent)
    : QWidget{parent}
{
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
    json kanbanFile;
    kanbanFile["ToDo"]=json::array();
    for (int i = 0; i < todoList->count(); ++i) {
        json obj;
        obj["content"]=todoList->item(i)->text().toStdString();
        kanbanFile["ToDo"].push_back(obj);
    }
    kanbanFile["InProgress"]=json::array();
    for (int i = 0; i < inProgressList->count(); ++i) {
        json obj;
        obj["content"]=inProgressList->item(i)->text().toStdString();
        kanbanFile["InProgress"].push_back(obj);
    }
    kanbanFile["Done"]=json::array();
    for (int i = 0; i < doneList->count(); ++i) {
        json obj;
        obj["content"]=doneList->item(i)->text().toStdString();
        kanbanFile["Done"].push_back(obj);
    }
    std::ofstream fOut ("Kanban.json");
    fOut<<kanbanFile.dump(4);
    fOut.close();
}

void KanbanBoard::readFromJson()
{
    json kanbanFile;
    std::ifstream fIn("Kanban.json");
    try {
        fIn >> kanbanFile;
    } catch (json::parse_error &e) {
        qDebug() << "Parse error: " << e.what();
        return;
    }
    for (const auto & i  : kanbanFile["ToDo"]) {
        listItem =new QListWidgetItem(QIcon(":/delivery-bike.ico"),QString::fromStdString(i["content"]));
        todoList->addItem(listItem);
    }
    for (const auto & i  : kanbanFile["InProgress"]) {
        listItem =new QListWidgetItem(QIcon(":/delivery-bike.ico"),QString::fromStdString(i["content"]));
        inProgressList->addItem(listItem);
    }for (const auto & i  : kanbanFile["Done"]) {
        listItem =new QListWidgetItem(QIcon(":/delivery-bike.ico"),QString::fromStdString(i["content"]));
        doneList->addItem(listItem);
    }
}





void KanbanBoard::handleAddDelivery()
{
    if(deliveryInput->isHidden()){
        deliveryInput->show();
    }
    // deliveryInput =new DeliveryInputDialog (this);
    if (deliveryInput->exec() == QDialog::Accepted) {
        if(deliveryInput->getName().isEmpty()||deliveryInput->getAddress().isEmpty()||deliveryInput->getPhoneNumber().isEmpty()||deliveryInput->getOrder().isEmpty()){
            QMessageBox::warning(this,"Invalid Input","Enter complete data!!!From DeliveryInput");
            return;
        }
        listItem=new QListWidgetItem(QIcon(":/delivery-bike.ico"),"Name : "+deliveryInput->getName()+"\nID : "+QString::number(++id)+"\nAddress : "+deliveryInput->getAddress()+"\nPhone : "+deliveryInput->getPhoneNumber()+"\nOrder : "+deliveryInput->getOrder()+"Total  : "+QString::number(deliveryInput->getTotal()));
        todoList->addItem(listItem);
        deliveryInput->setOrder("");
        deliveryInput->setTotal(0.0);

    }
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
