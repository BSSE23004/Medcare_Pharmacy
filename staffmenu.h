#ifndef STAFFMENU_H
#define STAFFMENU_H

#include <QWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QPushButton>
#include <customlistwidgetitemforstaff.h>
#include <addmemberdialog.h>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>



class StaffMenu : public QWidget
{
    Q_OBJECT
    QLabel *member;
    QLabel *memberInfo;
    QVBoxLayout *buttonsLayout;
    QHBoxLayout *mainLayout;
    QPushButton *addMember;
    QPushButton *removeMember;
    QPushButton *memberInfoButton;
    QListWidget *staffList;
    QTableWidget *memberInfoTable;

public:
    explicit StaffMenu(QWidget *parent = nullptr);
    void readFromJson();
    void writeToJson();
    ~StaffMenu();

private slots:
    void handleAddMemberButton();
    void handlestaffList();
    void handleAddingAttendance();
    void handleRemoveMember();
};

#endif // STAFFMENU_H
