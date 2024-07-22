#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

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
     medicinesMenu();
}

MainWindow::~MainWindow() {
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
    removeButton->hide();
    addButton->hide();
    searchBar->hide();
    searchButton->hide();
    medicinesTable->hide();
    if(listMenu->currentItem()->text()=="Medicines"){
        medicinesTable->show();
        searchButton->show();
        searchBar->show();
        addButton->show();
        removeButton->show();
    }
}

