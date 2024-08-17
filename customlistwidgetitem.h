#ifndef CUSTOMLISTWIDGETITEM_H
#define CUSTOMLISTWIDGETITEM_H

#include <QListWidgetItem>
#include <QWidget>
#include <QString>


class CustomListWidgetItem : public QListWidgetItem
{
    QString customerData;
public:
    CustomListWidgetItem(QString newCustomerName="N/A",QString newCustomerData="N/A",QListWidget *parent=nullptr);
    QString getCustomerData() const;
    void setCustomerData(const QString &newCustomerData);
};

#endif // CUSTOMLISTWIDGETITEM_H
