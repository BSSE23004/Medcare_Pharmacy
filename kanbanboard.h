#ifndef KANBANBOARD_H
#define KANBANBOARD_H

#include <QApplication>
#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QInputDialog>
#include <QDragEnterEvent>
#include <QMessageBox>
#include <deliveryinputdialog.h>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QListWidgetItem>
#include <QDebug>
#include <QAbstractFileIconProvider>
#include <salesandreports.h>


class KanbanBoard : public QWidget
{
    Q_OBJECT
    QVBoxLayout *mainLayout;
    QHBoxLayout *boardLayout;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *todoLayout;
    QLabel *todoLabel;
    QListWidget *todoList;
    QVBoxLayout *inProgressLayout;
    QLabel *inProgressLabel;
    QListWidget *inProgressList;
    QVBoxLayout *doneLayout;
    QLabel *doneLabel;
    QPushButton *addDeliveryButton;
    QPushButton *removeDeliveryButton;
    QListWidgetItem *listItem;
    SalesAndReports *salesMenu;
    static int orderId;
public:
    QStringList customersName;
    QStringList customersPhoneNumbers;
    QStringList customersAddresses;
    QListWidget *doneList;
    DeliveryInputDialog * deliveryInput;
    explicit KanbanBoard(QWidget *parent = nullptr,SalesAndReports *menu=nullptr);
    ~KanbanBoard();
    void writeToJson();
    void readFromJson();
    void setOrderIDInitialValue();
    int getOrderID();
private slots:
    void handleAddDelivery();
    void handleRemoveDelivery();
    void handleListsItems();
};

#endif // KANBANBOARD_H
