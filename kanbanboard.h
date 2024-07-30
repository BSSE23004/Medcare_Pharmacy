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

class KanbanBoard : public QWidget
{
    Q_OBJECT
    QVBoxLayout *mainLayout;
    QHBoxLayout *boardLayout;
    QVBoxLayout *todoLayout;
    QLabel *todoLabel;
    QListWidget *todoList;
    QVBoxLayout *inProgressLayout;
    QLabel *inProgressLabel;
    QListWidget *inProgressList;
    QVBoxLayout *doneLayout;
    QLabel *doneLabel;
    QListWidget *doneList;
    QListWidgetItem *item;
    QPushButton *addDeliveryButton;
    QListWidgetItem *listItem;
public:
    explicit KanbanBoard(QWidget *parent = nullptr);
    ~KanbanBoard();
private slots:
    void handleAddDelivery();
};

#endif // KANBANBOARD_H
