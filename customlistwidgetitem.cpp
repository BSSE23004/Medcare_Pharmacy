#include "customlistwidgetitem.h"



CustomListWidgetItem::CustomListWidgetItem(QString newCustomerName, QString newCustomerData, QListWidget *parent):QListWidgetItem{parent}
{
    setIcon(QIcon(":/customer.ico"));
    setText(newCustomerName);
    customerData=newCustomerData;

}

QString CustomListWidgetItem::getCustomerData() const
{
    return customerData;
}

void CustomListWidgetItem::setCustomerData(const QString &newCustomerData)
{
    customerData = newCustomerData;
}

