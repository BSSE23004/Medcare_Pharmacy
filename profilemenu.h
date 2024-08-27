#ifndef PROFILEMENU_H
#define PROFILEMENU_H

#include <QWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>
#include <QLabel>
#include <phoneinputDialog.h>
#include <QDesktopServices>

class ProfileMenu : public QWidget
{
    Q_OBJECT
    QHBoxLayout *mainLayout;
    QVBoxLayout *contactDetailsLayout;
    QVBoxLayout *contactBoardLayout;
    QHBoxLayout *contactImageLayout;
    QLabel *contactInfoHeader;
    QPushButton *addImage;
    QPushButton *email;
    QPushButton *addPhoneNumber;

public:
    explicit ProfileMenu(QWidget *parent = nullptr,QString newEmail="N/A");

private slots:
    void handlePhoneNumber();
    void handleProfilePic();
    void handleEmail();
};

#endif // PROFILEMENU_H
