#include "customercare.h"

CustomerCare::CustomerCare(QWidget *parent)
    : QWidget{parent}
{
    aw=200;
    ah=680;
    ax=10;
    ay=10;

    customersList=new QListWidget(this);
    customersList->setGeometry(ax,ay,aw,ah);
    customersList->setFont(QFont("Times New Roman",20));
    customersList->setIconSize(QSize(50,50));

    detailButton =new QPushButton(this);
    detailButton->setGeometry(300,70,400,200);
    detailButton->setIcon(QIcon(":/details.ico"));
    detailButton->setIconSize(QSize(50,50));
    detailButton->setFont(QFont("Times New Roman",16));
    detailButton->setStyleSheet("QPushButton {"
                          "border-radius: 10px;"
                          "color: DodgerBlue;"
                          "padding: 5px 10px;"
                          "}");

    initializeList();




}

void CustomerCare::initializeList()
{
    QFile file("Customers.json");
    QJsonArray customersArray;
    if(file.open(QFile::ReadOnly)){
        QByteArray jsonData =file.readAll();
        file.close();
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "Parse error: " << parseError.errorString()<<"  In initializeCustomersList In Customer Care";
        }
        if (jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();
            if (jsonObj.contains("Customers") && jsonObj["Customers"].isArray()) {
                customersArray = jsonObj["Customers"].toArray();
            } else {
                qDebug() << "Invalid JSON structure.In initializeCustomersList In Customer Care";

            }
        } else {
            qDebug() << "JSON is not an object.In initializeCustomersList In Customer Care";
        }
    } else {
        qDebug() << "Unable to open file.In initializeCustomersList In Customer Care";
    }
    customersList=new QListWidget(this);
    customersList->setGeometry(ax,ay,aw,ah);
    customersList->setFont(QFont("Times New Roman",20));
    customersList->setIconSize(QSize(50,50));
    for (int i = 0; i < customersArray.count(); ++i) {
        QJsonObject jsonCustomer =customersArray.at(i).toObject();
        if(jsonCustomer["Name"].toString()!="N/A"){
            CustomListWidgetItem *customer=new CustomListWidgetItem(jsonCustomer["Name"].toString(),"Address : "+jsonCustomer["Address"].toString()+"\nPhoneNumber : "+jsonCustomer["PhoneNumber"].toString());//"Address : "+jsonCustomer["Address"].toString()+"\nPhoneNumber : "+jsonCustomer["PhoneNumber"].toString());
            customersList->addItem(customer);
        }
    }
    connect(customersList,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(handleListWidget()));
}



void CustomerCare::handleListWidget()
{
    CustomListWidgetItem *customer = dynamic_cast<CustomListWidgetItem *>(customersList->currentItem());
    detailButton->setText(customer->getCustomerData());
}
