#include "kanbanboard.h"

KanbanBoard::KanbanBoard(QWidget *parent)
    : QWidget{parent}
{
    mainLayout = new QVBoxLayout(this);
    boardLayout = new QHBoxLayout();

    // To Do Column
    todoLayout = new QVBoxLayout();
    todoLabel = new QLabel("To Do");
    todoList = new QListWidget();
    todoLayout->addWidget(todoLabel);
    todoLayout->addWidget(todoList);

    // In Progress Column
    inProgressLayout = new QVBoxLayout();
    inProgressLabel = new QLabel("In Progress");
    inProgressList = new QListWidget();
    inProgressLayout->addWidget(inProgressLabel);
    inProgressLayout->addWidget(inProgressList);

    // Done Column
    doneLayout = new QVBoxLayout();
    doneLabel = new QLabel("Done");
    doneList = new QListWidget();
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
    inProgressList->setDragEnabled(true);
    doneList->setDragEnabled(true);
    todoList->setDragEnabled(true);
    inProgressList->setAcceptDrops(true);
    doneList->setAcceptDrops(true);
    todoList->setAcceptDrops(true);
    // making Button
    addDeliveryButton =new QPushButton(QIcon(":/add.ico"),"Add Delivery",this);
    addDeliveryButton->setGeometry(850,0,205,60);
    addDeliveryButton->setIconSize(QSize(50,50));
    addDeliveryButton->setFont(QFont("Times New Roman",14));
    // Add all columns to board layout
    boardLayout->addLayout(todoLayout);
    boardLayout->addLayout(inProgressLayout);
    boardLayout->addLayout(doneLayout);

    mainLayout->addLayout(boardLayout);
    mainLayout->addWidget(addDeliveryButton);
    setLayout(mainLayout);
    ///Connections
    connect(addDeliveryButton,SIGNAL(clicked(bool)),this,SLOT(handleAddDelivery()));
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
