#ifndef STAFFMENU_H
#define STAFFMENU_H

#include <QWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QPushButton>


class StaffMenu : public QWidget
{
    Q_OBJECT
    QListWidget *staffList;
    QTableWidget *memberInfoTable;

public:
    explicit StaffMenu(QWidget *parent = nullptr);

signals:
};

#endif // STAFFMENU_H
