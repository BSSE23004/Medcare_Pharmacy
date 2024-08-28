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
#include <QTimer>


class ProfileMenu : public QWidget
{
    Q_OBJECT
    QHBoxLayout *mainLayout;
    QVBoxLayout *contactDetailsLayout;
    QVBoxLayout *contactBoardLayout;
    QVBoxLayout *settingButtonsLayout;
    QHBoxLayout *contactImageLayout;
    QLabel *contactInfoHeader;
    QPushButton *addImage;
    QPushButton *email;
    QPushButton *addPhoneNumber;
    QPushButton *clock;
    QString iconName;
public:
    QPushButton *setWindowsOpacity;
    QPushButton *setWindowsFont;
    explicit ProfileMenu(QWidget *parent = nullptr,QString newEmail="N/A");
    ~ProfileMenu();
    void writeToJson();
    void readFromJson();
private slots:
    void handlePhoneNumber();
    void handleProfilePic();
    void handleEmail();
    void handleClock();
};

#endif // PROFILEMENU_H
