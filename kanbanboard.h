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
#include <kanbanListWidget.h>
#include <deliveryinputdialog.h>
#include <nlohmann/json.hpp>
#include <fstream>
using namespace nlohmann;

class KanbanBoard : public QWidget
{
    Q_OBJECT
    QVBoxLayout *mainLayout;
    QHBoxLayout *boardLayout;
    QHBoxLayout *buttonLayout;
    QVBoxLayout *todoLayout;
    QLabel *todoLabel;
    KanbanListWidget *todoList;
    QVBoxLayout *inProgressLayout;
    QLabel *inProgressLabel;
    KanbanListWidget *inProgressList;
    QVBoxLayout *doneLayout;
    QLabel *doneLabel;
    KanbanListWidget *doneList;
    QPushButton *addDeliveryButton;
    QPushButton *removeDeliveryButton;
    QListWidgetItem *listItem;
    static int id;
public:
    DeliveryInputDialog * deliveryInput;
    explicit KanbanBoard(QWidget *parent = nullptr);
    ~KanbanBoard();
    void writeToJson();
    void readFromJson();
private slots:
    void handleAddDelivery();
    void handleRemoveDelivery();
    void handleListsItems();
};

#endif // KANBANBOARD_H
