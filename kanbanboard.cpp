#include "kanbanboard.h"

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

    // In Progress Column
    inProgressLayout = new QVBoxLayout();
    inProgressLabel = new QLabel("In Progress");
    inProgressList = new KanbanListWidget();
    inProgressLayout->addWidget(inProgressLabel);
    inProgressLayout->addWidget(inProgressList);

    // Done Column
    doneLayout = new QVBoxLayout();
    doneLabel = new QLabel("Done");
    doneList = new KanbanListWidget();
    doneLayout->addWidget(doneLabel);
    doneLayout->addWidget(doneList);
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
    //Enabling Drag And Drop
    todoList->setDragEnabled(true);
    todoList->setAcceptDrops(true);
    inProgressList->setDragEnabled(true);
    inProgressList->setAcceptDrops(true);
    doneList->setDragEnabled(true);
    doneList->setAcceptDrops(true);
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
    connect(todoList,SIGNAL(currentRowChanged(int)),this,SLOT(handleListsItems()));
    connect(inProgressList,SIGNAL(currentRowChanged(int)),this,SLOT(handleListsItems()));
    connect(doneList,SIGNAL(currentRowChanged(int)),this,SLOT(handleListsItems()));
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





void KanbanBoard::handleAddDelivery()
{
    listItem=new QListWidgetItem(QIcon(":/delivery-bike.ico"),QInputDialog::getText(this,"Delivery-Details","Enter Deatails"));
    listItem->setSizeHint(QSize(50,60));
    todoList->addItem(listItem);
}

void KanbanBoard::handleListsItems()
{
    // Disconnect signals to prevent re-triggering during modifications
    disconnect(todoList, SIGNAL(currentRowChanged(int)), this, SLOT(handleListsItems()));
    disconnect(inProgressList, SIGNAL(currentRowChanged(int)), this, SLOT(handleListsItems()));
    disconnect(doneList, SIGNAL(currentRowChanged(int)), this, SLOT(handleListsItems()));

    // Perform the list modifications
    for (int i = 0; i < todoList->count(); ++i) {
        for (int j = 0; j < inProgressList->count(); ++j) {
            if (todoList->item(i)->text() == inProgressList->item(j)->text()) {
                delete todoList->takeItem(i);

                --i; // Adjust index i after deletion
                break; // Exit inner loop since the item was removed
            }
        }
    }
    for (int j = 0; j < inProgressList->count(); ++j) {
        for (int k = 0; k < doneList->count(); ++k) {
            if (inProgressList->item(j)->text() == doneList->item(k)->text()) {
                delete inProgressList->takeItem(j);
                --j; // Adjust index j after deletion
                break; // Exit innermost loop since the item was removed
            }
        }
    }
    for (int i = todoList->count() - 1; i >= 0; --i) {
        for (int j = i - 1; j >= 0; --j) {
            if (todoList->item(i)->text() == todoList->item(j)->text()) {
                delete todoList->takeItem(i);
                break; // No need to check further once a duplicate is removed
            }
        }
    }
    for (int i = inProgressList->count() - 1; i >= 0; --i) {
        for (int j = i - 1; j >= 0; --j) {
            if (inProgressList->item(i)->text() == inProgressList->item(j)->text()) {
                delete inProgressList->takeItem(i);
                break; // No need to check further once a duplicate is removed
            }
        }
    }
    for (int i = doneList->count() - 1; i >= 0; --i) {
        for (int j = i - 1; j >= 0; --j) {
            if (doneList->item(i)->text() == doneList->item(j)->text()) {
                delete doneList->takeItem(i);
                break; // No need to check further once a duplicate is removed
            }
        }
    }
    // Reconnect signals after modifications are done
    connect(todoList, SIGNAL(currentRowChanged(int)), this, SLOT(handleListsItems()));
    connect(inProgressList, SIGNAL(currentRowChanged(int)), this, SLOT(handleListsItems()));
    connect(doneList, SIGNAL(currentRowChanged(int)), this, SLOT(handleListsItems()));
}
