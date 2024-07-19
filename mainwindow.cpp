#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(700,600);
    setWindowTitle("Pharmacy");
    setWindowOpacity(0.98);
    setWindowIcon(QIcon(":/pharmacy.ico"));
    makeListMenu();
    hideButton =new QPushButton("Hide Panel",this);
    hideButton->setIcon(QIcon(":/blind.ico"));
    hideButton->setGeometry(-2,670,177,30);
    vbox=new QVBoxLayout();
    vbox->addWidget(listMenu);
    vbox->addWidget(hideButton);
    QPushButton *ProfileButton =new QPushButton("Change Profile Pic",this);
    ProfileButton->setGeometry(200,200,125,40);
    QHBoxLayout *hbox =new QHBoxLayout(this);
    hbox->addLayout(vbox);
    hbox->addWidget(ProfileButton);
    connect(hideButton,SIGNAL(clicked(bool)),this,SLOT(handleHideButton()));
    connect(ProfileButton,SIGNAL(clicked(bool)),this,SLOT(changeProfileButton()));
}

MainWindow::~MainWindow() {}

void MainWindow::makeListMenu()
{
    listMenu =new QListWidget(this);
    QListWidgetItem *profile =new QListWidgetItem(QIcon(":/user.ico"),"Profile");
    QListWidgetItem *medicines=new QListWidgetItem(QIcon(":/Medicine.ico"),"Medicines");
    QListWidgetItem *ordersAndDelivery =new QListWidgetItem(QIcon(":/delivery-bike.ico"),"Orders&Delivery");
    QListWidgetItem *staff =new QListWidgetItem(QIcon(":/medical-team.ico"),"Staff");
    QListWidgetItem *salesAndReports =new QListWidgetItem(QIcon(":/business-report.ico"),"Sales And Reports");
    QListWidgetItem *bills =new QListWidgetItem(QIcon(":/bill.ico"),"Generate Bill");
    QListWidgetItem *customers =new QListWidgetItem(QIcon(":/customer.ico"),"Customer Care");
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
        QListWidgetItem *item = listWidget->item(i);
        totalHeight += listWidget->visualItemRect(item).height();
        item->setSizeHint(QSize(30,listWidget->visualItemRect(item).height()+40));
    }
    totalHeight += 2 * listWidget->frameWidth();
    listWidget->setMinimumSize(175,totalHeight+700);
    listWidget->setMaximumSize(300,totalHeight+800);
    listWidget->setIconSize(QSize(30,(totalHeight/listWidget->count())+10));
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

void MainWindow::changeProfileButton()
{
    QString filename= QFileDialog::getOpenFileName(this,"Choose a jpeg/png/ico file","C://");
    listMenu->item(0)->setIcon(QIcon(filename));
}
